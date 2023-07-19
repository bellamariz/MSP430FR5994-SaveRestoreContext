#include <msp430.h>
#include <ctpl.h>
#include <driverlib.h>
#include "scheduler.h"

// Global counter variable
unsigned char counter = 0;

// Initializes GPIO of PORT3 to PIN0, PIN1 and PIN2 to be output
void GPIO_init(void) {
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
}

// Writes on the PORT3 pins the value of the counter
void counter_led(void) {
    // Maximum value of counter can be 7 (3 led pins)
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

    setupTasks(1, counter_led); // Setup task for blinking led based on counter

    GPIO_init(); // Initialize GPIO pins for blinking led
    PMM_unlockLPM5(); // Put into effect the GPIO change

    return 0;
}

/*
 * main.c
 */
int main(void) {
    while (1) {
        postTask(counter_led); // Posts counter_led task to be executed

        procTasks(); // Looks for tasks to be executed
    }

    return 0;
}
