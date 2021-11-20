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
//char commands[20] = "01230";

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

    Motor_Init();
    Encoder_Init();
//    Ultrasonic_Init();
    Uart_Init();
//        Temp_Init();

//    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN6);
//    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN7);

//    size_t length = strlen(commands);
//    int i = 0;
//    for (; i < length; i++)
//    {
//        printf("%c\n", commands[i]); /* Print each character of the string. */
//        switch (commands[i])
//        {
//        case '0':
//            printf("stop Car");
//            break;
//        case '1':
//            printf("Start CAr");
//            break;
//        case '2':
//            printf("Left");
//            break;
//        case '3':
//            printf("Right");
//            break;
//        }
//    }

    /* Enabling interrupts and starting the watchdog timer */
    //    Interrupt_enableInterrupt(INT_PORT1);
    //    Interrupt_enableInterrupt(INT_PORT2);
    //    Interrupt_enableInterrupt(INT_PORT3);
    //    Interrupt_enableInterrupt(INT_PORT4);
        Interrupt_enableInterrupt(INT_PORT5);
    //    Interrupt_enableInterrupt(INT_PORT6);
    //    Interrupt_enableSleepOnIsrExit();
    //    Interrupt_enableMaster();
    while (1)
    {
//        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 0)
//        {
//            printf("\nLINE DECTECTED");
//        }
//        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN7) == 0)
//        {
//            printf("\nHello2");
//        }
        //        PCM_gotoLPM0();
        //        PCM_gotoLPM3();
    }
}
