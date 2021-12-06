/*
 * temperature.h
 *
 *  Created on: Nov 27, 2021
 *      Author: Jaspzx
 */

#ifndef TEMPERATURE_TEMPERATURE_H_
#define TEMPERATURE_TEMPERATURE_H_
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <UART_Driver.h>
#include <MSPIO.h>
#include <ESP8266.h>
#include <stdio.h>
#include <string.h>

uint32_t cal30;
uint32_t cal85;
float calDifference;
float tempC;
float tempF;
int16_t conRes;

inline void uart_println(const char* str, ...);

void initTemp(void);


#endif /* TEMPERATURE_TEMPERATURE_H_ */
