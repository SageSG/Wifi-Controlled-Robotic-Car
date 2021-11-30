/*
 * ultrasonic.h
 *
 *  Created on: Nov 26, 2021
 *      Author: Jaspzx
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define MIN_DISTANCE    15.0f
#define TICKPERIOD      1000

uint32_t SR04IntTimes;

void init_HCSR04(void);

static uint32_t getHCSR04Time(void);

float getHCSR04Distance(void);

#endif /* ULTRASONIC_H_ */
