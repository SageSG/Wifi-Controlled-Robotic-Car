/*
 * uart.c
 *
 *  Created on: Nov 20, 2021
 *      Author: jaspz
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//#include <MSPIO.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

char secString[20];
char rpmString[20];
char commands[20] = "123010";
volatile uint32_t rpmRight;
volatile uint32_t rpmLeft;
uint32_t fiveSec = 0;
uint32_t threeSec = 0;
uint32_t lineCount = 0;
volatile static float rpm = 0.0;
volatile static float secCounter = 0.0;
volatile bool car_stop = false;

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++)
        ;
}

void uPrintf(unsigned char *TxArray)
{
    unsigned short i = 0;
    while (*(TxArray + i))
    {
        UART_transmitData(EUSCI_A0_BASE, *(TxArray + i)); // Write the character at the location specified by pointer
        i++;                 // Increment pointer to point to the next character
    }
}

const eUSCI_UART_ConfigV1 uartConfig = { EUSCI_A_UART_CLOCKSOURCE_SMCLK, // SMCLK Clock Source
        19,                                             // BRDIV = 78
        8,                                              // UCxBRF = 2
        85,                                              // UCxBRS = 0
        EUSCI_A_UART_ODD_PARITY,                        // ODD Parity
        EUSCI_A_UART_LSB_FIRST,                         // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,                      // One stop bit
        EUSCI_A_UART_MODE,                              // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                          // 8 bit data length
        };

// Reverses a string 'str' of length 'len'
void reverseUart(char *str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStrUart(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverseUart(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void ftoaUart(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int) n;

    // Extract floating part
    float fpart = n - (float) ipart;

    // convert integer part to string
    int i = intToStrUart(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStrUart((int) fpart, res + i + 1, afterpoint);
    }
}

void Uart_Init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN7);
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN7);

    Interrupt_enableInterrupt(INT_PORT5);

//    TIMER32_1->LOAD = 3000000; /* set the reload value */
////    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
//
//    /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
//    TIMER32_1->CONTROL = 0xC3;
////    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
////                           TIMER32_FREE_RUN_MODE);

    /* Selecting P1.2 and P1.3 in UART mode */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
    GPIO_PIN2 | GPIO_PIN3,
                                               GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 12MHz */
//    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_3);
//    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
    /* Configuring UART Module */
    UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    UART_enableModule(EUSCI_A0_BASE);

    /* Enabling interrupts (Rx) */
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA0);
//    Interrupt_enableMaster();
    uPrintf("| Starting Car.\n\r");

    runString();

//    while (car_stop == false)
//    {
//        while ((TIMER32_1->RIS & 1) == 0)
//            ; /* wait until the RAW_IFG is set */
//        TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
//////        P2->OUT ^= 4; /* toggle blue LED */
//////        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
//        TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
//
//        secCounter += 1;
////        ftoaUart(secCounter, secString, 1);
////        uPrintf(secString);
//        rpmRight = getRight();
//        rpmLeft = getLeft();
//        rpm = (rpmRight + rpmLeft) / 2;
//        rpm = (rpm / secCounter) * 6;
//        ftoaUart(rpm, rpmString, 1);
//        strcat(rpmString, "rpm | ");
////        uPrintf(rpmString);
//
////        printf("\nDIstance: %.2f", getHCSR04Distance());
////        uPrintf("hi");
//        /* Obtain distance from HCSR04 sensor and check if its less then minimum distance */
////        if ((getHCSR04Distance() < 15.0))
////        {
////            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
////            Motor_Stop();
////        }
////        else
////        {
////            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
////            //            Motor_Stop();
////        }
//    }
}

void PORT5_IRQHandler(void)
{
    uint32_t statusLeft = 0;
    uint32_t statusRight = 0;
    statusLeft = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5) & BIT6;
    statusRight = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5) & BIT7;
    GPIO_clearInterruptFlag(GPIO_PORT_P5, statusLeft);
    GPIO_clearInterruptFlag(GPIO_PORT_P5, statusRight);

    if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 0
            && GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN7) == 0)
    {
        uPrintf("LINEEEEEEEEEEEEEEEEEEEEEEE");
        Motor_Stop();
//        lineCount++;
//        if (lineCount == 3)
//        {
//            uPrintf("CAR STOPPPED");
//            Motor_Stop();
//            car_stop = true;
//        }
    }
//    else
//    {
//        lineCount = 0;
//    }

    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk; // Disable SLEEPON EXIT
    __DSB(); // Ensures SLEEPONEXIT is set immediately before exiting ISR

}

/* EUSCI A0 UART ISR */
void EUSCIA0_IRQHandler(void)
{
    unsigned char x = 0;

    x = UART_receiveData(EUSCI_A0_BASE);

    UART_transmitData(EUSCI_A0_BASE, x);

    if (x == 115)
    {
        uPrintf("\nStopping.");
        Motor_Stop();
    }
    else if (x == 119)
    {
        uPrintf("\nMoving Forward.");
//        size_t length = strlen(commands);
//        int i = 0;
//        for (; i < length; i++)
//        {
//            printf("%c\n", commands[i]); /* Print each character of the string. */
//            switch (commands[i])
//            {
//            case '0':
//                printf("stop Car");
//                break;
//            case '1':
//                printf("Start CAr");
//                break;
//            case '2':
//                printf("Left");
//                break;
//            case '3':
//                printf("Right");
//                break;
//            }
//    }
        Motor_Start();
    }
    else if (x == 97)
    {
        uPrintf("\nTurning LEFT.");
        Motor_Left();
    }
    else if (x == 100)
    {
        uPrintf("\nTurning RIGHT.");
        Motor_Right();
    }
}
