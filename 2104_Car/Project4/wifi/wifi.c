/*
 * wifi.c
 *
 *  Created on: Nov 25, 2021
 *      Author: Jaspzx
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <UART_Driver.h>
#include <MSPIO.h>
#include <ESP8266.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "wifi.h"
#include "../motor/motor.h"
#include "ultrasonic/ultrasonic.h"
#include "../temperature/temperature.h"
#include "../encoder/encoder.h"

//uint64_t status;
int16_t conRes;

//==========================================

// TX:      3.2
// RX:      3.3
// RST:     6.1
// EN:      3.3v

// Baud:        115200
// Data Size:   8
// Parity:      None
// Stop Bit:    1

//==========================================

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++)
        ;
}

void initWifi()
{

    MAP_WDT_A_holdTimer();

    /*Pointer to ESP8266 global buffer*/
    char *ESP8266_Data = ESP8266_GetBuffer();

//    if (!EstablishConnection(TCP, url, "80"))
//    {
//        while (1)
//            ;
//    }
//    MSPrintf(EUSCI_A0_BASE, "AT+CIPSTART='TCP','192.168.215.247',80\n\r");

//    sendData();
    uint32_t HTTP_Request_Size = sizeof(HTTP_Request) - 1;

    if (!SendData(HTTP_Request, HTTP_Request_Size))
    {
        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "Send Data\n\r");

    MSPrintf(EUSCI_A0_BASE,
             "Data sent: %s to %s\r\n\r\nESP8266 Data Received: %s\r\n",
             HTTP_Request, "192.168.125.247", ESP8266_Data);

    getData(ESP8266_Data);

    init_HCSR04();
    runString();
}
;

void connectWifi(void)
{
    /*Ensure MSP432 is Running at 24 MHz*/
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    /*Initialize required hardware peripherals for the ESP8266*/
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A0_BASE, &UART0Config);
    MAP_UART_enableModule(EUSCI_A0_BASE);
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);

    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A2_BASE, &UART2Config);
    MAP_UART_enableModule(EUSCI_A2_BASE);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);

    /*Reset GPIO of the ESP8266*/
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN1);

    MAP_Interrupt_enableMaster();

    /*Hard Reset ESP8266*/
    ESP8266_HardReset();
    __delay_cycles(48000000);
    /*flush reset data, we do this because a lot of data received cannot be printed*/
    UART_Flush(EUSCI_A2_BASE);
    MSPrintf(EUSCI_A0_BASE, "Hard Reset\n\r");

    if (!ChangeMode())
    {
        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "Set WiFi Mode\n\r");

    if (!ConnectToAP(username, password))
    {
        MSPrintf(EUSCI_A0_BASE, "Cannot connect to AP\n\r");
        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "Connected to WiFi\n\r");

    if (!QueryIP())
    {
        MSPrintf(EUSCI_A0_BASE, "IP address not available\n\r");
        while (1)
            ;
    }

    if (!EstablishConnection(TCP, url, "80"))
    {
        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "AT+CIPSTART='TCP','192.168.125.247',80\n\r");

}

void counter()
{
    //        ===============================================================================
//    TIMER32_1->LOAD = 3000000; /* set the reload value */
    //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);

    /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
//    TIMER32_1->CONTROL = 0xC3;
    //    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
    //                           TIMER32_FREE_RUN_MODE);
    while ((TIMER32_1->RIS & 1) == 0)
        ; /* wait until the RAW_IFG is set */
    TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
    ////        P2->OUT ^= 4; /* toggle blue LED */
    ////        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
    //        ===============================================================================
}

char getData(char *s)
{
    char *target = NULL;
    char *start, *end;

    if (start = strstr(s, PATTERN1))
    {
        start += strlen(PATTERN1);
        if (end = strstr(start, PATTERN2))
        {
            target = (char*) malloc(end - start + 1);
            memcpy(target, start, end - start);
            target[end - start] = '\0';
        }
    }

    if (target)
        printf("Target: %s\n", target);

    int i = 0; //start at 0
    do
    {
        cmdString[i] = target[i]; //assign s[i] to the string literal index i
    }
    while (cmdString[i++]);
    free(target);
    return 0;
}
;

void sendWifi()
{
    /*Pointer to ESP8266 global buffer*/
    char *ESP8266_DataSend = ESP8266_GetBuffer();

    char HTTP_Request[80];
//    char HTTP_Request[] =
//            "POST stats_controller?temp=99.0&dist=888.50&speed=44&line=1 HTTP/1.1\r\n\r\n";

    sprintf(HTTP_Request, "%s%.2f%s%.2f%s%.2f%s%d%s",
            "POST stats_controller?temp=", temperatureReading, "&dist=",
            distanceReading, "&speed=", speedReading, "&line=", lineReading,
            " HTTP/1.1\r\n\r\n\r\n\r\n\r\n\r\n");

    MSPrintf(EUSCI_A0_BASE, HTTP_Request);

    uint32_t HTTP_Request_Size = sizeof(HTTP_Request) - 1;

    if (!SendData(HTTP_Request, HTTP_Request_Size))
    {
        MSPrintf(EUSCI_A0_BASE, "Error send data");
        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "Send SENSOR DATA\n\r");

    MSPrintf(EUSCI_A0_BASE,
             "Data sent: %s to %s\r\n\r\nESP8266 Data Received: %s\r\n",
             HTTP_Request, "192.168.125.247", ESP8266_DataSend);
}
;

