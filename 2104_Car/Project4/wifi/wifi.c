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

#include "wifi.h"
#include "../motor/motor.h"
#include "ultrasonic/ultrasonic.h"
#include "../temperature/temperature.h"

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

//int count;
////const char *username = "Xperia5II";
////const char *password = "mango12345";
//const char *username = "Linksys21487";
//const char *password = "axmpdgh5pr";
////const char *username = "AndroidAP542c";
////const char *password = "vgar7960";
//
//const char *url = "192.168.10.139";
//volatile char cmdString[20] = "";
//
//const char *PATTERN1 = "\"command\": \"";
//const char *PATTERN2 = "\"";
////char HTTP_Request[] = "GET /car/commands HTTP/1.1\r\n\r\n";
//char HTTP_Request[] = "GET /car/test HTTP/1.1\r\n\r\n";
//
//volatile static int secCounter = 0;
//bool obstacle = false;
//int timer = 0;
//float rpm = 0.0;
//float rotations = 0.0;

eUSCI_UART_ConfigV1 UART0Config = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK, 13, 0, 37,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION };

eUSCI_UART_ConfigV1 UART2Config = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK, 13, 0, 37,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION };

void initWifi()
{
    MAP_WDT_A_holdTimer();
//    MSPrintf(EUSCI_A0_BASE, "Setting Wifi.\n\r");

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
//    Interrupt_enableInterrupt(INT_PORT5);

    MAP_Interrupt_enableMaster();

    /*Hard Reset ESP8266*/
    ESP8266_HardReset();
    __delay_cycles(48000000);
    /*flush reset data, we do this because a lot of data received cannot be printed*/
    UART_Flush(EUSCI_A2_BASE);
    MSPrintf(EUSCI_A0_BASE, "Hard Reset\n\r");

    /*Pointer to ESP8266 global buffer*/
    char *ESP8266_Data = ESP8266_GetBuffer();
    MSPrintf(EUSCI_A0_BASE, "1.\n\r");

//    if (!ChangeMode())
//    {
//        MSPrintf(EUSCI_A0_BASE, "H2\n\r");
//        while (1)
//            ;
//    }

    MSPrintf(EUSCI_A0_BASE, "Set WiFi Mode\n\r");

    if (!ConnectToAP(username, password))
    {
        MSPrintf(EUSCI_A0_BASE, "2.\n\r");

        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "Connect to WiFi\n\r");

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
    MSPrintf(EUSCI_A0_BASE, "AT+CIPSTART='TCP','192.168.10.139',80\n\r");

    float ultrasonicReading = 0.0;
    float temperatureReading = 10.0;
    int batteryReading = 90;
    float distanceReading = 13.50;
    float speedReading = 5.50;
    int lineReading = 0;

    char ultraString[5];
    char tempString[5];
    char batString[5];
    char distString[5];
    char speedString[5];
    char lineString[5];

    sprintf(ultraString, "%.2f", ultrasonicReading);
    sprintf(tempString, "%.2f", temperatureReading);
    sprintf(batString, "%d", batteryReading);
    sprintf(distString, "%.2f", distanceReading);
    sprintf(speedString, "%.2f", speedReading);
    sprintf(lineString, "%d", lineReading);

    printf("\n%s\n", ultraString);
    printf("%s\n", tempString);
    printf("%s\n", batString);
    printf("%s\n", distString);
    printf("%s\n", speedString);
    printf("%s\n", lineString);

//            char done = true;
//            char HTTP_Request[] = "POST ";
//
//            while(done){
//                strcat(HTTP_Request, "/car/stats?mac_addr=12345&temperature=");
//                    strcat(HTTP_Request, tempString);
//                    strcat(HTTP_Request, "&battery_level=");
//                    strcat(HTTP_Request, batString);
//                    strcat(HTTP_Request, "&distance=");
//                    strcat(HTTP_Request, distString);
//                    strcat(HTTP_Request, "&speed=");
//                    strcat(HTTP_Request, speedString);
//                    strcat(HTTP_Request, "&line_detected=");
//                    strcat(HTTP_Request, lineString);
//                    strcat(HTTP_Request, " HTTP/1.1\r\n\r\n");
//                    printf("%s\n", HTTP_Request);
//                    done = false;
//            }

//            char HTTP_Request[] = "POST /car/stats HTTP/1.1\r\nContent-Type: text/plain\r\nContent-Length: 9\r\n\r\name=\r\n\r\n";

    uint32_t HTTP_Request_Size = sizeof(HTTP_Request) - 1;

    if (!SendData(HTTP_Request, HTTP_Request_Size))
    {
        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "Send Data\n\r");

    MSPrintf(EUSCI_A0_BASE,
             "Data sent: %s to %s\r\n\r\nESP8266 Data Received: %s\r\n",
             HTTP_Request, "192.168.10.139", ESP8266_Data);
    getData(ESP8266_Data);

//    printf("\nLevel1: %s", getData(ESP8266_Data));
//    printf("\nGet function: %s", getCmdString());
//    printf("\nString: %s", cmdString);
//    Interrupt_enableInterrupt(INT_PORT5);
    runString();
//            printf("%s\n", result);

//            while(1)
//                {
////                Delay(20000);
////                HTTP_Request[] = ''
////                MSPrintf(EUSCI_A0_BASE, "Data sent: %s to %s\r\n\r\nESP8266 Data Received: %s\r\n", HTTP_Request, "192.168.215.85", ESP8266_Data);
////                HTTP_Request[] = "POST /car/stats?mac_addr=12345&temperature=27.5&battery_level=50&distance=10&speed=5&line_detected=0 HTTP/1.1\r\n\r\n";
////                for (i = 1; i < 1000; ++i);
//
//                    /*You can query data here by sending the HTTP request string every n seconds.
//                     * Be careful about the amount of times per second that you can query data from an API
//                     */
////                for ( count = 0; count < 10000; count++) { }
//                }

    /*Start ESP8266 serial terminal, will not return*/
//    ESP8266_Terminal();
}
;

