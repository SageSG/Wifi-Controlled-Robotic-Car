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

void initMotor(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
    GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5,
    GPIO_PRIMARY_MODULE_FUNCTION);

//    pwmConfig.dutyCycle = 2000;
//    pwmConfig2.dutyCycle = 2000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    Interrupt_enableInterrupt(INT_PORT1);
}

void motor_stop(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
    printf("\nmotor_stop();");
    pwmConfig.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    P2->OUT = BIT0;     // ON RED
}

void motor_start(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);

    P2->OUT = BIT1;     // ON GREEN
    pwmConfig.dutyCycle = 7825;         // LEFT
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    P2->OUT = BIT0;     // ON RED
}

void motor_back(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);

    P2->OUT = ~1;
    pwmConfig.dutyCycle = 7725;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    P2->OUT = BIT0;     // ON RED
}

void motor_left(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);

    P2->OUT = ~2;
    pwmConfig.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    P2->OUT = BIT0;     // ON RED
}

void motor_right(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);

    P2->OUT = ~1;
    pwmConfig.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
//    P2->OUT = BIT0;     // ON RED
}

void oneEighty()
{
    motor_stop();
    motor_back();
    printf("oneeighty()");
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
    printf("here()");
    P2->OUT = ~1;
    pwmConfig.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    pwmConfig2.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    //    P2->OUT = BIT0;     // ON RED
    while (secCounterM < 2)
    {
        TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
        secCounterM += 1;
    }
    motor_stop();
    secCounterM = 0;
}

void adjustLeft()
{
    pwmConfig.dutyCycle -= 25;         // LEFT
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    printf(" - ADJUSTED LEFT");
}

void adjustRight()
{
    pwmConfig2.dutyCycle -= 25;         // LEFT
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    printf(" - ADJUSTED RIGHT");
}
