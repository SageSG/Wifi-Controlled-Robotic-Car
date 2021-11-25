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

bool obstacle = false;
int timer = 0;
float rpm = 0.0;
float rotations = 0.0;

//char commandsM[20] = "231230";
volatile static int secCounter = 0;

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

//    init_HCSR04();
//    initMotor();
//    motor_start();
    initWifi();

    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN7);
    Interrupt_enableInterrupt(INT_PORT5);

//    runString(getData());

    while (1)
    {
        printf("\nObstacle Distance: %.2f", getHCSR04Distance());
        if ((getHCSR04Distance() < 15.0))
        {
            printf("\nMotor_Stop();");
            motor_stop();
//                    obstacle = true;
        }
    }
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

    if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 0
            && GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN7) == 0)
    {
        printf("\n--LINE Detected--");
        motor_stop();
//        obstacle = true;
    }

//    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk; // Disable SLEEPON EXIT
//    __DSB(); // Ensures SLEEPONEXIT is set immediately before exiting ISR

}

void runString(char *commandsM)
{
//    motor_start();
    printf(commandsM);
    printf("Oneee");
    size_t length = strlen(commandsM);
    int i = 0;
    printf("Hiiii?");
    for (; i < length && obstacle == false; i++)
    {
//        printf("\nDIstance: %.2f", getHCSR04Distance());
        printf("%c\n", commandsM[i]); /* Print each character of the string. */
//        printf("hellooo?;");
        switch (commandsM[i])
        {
        case '0':
//            printf("\nMotor_Stop();");
            motor_stop();
            while (secCounter < 5)
            {
//                printf("%d", secCounter);
//                printf("\nD2: %.2f", getHCSR04Distance());
//                checkObstacle();
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("stop Car");
            //            Motor_Stop();
            //            Delay(5000);
            break;
        case '1':
            printf("\nMotor_Start();");
            motor_start();
            while (secCounter < 5)
            {
//                printf("\nD2: %.2f", getHCSR04Distance());
//                checkObstacle();
//                if (checkObstacle() == true)
//                {
//                    i = length;
//                }
//                printf("%d", secCounter);
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("Start CAr");
            //            Motor_Start();
            //            Delay(5000);
            break;
        case '2':
            printf("\nMotor_Left();");
            motor_left();
            while (secCounter < 5)
            {
//                printf("%d", secCounter);
//                printf("\nD2: %.2f", getHCSR04Distance());
//                checkObstacle();
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("Left");
            //            Motor_Left();
            //            Delay(5000);
            break;
        case '3':
            printf("\nMotor_Right();");
            motor_right();
            while (secCounter < 5)
            {
//                printf("%d", secCounter);
//                printf("\nD2: %.2f", getHCSR04Distance());
//                checkObstacle();
                counter();
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("Right");
            //            Motor_Right();
            //            Delay(5000);
            break;
        }
    }
    printf("\n--String End--");
}
