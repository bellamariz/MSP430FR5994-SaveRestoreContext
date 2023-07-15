#include <msp430.h>
#include <ctpl.h>
#include <stdlib.h>
#include <driverlib.h>
#include "scheduler.h"

int cmpfunc(const void* a, const void* b) {
   return *(int*)a - *(int*)b;
}

void blink_led(int blink_count) {
    unsigned char i;
    for (i = 0; i < blink_count; i++) {
        __delay_cycles(200000);
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        __delay_cycles(100000);
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        __delay_cycles(100000);
    }
}

// create tasks
// sorts an array and blinks led once
void sort_array(void) {
    int a[25] = {1, 5, 2, 6, 12, 31, 87, 54, 112, 74, 53, 4, 101, 9, 121, 63, 64, 147, 12, 93, 23, 12, 1, 12, 7};

    qsort(a, 25, sizeof(int), cmpfunc);

    // blinks led
    blink_led(1);

    ctpl_enterShutdown(CTPL_SHUTDOWN_TIMEOUT_64_MS);
}

void test(void) {
    blink_led(2);
    ctpl_enterShutdown(CTPL_SHUTDOWN_TIMEOUT_64_MS);
}

int _system_pre_init(void) {
    ctpl_init(); // Initialize ctpl library

    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    setupTasks(1, sort_array, test);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    PMM_unlockLPM5();

    return 0;
}

/*
 * main.c
 */
int main(void) {
    unsigned long long a = 0;

    while (a++ < 100000) {
        postTask(sort_array, 2);
        __delay_cycles(400000);
        postTask(test, 34);

        procTasks();
    }

    // sort_array();

    return 0;
}
