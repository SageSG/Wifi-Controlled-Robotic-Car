/*
 * encoder.c
 *
 *  Created on: Nov 26, 2021
 *      Author: Jaspzx
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

volatile uint32_t i;
volatile static uint32_t right = 0;
volatile static uint32_t left = 0;
int rotationLeft = 0;
int rotationRight = 0;
uint32_t status = 0;
uint32_t status2 = 0;

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

int getRotationLeft()
{
    return left / 20;
}

int getRotationRight()
{
    return right / 20;
}

void initEncoder()
{
//    printf("\nIm hereee");

    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);

    GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN7);

    Interrupt_enableInterrupt(INT_PORT3);
    Interrupt_enableInterrupt(INT_PORT2);

    TIMER32_1->LOAD = 3000000; /* set the reload value */
    //    //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    //    /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
    TIMER32_1->CONTROL = 0xC3;
//    Interrupt_enableMaster();
}

void PORT3_IRQHandler(void)
{
//    status = 0;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3) & BIT6;
    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);
//    printf("\nright: %d", right);

    right += 1;
//    if (right == 20)
//    {
//        rotationRight += 1;
//    }

//    for (i = 0; i < 5000; i++)
//        ; //sleep

//    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk; // Disable SLEEPON EXIT
//    __DSB(); // Ensures SLEEPONEXIT is set immediately before exiting ISR
}

void PORT2_IRQHandler(void)
{
//    status2 = 0;
    status2 = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2) & BIT7;
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status2);
//    printf("\nleft: %d", left);

    left += 1;
//    if (left == 20)
//    {
//        rotationLeft += 1;
//    }
//    for (i = 0; i < 5000; i++)
//        ; //sleep

//    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk; // Disable SLEEPON EXIT
//    __DSB(); // Ensures SLEEPONEXIT is set immediately before exiting ISR
}

