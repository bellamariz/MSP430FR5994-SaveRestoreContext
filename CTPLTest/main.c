#include <msp430.h>
#include <ctpl.h>

int _system_pre_init(void) {
    ctpl_init();
    return 1;
}

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    int counter = 0;

    while (1) {
        if ((counter % 10000) == 0) {
            // turn on led
        }
    }

    return 0;
}
