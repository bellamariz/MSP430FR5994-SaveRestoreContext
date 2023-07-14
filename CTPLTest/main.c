#include <msp430.h>
#include <ctpl.h>
#include "scheduler.h"

// create tasks

int _system_pre_init(void)
{
    ctpl_init(); // Initialize ctpl library

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    // setupTasks(1, /* task pointers */);

    return 1;
}


/*
 * main.c
 */
int main(void)
{
    while (1) {
        procTasks();
        break;
    }

    return 0;
}