void counter()
{
    //        ===============================================================================
    TIMER32_1->LOAD = 3000000; /* set the reload value */
    //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);

    /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
    TIMER32_1->CONTROL = 0xC3;
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
//
//char getCmdString()
//{
////    printf("\nWithin Function %s\n", cmdString);
//    return cmdString;
//}

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
//    char test[] = target;
//    printf("%s", test);
//        strcat(cmdString, target);
//        printf('hedecc');
//        printf(cmdString);
//        printf('hedecc');

    int i = 0; //start at 0
    do
    {
        cmdString[i] = target[i]; //assign s[i] to the string literal index i
    }
    while (cmdString[i++]);
//    printf("HEREEE: %s", cmdString);
    free(target);
//    runString();
    return 0;
//    return cmdString;
}
;

void checkObstacle()
{
    if ((getHCSR04Distance() < 15.0))
    {
        printf("\nOBSTACLEEEE;");
//        motor_stop();
        oneEighty();
        obstacle = true;
    }
}



void runString()
{
//    printf("\nIMM INNNNN");
    printf("\nString: %s", cmdString);
    size_t length = strlen(cmdString);
    int i = 0;
//    printf("Hiiii?");
    for (; i < length && obstacle == false; i++)
    {
        while ((TIMER32_1->RIS & 1) == 0)
            ; /* wait until the RAW_IFG is set */
        TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */

        printf("\nDIstance: %.2f", getHCSR04Distance());
        printf("\n%c", cmdString[i]); /* Print each character of the string. */
//        printf("hellooo?;");
//        uart_println("Temperature(degC): %f", tempC);
        switch (cmdString[i])
        {
        case '0':
            printf("\nMotor_Stop();");
            motor_stop();
            obstacle = true;
            break;
        case '1':
            printf("\nMotor_Start();");
            motor_start();
            while (secCounter < 10)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
//                printf("%d\n", timer);
                printf("\nrpm: %.2f", rpm);
                checkObstacle();
                rpm = 0;
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            break;
        case '2':
            printf("\nMotor_Left();");
            motor_left();
            while (secCounter < 7)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
//                printf("%d\n", timer);
                printf("\nrpm: %.2f", rpm);
                checkObstacle();
                rpm = 0;
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            break;
        case '3':
            printf("\nMotor_Right();");
            motor_right();
            while (secCounter < 7)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
//                printf("%d\n", timer);
                printf("\nrpm: %.2f", rpm);
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
            while (secCounter < 10)
            {
                rotations = ((getLeft() + getRight()) / 20) / 2;
                rpm = ((float) rotations / (float) timer) * 60.00;
                timer++;
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
                //                printf("%d\n", timer);
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
    printf("\n--String End--");
}
