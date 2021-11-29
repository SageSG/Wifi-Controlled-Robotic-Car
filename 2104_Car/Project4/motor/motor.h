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

static void Delay(uint32_t loop);

void initMotor(void);

void motor_stop(void);

void motor_start(void);

void motor_left(void);

void motor_right(void);

#endif /* MOTOR_H_ */
