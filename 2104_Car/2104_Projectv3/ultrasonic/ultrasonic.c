/*
 * ultrasonic.c
 *
 *  Created on: Nov 20, 2021
 *      Author: jaspz
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Include Files */

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MIN_DISTANCE    15.0f
#define TICKPERIOD      1000

uint32_t SR04IntTimes;

// -------------------------------------------------------------------------------------------------------------------

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++)
        ;
}

// -------------------------------------------------------------------------------------------------------------------

void Initalise_HCSR04(void)
{
    /* Timer_A UpMode Configuration Parameter */
    const Timer_A_UpModeConfig upConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/3 = 1MHz
            TICKPERIOD,                             // 1000 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
            };

    int a = CS_getSMCLK();

    /* Configuring P3.6 as Output */
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0);                        //
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0);                        //

    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P5, GPIO_PIN2);

    /* Configuring Timer_A0 for Up Mode */
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

    /* Enabling interrupts and starting the timer */
    Interrupt_enableInterrupt(INT_TA0_0);
    //Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    //Timer_A_stopTimer(TIMER_A0_BASE);
    Timer_A_clearTimer(TIMER_A0_BASE);
}

// -------------------------------------------------------------------------------------------------------------------

void TA0_0_IRQHandler(void)
{
    /* Increment global variable (count number of interrupt occurred) */
    SR04IntTimes++;

    /* Clear interrupt flag */
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,
    TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

// -------------------------------------------------------------------------------------------------------------------

static uint32_t getHCSR04Time(void)
{
    uint32_t pulsetime = 0;

    /* Number of times the interrupt occurred (1 interrupt = 1000 ticks)    */
    pulsetime = SR04IntTimes * TICKPERIOD;

    /* Number of ticks (between 1 to 999) before the interrupt could occur */
    pulsetime += Timer_A_getCounterValue(TIMER_A0_BASE);

    /* Clear Timer */
    Timer_A_clearTimer(TIMER_A0_BASE);

    Delay(3000);

    return pulsetime;
}

// -------------------------------------------------------------------------------------------------------------------

float getHCSR04Distance(void)
{
    uint32_t pulseduration = 0;
    float calculateddistance = 0;

    /* Generate 10us pulse at P3.6 */
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN0);
    Delay(30);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0);

    /* Wait for positive-edge */
    while (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN2) == 0)
        ;

    /* Start Timer */
    SR04IntTimes = 0;
    Timer_A_clearTimer(TIMER_A0_BASE);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    /* Detects negative-edge */
    while (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN2) == 1)
        ;

    /* Stop Timer */
    Timer_A_stopTimer(TIMER_A0_BASE);

    /* Obtain Pulse Width in microseconds */
    pulseduration = getHCSR04Time();

    /* Calculating distance in cm */
    calculateddistance = (float) pulseduration / 58.0f;

    return calculateddistance;
}

// -------------------------------------------------------------------------------------------------------------------

//void Ultrasonic_Init(void)
//{
//    Initalise_HCSR04();
//
//    /* Configure P1.0 and set it to LOW */
//    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
//    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
//
////    while (1)
////    {
////        Delay(3000);
////        printf("\nDIstance: %.2f", getHCSR04Distance());
////        /* Obtain distance from HCSR04 sensor and check if its less then minimum distance */
////        if ((getHCSR04Distance() < MIN_DISTANCE))
////        {
////            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
////            Motor_Stop();
////        }
////        else
////        {
////            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
//////            Motor_Stop();
////        }
////    }
//}

