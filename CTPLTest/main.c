#include <msp430.h>
#include <ctpl.h>
#include <stdlib.h>
#include <driverlib.h>
#include "scheduler.h"

unsigned char counter = 0;

void GPIO_init(void) {
//    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
//    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);

    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
}

void counter_led(unsigned char i) {
    if (counter > 7) {
        counter = 0;
    }

    GPIO_setOutputHighOnPin(GPIO_PORT_P3, counter);
    __delay_cycles(100000);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, counter);
    __delay_cycles(200000);

    counter++;
}

int _system_pre_init(void) {
    ctpl_init(); // Initialize ctpl library

    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    setupTasks(1, counter_led);

    GPIO_init();
    PMM_unlockLPM5();

    return 0;
}

/*
 * main.c
 */
int main(void) {
    while (1) {
        postTask(counter_led, 0);

        procTasks();
    }

    return 0;
}
