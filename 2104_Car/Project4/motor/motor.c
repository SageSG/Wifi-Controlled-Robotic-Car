/*
 * motor.c
 *
 *  Created on: Nov 25, 2021
 *      Author: Jaspzx
 */

/* DriverLib Includes */

#include "motor/motor.h"

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

//void counter()
//{
//    //        ===============================================================================
//    TIMER32_1->LOAD = 3000000; /* set the reload value */
//    //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
//
//    /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
//    TIMER32_1->CONTROL = 0xC3;
//    //    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
//    //                           TIMER32_FREE_RUN_MODE);
//    while ((TIMER32_1->RIS & 1) == 0)
//        ; /* wait until the RAW_IFG is set */
//    TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
//    ////        P2->OUT ^= 4; /* toggle blue LED */
//    ////        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
//    TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
//    //        ===============================================================================
//}

//static void Delay(uint32_t loop)
//{
//    volatile uint32_t i;
//
//    for (i = 0; i < loop; i++)
//        ;
//}

void initMotor(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
    GPIO_PRIMARY_MODULE_FUNCTION);
//    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
//    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
//    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5,
    GPIO_PRIMARY_MODULE_FUNCTION);
//    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
//    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
//    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

//    pwmConfig.dutyCycle = 2000;
//    pwmConfig2.dutyCycle = 2000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    Interrupt_enableInterrupt(INT_PORT1);
}

void motor_stop(void)
{
//    printf("\nMotor_Stop();");
//    while (secCounter < 5)
//    {
//        secCounter += 1;
//        pwmConfig.dutyCycle = 0;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
//        pwmConfig2.dutyCycle = 0;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    }
//    secCounter = 0;
    pwmConfig.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    Delay(500000);
    P2->OUT = BIT0;     // ON RED
}

void motor_start(void)
{
//    printf("Hi2");
//    while (secCounter < 5)
//    {
//        printf("Hi3");
//
//        secCounter += 1;
//        pwmConfig.dutyCycle = 5000;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
//        pwmConfig2.dutyCycle = 5000;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    }
//    secCounter = 0;
    P2->OUT = BIT1;     // ON GREEN
    pwmConfig.dutyCycle = 5000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 5000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    P2->OUT = BIT0;     // ON RED
//    Delay(500000);
}

void motor_left(void)
{
//    while (secCounter < 5)
//    {
//    printf("HiLeft");
//
//        secCounter += 1;
//        pwmConfig.dutyCycle = 0;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
//        pwmConfig2.dutyCycle = 5000;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    }
//    secCounter = 0;
    P2->OUT = ~2;
    pwmConfig.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 5000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    P2->OUT = BIT0;     // ON RED
//    Delay(500000);
}

void motor_right(void)
{
//    while (secCounter < 5)
//    {
//    printf("HiRight");
//
//        secCounter += 1;
//        pwmConfig.dutyCycle = 5000;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
//        pwmConfig2.dutyCycle = 0;
//        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    }
//    secCounter = 0;
    P2->OUT = ~1;
    pwmConfig.dutyCycle = 5000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    P2->OUT = BIT0;     // ON RED
//    Delay(500000);
}

