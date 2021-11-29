/*
 * motor.h
 *
 *  Created on: Nov 25, 2021
 *      Author: Jaspzx
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdio.h>
#include <string.h>

#ifndef MOTOR_H_
#define MOTOR_H_

//int up = 8000;
//int down =
volatile static int secCounterM = 0;
static void Delay(uint32_t loop);

void adjustLeft();

void adjustRight();

void initMotor(void);

void motor_stop(void);

void oneEighty(void);

void motor_back(void);

void motor_start(void);

void motor_left(void);

void motor_right(void);

#endif /* MOTOR_H_ */
