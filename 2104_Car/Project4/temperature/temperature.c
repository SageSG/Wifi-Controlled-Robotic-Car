/*
 * temperature.c
 *
 *  Created on: Nov 27, 2021
 *      Author: Jaspzx
 */

#include "temperature.h"

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

void initTemp(void)
{
    /* Halting WDT  */
    WDT_A_holdTimer();
//    Interrupt_enableSleepOnIsrExit();

    /////* for uart_println */////
    // init UART (LSB first, 1 stop bit, no parity, 8-bit characters, 115200 baud)
    P1SEL0 = 0x0c;
    UCA0CTLW0  = UCSWRST | EUSCI_A_CTLW0_SSEL__SMCLK;
    UCA0BRW    = (uint16_t)((uint32_t)3000000 / 115200);
//    UCA0BRW    = (uint16_t)((uint32_t)24000000 / 115200);

    UCA0MCTLW  = 0;
    UCA0CTLW0 &= ~UCSWRST;
    /////* for uart_println */////

    /* Enabling the FPU with stacking enabled (for use within ISR) */
    FPU_enableModule();
    FPU_enableLazyStacking();

    /* Initializing ADC (MCLK/1/1) with temperature sensor routed */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
            ADC_TEMPSENSEMAP);

    /* Configuring ADC Memory (ADC_MEM0 A22 (Temperature Sensor) in repeat
     * mode).
     */
    ADC14_configureSingleSampleMode(ADC_MEM0, true);
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_INTBUF_VREFNEG_VSS,
            ADC_INPUT_A22, false);

    /* Configuring the sample/hold time for 192 */
    ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_192, ADC_PULSE_WIDTH_192);

    /* Enabling sample timer in auto iteration mode and interrupts*/
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    ADC14_enableInterrupt(ADC_INT0);

    /* Setting reference voltage to 2.5 and enabling temperature sensor */
    REF_A_enableTempSensor();
    REF_A_setReferenceVoltage(REF_A_VREF2_5V);
    REF_A_enableReferenceVoltage();

    cal30 = SysCtl_getTempCalibrationConstant(SYSCTL_2_5V_REF,
            SYSCTL_30_DEGREES_C);
    cal85 = SysCtl_getTempCalibrationConstant(SYSCTL_2_5V_REF,
            SYSCTL_85_DEGREES_C);
    calDifference = cal85 - cal30;

    /* Enabling Interrupts */
    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();

    /* Triggering the start of the sample */
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();

    /* Going to sleep */
//    while (1)
//    {
//        PCM_gotoLPM0();
//    }
}

/* This interrupt happens every time a conversion has completed. Since the FPU
 * is enabled in stacking mode, we are able to use the FPU safely to perform
 * efficient floating point arithmetic.*/
//void ADC14_IRQHandler(void)
//{
//    uint64_t status;
//    int16_t conRes;
//
//    status = ADC14_getEnabledInterruptStatus();
//    ADC14_clearInterruptFlag(status);
//
//    if(status & ADC_INT0)
//    {
//        conRes = ((ADC14_getResult(ADC_MEM0) - cal30) * 55);
//        tempC = (conRes / calDifference) + 30.0f;
////        tempF = tempC * 9.0f / 5.0f + 32.0f;
//        uart_println("Temperature(degC): %f", tempC);
//    }
//}
//


