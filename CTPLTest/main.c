#include <msp430.h>
#include <ctpl.h>
#include <stdlib.h>
#include <driverlib.h>
#include "scheduler.h"

volatile unsigned int a;

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
void sort_array_green(void) {
    int a[25] = {1, 5, 2, 6, 12, 31, 87, 54, 112, 74, 53, 4, 101, 9, 121, 63, 64, 147, 12, 93, 23, 12, 1, 12, 7};

    qsort(a, 25, sizeof(int), cmpfunc);

    blink_led11(2);
    // ctpl_enterShutdown(CTPL_SHUTDOWN_TIMEOUT_64_MS);
}

// sorts an array and blinks led once
void sort_array_red(void) {
    int a[25] = {1, 5, 2, 6, 12, 31, 87, 54, 112, 74, 53, 4, 101, 9, 121, 63, 64, 147, 12, 93, 23, 12, 1, 12, 7};

    qsort(a, 25, sizeof(int), cmpfunc);

    // blinks led
    blink_led10(1);
    // ctpl_enterShutdown(CTPL_SHUTDOWN_TIMEOUT_64_MS);
}

int _system_pre_init(void) {
    ctpl_init(); // Initialize ctpl library

    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    setupTasks(1, sort_array_red, sort_array_green);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);

    PMM_unlockLPM5();

    return 0;
}

/*
 * main.c
 */
int main(void) {
    a = 0;
    unsigned int* p = &a;

    while ((a++) < 10) {
        blink_led11(a);
        postTask(sort_array_red, 2);
        // postTask(sort_array_green, 5);

        procTasks();
        ctpl_enterLpm45(CTPL_ENABLE_RESTORE_ON_RESET);
    }

    return 0;
}
