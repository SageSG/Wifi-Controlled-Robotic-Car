/*
 * uart.h
 *
 *  Created on: Nov 20, 2021
 *      Author: jaspz
 */

#ifndef UART_H_
#define UART_H_

void uPrintf(unsigned char *TxArray);

// Reverses a string 'str' of length 'len'
void reverseUart(char *str, int len);

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStrUart(int x, char str[], int d);

// Converts a floating-point/double number to a string.
void ftoaUart(float n, char *res, int afterpoint);

void Uart_Init(void);

#endif /* UART_H_ */
