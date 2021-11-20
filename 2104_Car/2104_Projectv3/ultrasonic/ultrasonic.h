/*
 * ultrasonic.h
 *
 *  Created on: Nov 20, 2021
 *      Author: jaspz
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*
 * ultrasonic.c
 *
 *  Created on: Nov 20, 2021
 *      Author: jaspz
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Include Files */

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MIN_DISTANCE    15.0f
#define TICKPERIOD      1000

uint32_t SR04IntTimes;

static void Delay(uint32_t loop);

void Initalise_HCSR04(void);

static uint32_t getHCSR04Time(void);

float getHCSR04Distance(void);

uint32_t Ultrasonic_Init(void);

#endif /* ULTRASONIC_H_ */
