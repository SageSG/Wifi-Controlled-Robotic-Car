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

// TX: 3.2
//RX: 3.3
// RST: 6.1
// EN: 3.3v


// Baud:        115200
// Data Size:   8
// Parity:      None
// Stop Bit:    1

int count;

const char *username = "Xperia5II";
const char *password = "mango12345";
//const char *username = "AndroidAP542c";
//const char *password = "vgar7960";

const char *url = "192.168.40.247";
char cmdString[20] = "";

const char *PATTERN1 = "\"command\": \"";
const char *PATTERN2 = "\"";
//char HTTP_Request[] = "GET /car/commands HTTP/1.1\r\n\r\n";
char HTTP_Request[] = "GET /car/test HTTP/1.1\r\n\r\n";

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

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++)
        ;
}

void initWifi()
{
    MAP_WDT_A_holdTimer();

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

    /*Pointer to ESP8266 global buffer*/
    char *ESP8266_Data = ESP8266_GetBuffer();

    if (!ChangeMode())
    {
        while (1)
            ;
    }
    MSPrintf(EUSCI_A0_BASE, "Set WiFi Mode\n\r");

    if (!ConnectToAP(username, password))
    {
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
    MSPrintf(EUSCI_A0_BASE, "AT+CIPSTART='TCP','192.168.40.247',80\n\r");

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
             HTTP_Request, "192.168.40.247", ESP8266_Data);

    getData(ESP8266_Data);
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

bool getData(char *s)
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
        printf("%s\n", target);
//    char test[] = target;
//    printf("%s", test);
//        strcat(cmdString, target);
//        printf('hedecc');
//        printf(cmdString);
//        printf('hedecc');

//        cmdString = target;
    free(target);

    return 0;
//    return cmdString;
}
;
