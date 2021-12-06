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
#include "../temperature/temperature.h"

#ifndef WIFI_H_
#define WIFI_H_

eUSCI_UART_ConfigV1 UART0Config = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK, 13, 0, 37,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION };

eUSCI_UART_ConfigV1 UART2Config = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK, 13, 0, 37,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION };

//const char *username = "Js";
//const char username[] = "sy";
//const char password[] = "12345678";
//const char *username = "Linksys21487";
//const char *password = "axmpdgh5pr";
const char *username = "AndroidAP542c";
const char *password = "vgar7960";
//
const char url []= "192.168.125.247";

volatile char cmdString[20] = "";
const char PATTERN1 [] = "\"command\": ";
const char PATTERN2 [] = "\}";
char HTTP_Request[] = "GET /controls_controller HTTP/1.1\r\n\r\n";

float temperatureReading;
float distanceReading;
float speedReading;
int lineReading = 0;

bool obstacle = false;
volatile static int secCounter = 0;
int timer = 0;
float rotations = 0.0;
float rpm = 0.0;
float rpmL = 0.0;
float rpmR = 0.0;

void sendData();

void connectWifi();

void receiveData();

void runString();

#endif /* WIFI_H_ */
