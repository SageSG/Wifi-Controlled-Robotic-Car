/*
 * motor.c
 *
 *  Created on: Nov 25, 2021
 *      Author: Jaspzx
 */

#include "motor/motor.h"

/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfigLeft = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                    TIMER_A_CLOCKSOURCE_DIVIDER_24, 10000,
                                    TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                    TIMER_A_OUTPUTMODE_RESET_SET, 1000 };

Timer_A_PWMConfig pwmConfigRight = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                     TIMER_A_CLOCKSOURCE_DIVIDER_24, 10000,
                                     TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                     TIMER_A_OUTPUTMODE_RESET_SET, 1000 };

/* Delay. */
static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++)
        ;
}

/* Initialise the motor. */
void initMotor(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
    GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5,
    GPIO_PRIMARY_MODULE_FUNCTION);

//    pwmConfigLeft.dutyCycle = 2000;
//    pwmConfigRight.dutyCycle = 2000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
//    Interrupt_enableInterrupt(INT_PORT1);
}

/* Stop the car.*/
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
    pwmConfigLeft.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    pwmConfigRight.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
    P2->OUT = BIT0;     // ON RED
}

/* Start the car, Move Straight.*/
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
    pwmConfigLeft.dutyCycle = 7700;         // LEFT
    pwmConfigRight.dutyCycle = 8000;        //Right
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);

    Delay(5000);
}

/* Reverse the car. */
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
    pwmConfigLeft.dutyCycle = 7725;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    pwmConfigRight.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
    P2->OUT = BIT0;     // ON RED
}

/* Turn the Car left.   */
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
    pwmConfigLeft.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    pwmConfigRight.dutyCycle = 7000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
//    P2->OUT = BIT0;     // ON RED
}

/* Turn the car right. */
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
    pwmConfigLeft.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    pwmConfigRight.dutyCycle = 0;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
}

/* Turn the car 180 Degrees. */
void oneEighty()
{
//    motor_stop();
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
    pwmConfigLeft.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    pwmConfigRight.dutyCycle = 8000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
    //    P2->OUT = BIT0;     // ON RED
    while (secCounterM < 2)
    {
        TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
        secCounterM += 1;
    }
    motor_stop();
    secCounterM = 0;
}

/* Adjusting PWM for RightSide */
void adjustLeft()
{
//    int diff = pwmConfigRight.dutyCycle - pwmConfigLeft.dutyCycle;
//    pwmConfigLeft.dutyCycle -= diff;
//    pwmConfigRight.dutyCycle -= 20;         // LEFT
    pwmConfigRight.dutyCycle += 15;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
    printf(" - ADJUSTED RIGHT");
    printf("\nPWMLEFT:  %d", pwmConfigLeft.dutyCycle);
    printf(" | PWMRIGHT: %d\n", pwmConfigRight.dutyCycle);
}

/* Adjusting PWM for LeftSide */
void adjustRight()
{
//    pwmConfigRight.dutyCycle -= 22;         // RIGHT
//    int diff = pwmConfigLeft.dutyCycle - pwmConfigRight.dutyCycle;
//    pwmConfigRight.dutyCycle -= diff;
    pwmConfigLeft.dutyCycle += 10;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    printf(" - ADJUSTED LEFT");
    printf("\nPWMLEFT:  %d", pwmConfigLeft.dutyCycle);
    printf(" | PWMRIGHT: %d\n", pwmConfigRight.dutyCycle);
}
