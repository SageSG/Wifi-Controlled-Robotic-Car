/*
 * encoder.c
 *
 *  Created on: Nov 20, 2021
 *      Author: jaspz
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "encoder.h"
//#include "../ultrasonic/ultrasonic.c"


volatile uint32_t i;
volatile static uint32_t right = 0;
volatile static uint32_t left = 0;
//char rpmChar[20];
char rpmRightString[20];
char rpmLeftString[20];

float getRight()
{
    return right;
}

void setRight()
{
    right = 0;
}

float getLeft()
{
    return left;
}

void setLeft()
{
    left = 0;
}

void Encoder_Init()
{
    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);

    GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN7);

    Interrupt_enableInterrupt(INT_PORT3);
    Interrupt_enableInterrupt(INT_PORT2);
    Interrupt_enableMaster();

//    printf("\nDIstance: %.2f", getHCSR04Distance());
//    /* Obtain distance from HCSR04 sensor and check if its less then minimum distance */
//    if ((getHCSR04Distance() < MIN_DISTANCE))
//    {
//        Motor_Stop();
//    }
//    else
//    {
////        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
//    }
}

void PORT3_IRQHandler(void)
{
    uint32_t status = 0;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3) & BIT6;
    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);

    // Delay for switch debounce
    right += 1;
//    printf("\nright: %d", right);
    for (i = 0; i < 5000; i++)
        ; //sleep

    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk; // Disable SLEEPON EXIT
    __DSB(); // Ensures SLEEPONEXIT is set immediately before exiting ISR

}

void PORT2_IRQHandler(void)
{
    uint32_t status2 = 0;
    status2 = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2) & BIT7;
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status2);

    // Delay for switch debounce
//    printf("\nleft: %d", left);
    left += 1;
    for (i = 0; i < 5000; i++)
        ; //sleep

    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk; // Disable SLEEPON EXIT
    __DSB(); // Ensures SLEEPONEXIT is set immediately before exiting ISR
}

