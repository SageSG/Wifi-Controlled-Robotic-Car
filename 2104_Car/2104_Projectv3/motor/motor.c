/*
 * motor.c
 *
 *  Created on: Nov 19, 2021
 *      Author: jaspz
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "motor.h"

/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                TIMER_A_CLOCKSOURCE_DIVIDER_24, 10000,
                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                TIMER_A_OUTPUTMODE_RESET_SET, 1000 };

Timer_A_PWMConfig pwmConfig2 = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                 TIMER_A_CLOCKSOURCE_DIVIDER_24, 10000,
                                 TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                 TIMER_A_OUTPUTMODE_RESET_SET, 1000 };

void Motor_Init(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
    GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5,
    GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    pwmConfig.dutyCycle = 3000;
    pwmConfig2.dutyCycle = 3000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    Interrupt_enableInterrupt(INT_PORT1);

}
void Motor_Stop(void)
{
    pwmConfig.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);

    P2->OUT = BIT0;     // ON RED
}

void Motor_Start(void)
{
    P2->OUT = BIT1;     // ON GREEN
    pwmConfig.dutyCycle = 5000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 5000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    P2->OUT = BIT0;     // ON RED
}

void Motor_Left(void)
{
    P2->OUT = ~2;
    pwmConfig.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 3000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    P2->OUT = BIT0;     // ON RED
}

void Motor_Right(void)
{
    P2->OUT = ~1;
    pwmConfig.dutyCycle = 3000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    P2->OUT = BIT0;     // ON RED
}

void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (status & GPIO_PIN1)
    {
        MAP_GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        MAP_Timer32_setCount(TIMER32_0_BASE, 128000);
        MAP_Timer32_enableInterrupt(TIMER32_0_BASE);
//        ==============================================================
//        Motor_Start();
//        if (pwmConfig.dutyCycle == 9000)
//            pwmConfig.dutyCycle = 3000;
//        else
//            pwmConfig.dutyCycle += 1000;
//
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
//
//        if (pwmConfig2.dutyCycle == 9000)
//            pwmConfig2.dutyCycle = 3000;
//        else
//            pwmConfig2.dutyCycle += 1000;
//
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    }
//    if (status & GPIO_PIN4)
//
//    }
}

