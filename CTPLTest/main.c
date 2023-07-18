#include <msp430.h>
#include <ctpl.h>
#include <stdlib.h>
#include <driverlib.h>
#include "scheduler.h"

void GPIO_init(void);
void UART_init(void);

void GPIO_init(void) {
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P6,
        GPIO_PIN0,
        GPIO_SECONDARY_MODULE_FUNCTION
        );
}


void UART_init() {
    // Configure UART
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 3;
    param.firstModReg = 0;
    param.secondModReg = 92;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param)) {
        return;
    }

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
}

int cmpfunc(const void* a, const void* b) {
   return *(int*)a - *(int*)b;
}

void blink_led10(int blink_count) {
    unsigned char i;
    for (i = 0; i < blink_count; i++) {
        __delay_cycles(200000);
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        __delay_cycles(100000);
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        __delay_cycles(100000);
    }
}

void blink_led11(int blink_count) {
    unsigned char i;
    for (i = 0; i < blink_count; i++) {
        __delay_cycles(200000);
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN1);
        __delay_cycles(100000);
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN1);
        __delay_cycles(100000);
    }
}

// create tasks
void sort_array_green(unsigned char blink_count) {
    int a[25] = {1, 5, 2, 6, 12, 31, 87, 54, 112, 74, 53, 4, 101, 9, 121, 63, 64, 147, 12, 93, 23, 12, 1, 12, 7};

    qsort(a, 25, sizeof(int), cmpfunc);

    blink_led11(blink_count);
}

// sorts an array and blinks led once
void sort_array_red(unsigned char blink_count) {
    int a[25] = {1, 5, 2, 6, 12, 31, 87, 54, 112, 74, 53, 4, 101, 9, 121, 63, 64, 147, 12, 93, 23, 12, 1, 12, 7};

    qsort(a, 25, sizeof(int), cmpfunc);

    // blinks led
    blink_led10(blink_count);
}

void green_red(unsigned char blink_count) {
    blink_led10(5);
    blink_led11(3);
}

int _system_pre_init(void) {
    ctpl_init(); // Initialize ctpl library

    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    setupTasks(1, sort_array_red, sort_array_green, green_red);

    GPIO_init();
    UART_init();

    PMM_unlockLPM5();

    return 0;
}

/*
 * main.c
 */
int main(void) {
    unsigned int counter = 0;
    while (1) {
        postTask(sort_array_red, 2);
        postTask(sort_array_green, 5);
        postTask(green_red, 3);

        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, counter);
        counter++;

        procTasks();
    }

    return 0;
}