void checkObstacle()
{
//    printf("\nDistance: %.2f", getHCSR04Distance());

    if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 1
            && GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN7) == 1)
    {
        printf("\n--LINE Detected--");
        lineReading = 1;
        motor_stop();
        obstacle = true;
    }
    if ((getHCSR04Distance() < 4.0))
    {
        printf("\nOBSTACLEEEE;");
        printf("\nDistance: %.2f", getHCSR04Distance());

        lineReading = 1;
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        motor_stop();
        obstacle = true;
    }
}

void runString()
{
    obstacle = false;
    lineReading = 0;
//    char cmdString[] = '1';
    printf("\nString: %s", cmdString);

    TIMER32_1->LOAD = 3000000; /* set the reload value */
    //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
    TIMER32_1->CONTROL = 0xC3;

    size_t length = strlen(cmdString);
    int i = 0;
    for (; i < length; i++)
    {
        switch (cmdString[i])
        {
        case '2':
            printf("\nMotor_Stop();");
            motor_stop();
            obstacle = true;
            break;
        case '1':
            printf("\nMotor_Start();");
            motor_start();
            while (secCounter < 5 && obstacle == false)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                rpmL = ((float) (getLeft() / 20) / (float) timer) * 60.00;
                rpmR = ((float) (getRight() / 20) / (float) timer) * 60.00;
                speedReading = ((rpmL + rpmR) / 2.0);
//                printf("Speed reeading:  %.2f", speedReading);
                temperatureReading = ((float) rand() / RAND_MAX)
                        * (float) (28.0);
//                temperatureReading = ((float) rand() % (26 - 18 + 1) * (float))
                distanceReading = getHCSR04Distance();

//                conRes = ((ADC14_getResult(ADC_MEM0) - cal30) * 55);
//                tempC = (conRes / calDifference) + 30.0f;
//                temperatureReading = tempC;
                printf("\nrpmLEFT: %.2f", rpmL);
                printf(" | rpmRIGHT: %.2f", rpmR);
                if (rpmL > rpmR)
                {
                    if (rpmL - rpmR >= 1)
                    {
                        printf(" - FAST LEFT");
                        adjustLeft();
                    }
                }
                else if (rpmR > rpmL)
                {
                    if (rpmR - rpmL >= 1)
                    {
                        printf(" - FAST RIGHT");
                        adjustRight();
                    }
                }

                checkObstacle();
//                rpm = 0;
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            break;
        case '3':
            printf("\nMotor_Left();");
            motor_left();
            while (secCounter < 5 && obstacle == false)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                rpmL = ((float) (getLeft() / 20) / (float) timer) * 60.00;
                rpmR = ((float) (getRight() / 20) / (float) timer) * 60.00;
                speedReading = ((rpmL + rpmR) / 2.0);
                //                printf("Speed reeading:  %.2f", speedReading);
                temperatureReading = ((float) rand() / RAND_MAX)
                        * (float) (28.0);
                //                temperatureReading = ((float) rand() % (26 - 18 + 1) * (float))
                distanceReading = getHCSR04Distance();
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
                printf("\nrpm: %.2f", rpm);
                checkObstacle();
                rpm = 0;
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            break;
        case '4':
            printf("\nMotor_Right();");
            motor_right();
            while (secCounter < 5)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                rpmL = ((float) (getLeft() / 20) / (float) timer) * 60.00;
                rpmR = ((float) (getRight() / 20) / (float) timer) * 60.00;
                speedReading = ((rpmL + rpmR) / 2.0);
                //                printf("Speed reeading:  %.2f", speedReading);
                temperatureReading = ((float) rand() / RAND_MAX)
                        * (float) (28.0);
                //                temperatureReading = ((float) rand() % (26 - 18 + 1) * (float))
                distanceReading = getHCSR04Distance();

                //                conRes = ((ADC14_getResult(ADC_MEM0) - cal30) * 55);
                //                tempC = (conRes / calDifference) + 30.0f;
                //                temperatureReading = tempC;
                printf("\nrpmLEFT: %.2f", rpmL);
                printf(" | rpmRIGHT: %.2f", rpmR);
                checkObstacle();
                rpm = 0;
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            break;
        case '9':
            printf("\nMotor_back();");
            motor_back();
            while (secCounter < 5 && obstacle == false)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                rpmL = ((float) (getLeft() / 20) / (float) timer) * 60.00;
                rpmR = ((float) (getRight() / 20) / (float) timer) * 60.00;
                speedReading = ((rpmL + rpmR) / 2.0);
                //                printf("Speed reeading:  %.2f", speedReading);
                temperatureReading = ((float) rand() / RAND_MAX)
                        * (float) (28.0);
                //                temperatureReading = ((float) rand() % (26 - 18 + 1) * (float))
                distanceReading = getHCSR04Distance();
//                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
                printf("\nrpm: %.2f", rpm);
                checkObstacle();
                rpm = 0;
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            break;
        }
    }
    obstacle = false;
    motor_stop();
    printf("\n--Cmd End--\n");
}
