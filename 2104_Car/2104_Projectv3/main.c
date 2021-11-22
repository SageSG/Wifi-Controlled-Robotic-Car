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

/* Include Files */

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "motor/motor.h"
#include "encoder/encoder.h"
#include "ultrasonic/ultrasonic.h"
#include "uart/uart.h"

//volatile bool car_stop = false;
char commandsM[20] = "123010";
volatile static int secCounter = 0;

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++)
        ;
}

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    //    /* Configure P1.0 and set it to LOW */
    //    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    //    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    //
    //    /* Configure P2.0 and set it to LOW */
    //    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    //    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);

//    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    Initalise_HCSR04();
    Motor_Init();
//    Initalise_HCSR04();
//    Encoder_Init();
//    Ultrasonic_Init();
    Uart_Init();
//        Temp_Init();
//    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//    printf("\nDIstance: %.2f", getHCSR04Distance());

    /* Enabling interrupts and starting the watchdog timer */
    //    Interrupt_enableInterrupt(INT_PORT1);
    //    Interrupt_enableInterrupt(INT_PORT2);
    //    Interrupt_enableInterrupt(INT_PORT3);
    //    Interrupt_enableInterrupt(INT_PORT4);
    Interrupt_enableInterrupt(INT_PORT5);
    //    Interrupt_enableInterrupt(INT_PORT6);
    //    Interrupt_enableSleepOnIsrExit();
    //    Interrupt_enableMaster();
}

void runString()
{
    printf("ONEEEEEE?;");
    size_t length = strlen(commandsM);
    int i = 0;
    for (; i < length; i++)
    {
        printf("%c\n", commandsM[i]); /* Print each character of the string. */
        printf("hellooo?;");
        switch (commandsM[i])
        {
        case '0':
            printf("Motor_Stop();");
            Motor_Stop();
            while (secCounter < 3)
            {
                printf("%d", secCounter);
                //        ===============================================================================
                TIMER32_1->LOAD = 3000000; /* set the reload value */
                //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);

                /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
                TIMER32_1->CONTROL = 0xC3;
                //    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
                //                           TIMER32_FREE_RUN_MODE);
                while ((TIMER32_1->RIS & 1) == 0)
                    ; /* wait until the RAW_IFG is set */
                TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
                ////        P2->OUT ^= 4; /* toggle blue LED */
                ////        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
                //        ===============================================================================
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("stop Car");
            //            Motor_Stop();
            //            Delay(5000);
            break;
        case '1':
            printf("Motor_Start();");
            Motor_Start();
            while (secCounter < 3)
            {
                printf("%d", secCounter);
                //        ===============================================================================
                TIMER32_1->LOAD = 3000000; /* set the reload value */
                //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);

                /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
                TIMER32_1->CONTROL = 0xC3;
                //    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
                //                           TIMER32_FREE_RUN_MODE);
                while ((TIMER32_1->RIS & 1) == 0)
                    ; /* wait until the RAW_IFG is set */
                TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
                ////        P2->OUT ^= 4; /* toggle blue LED */
                ////        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
                //        ===============================================================================
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("Start CAr");
            //            Motor_Start();
            //            Delay(5000);
            break;
        case '2':
            printf("Motor_Left();");
            Motor_Left();
            while (secCounter < 3)
            {
                printf("%d", secCounter);
                //        ===============================================================================
                TIMER32_1->LOAD = 3000000; /* set the reload value */
                //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);

                /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
                TIMER32_1->CONTROL = 0xC3;
                //    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
                //                           TIMER32_FREE_RUN_MODE);
                while ((TIMER32_1->RIS & 1) == 0)
                    ; /* wait until the RAW_IFG is set */
                TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
                ////        P2->OUT ^= 4; /* toggle blue LED */
                ////        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
                //        ===============================================================================
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("Left");
            //            Motor_Left();
            //            Delay(5000);
            break;
        case '3':
            printf("Motor_Right();");
            Motor_Right();
            while (secCounter < 3)
            {
                printf("%d", secCounter);
                //        ===============================================================================
                TIMER32_1->LOAD = 3000000; /* set the reload value */
                //    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);

                /* no prescaler, one-shot mode, disable interrupt, 32-bit timer. */
                TIMER32_1->CONTROL = 0xC3;
                //    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
                //                           TIMER32_FREE_RUN_MODE);
                while ((TIMER32_1->RIS & 1) == 0)
                    ; /* wait until the RAW_IFG is set */
                TIMER32_1->INTCLR = 0; /* clear raw interrupt flag */
                ////        P2->OUT ^= 4; /* toggle blue LED */
                ////        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                TIMER32_1->LOAD = 3000000; /* reload LOAD register to restart one-shot */
                //        ===============================================================================
                secCounter += 1;
            }
            secCounter = 0;
            //            printf("Right");
            //            Motor_Right();
            //            Delay(5000);
            break;
        }
    }
}
