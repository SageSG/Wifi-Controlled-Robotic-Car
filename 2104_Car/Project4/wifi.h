/*
 * wifi.h
 *
 *  Created on: Nov 26, 2021
 *      Author: Jaspzx
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <UART_Driver.h>
#include <MSPIO.h>
#include <ESP8266.h>
#include <stdio.h>
#include <string.h>

#include "motor/motor.h"

#ifndef WIFI_H_
#define WIFI_H_

int count;
const char *username = "Xperia5II";
const char *password = "mango12345";
//const char *username = "AndroidAP542c";
//const char *password = "vgar7960";

const char *url = "192.168.40.247";
char cmdString[20] = "";

const char *PATTERN1 = "\"command\": \"";
const char *PATTERN2 = "\"";
//char HTTP_Request[] = "GET /car/commands HTTP/1.1\r\n\r\n";
char HTTP_Request[] = "GET /car/test HTTP/1.1\r\n\r\n";

void initWifi();

bool getData(char *s);

#endif /* WIFI_H_ */
