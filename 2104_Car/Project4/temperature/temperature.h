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

inline void uart_println(const char* str, ...)
{
    static char print_buffer[256];
    va_list lst;
    va_start(lst, str);
    vsnprintf(print_buffer, 256, str, lst);
    str = print_buffer;
    while (*str)
    {
        while (!(UCA0IFG & EUSCI_A_IFG_TXIFG));
        UCA0TXBUF = *str;
        str++;
    }
    while (!(UCA0IFG & EUSCI_A_IFG_TXIFG));
    UCA0TXBUF = '\r';
    while (!(UCA0IFG & EUSCI_A_IFG_TXIFG));
    UCA0TXBUF = '\n';
}

int initTemp(void);


#endif /* TEMPERATURE_TEMPERATURE_H_ */
