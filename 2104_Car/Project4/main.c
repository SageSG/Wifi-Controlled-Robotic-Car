/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432 Empty Project
 *
 * Description: An empty project that uses DriverLib
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST               |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author: 
 *******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "motor/motor.h"
#include "ultrasonic/ultrasonic.h"
#include "encoder/encoder.h"
#include "temperature/temperature.h"
//#include "wifi/wifi.h"

//bool obstacle = false;
//int timer = 0;
//float rpm = 0.0;
//float rotations = 0.0;
//char commandsM[20] = "231230";
//volatile static int secCounter = 0;

//int timer = 0;
//float rpm = 0.0;
//float rotations = 0.0;

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    //    /* Configure P2.0 and set it to LOW */
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);

    init_HCSR04();
    initMotor();
    initEncoder();

//    initTemp();

    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN7);

//    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
//    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
//    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
//    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableInterrupt(INT_PORT5);

    initWifi();
//    motor_start();
    while (1)
    {
//        initWifi();
//        PCM_gotoLPM0();
    }

//    while (1)
//    {
//        printf("ready.");
//        printf("\nObstacle Distance: %.2f", getHCSR04Distance());
//        if ((getHCSR04Distance() < 15.0))
//        {
//            printf("\nMotor_Stop();");
//            motor_stop();
//                    obstacle = true;
//        }
//    }

//    while (1)
//    {
//        ////        Delay(3000);
////        printf("helloo");
////        printf("\nDistance: %f", getHCSR04Distance());
//        while ((TIMER32_1->RIS & 1) == 0)
//            ; /* wait until the RAW_IFG is set */
//        TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
//        //
////        printf("\nLeft: %s", getLeft());
////        printf("\nRight: %s", getRight());
//        rotations = ((getLeft() + getRight()) / 20) / 2;
//        //
//        rpm = ((float) rotations / (float) timer) * 60.00;
//        timer++;
//        TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
//
//        //        printf("%d\n", timer);
//        printf("\nrpm: %.2f", rpm);
//        //                printf("rotations: %d, timer: %d\n", rotations, timer);
//        //        PCM_gotoLPM0();
//        rpm = 0;
//    }
}

void PORT5_IRQHandler(void)
{
    uint32_t statusLeft = 0;
    uint32_t statusRight = 0;
    uint32_t statusUltra = 0;
    statusLeft = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5) & BIT6;
    statusRight = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5) & BIT7;
    statusUltra = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5) & BIT2;
    GPIO_clearInterruptFlag(GPIO_PORT_P5, statusLeft);
    GPIO_clearInterruptFlag(GPIO_PORT_P5, statusRight);
    GPIO_clearInterruptFlag(GPIO_PORT_P5, statusUltra);

    if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 1
            && GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN7) == 1)
    {
        printf("\n--LINE Detected--");
        motor_stop();
//        printf(getCmdString());
//        obstacle = true;
    }
//    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk; // Disable SLEEPON EXIT
//    __DSB(); // Ensures SLEEPONEXIT is set immediately before exiting ISR
}

void PORT1_IRQHandler(void)
{
    uint32_t statusStart = MAP_GPIO_getEnabledInterruptStatus(
    GPIO_PORT_P1) & BIT1;

    uint32_t statusStop = MAP_GPIO_getEnabledInterruptStatus(
    GPIO_PORT_P1) & BIT4;
//    printf("\n--Hi?--");

    if (statusStart & GPIO_PIN1)
    {
        printf("\n--111--");
        motor_start();
//        initWifi();
    }
    if (statusStop & GPIO_PIN4)
    {
        printf("\n--000--");
        motor_stop();
    }

    GPIO_clearInterruptFlag(GPIO_PORT_P1, statusStart);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, statusStop);
}
