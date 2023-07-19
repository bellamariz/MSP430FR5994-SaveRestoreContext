#include <msp430.h>
#include <ctpl.h>
#include <stdlib.h>
#include <driverlib.h>
#include "scheduler.h"

//volatile unsigned int counter = 0;

void GPIO_init(void);
//void UART_init(void);
//void XT1_init(void);

void GPIO_init(void) {
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
//    P6SEL1 &= ~(0x0000 | 0x0000);               // USCI_A3 UART operation
//    P6SEL0 |= (0x0001 | 0x0000);                // USCI_A3 UART operation
//    PJSEL0 |= BIT4 | BIT5;                  // Configure XT1 pins
}


//void UART_init() {
//    // Configure USCI_A3 for UART mode
//    UCA3CTLW0 |= UCSWRST;
//    UCA3CTLW0 |= UCSSEL__ACLK;                // Set ACLK = 32768 as UCBRCLK
//    UCA3BRW = 3;                            // 9600 baud
//    UCA3MCTLW |= 0x5300;                    // 32768/9600 - INT(32768/9600)=0.41
//                                            // UCBRSx value = 0x53 (See UG)
//    UCA3CTLW0 &= ~UCSWRST;                   // release from reset
//}
//
//void XT1_init() {
//    // XT1 Setup
//    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
//    CSCTL1 = DCOFSEL_0;                     // Set DCO to 1MHz
//    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
//    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;   // Set all dividers
//    CSCTL4 &= ~LFXTOFF;                     // Enable LFXT1
//    do
//    {
//        CSCTL5 &= ~LFXTOFFG;                // Clear XT1 fault flag
//        SFRIFG1 &= ~OFIFG;
//    } while (SFRIFG1 & OFIFG);              // Test oscillator fault flag
//    CSCTL0_H = 0;                           // Lock CS registers
//}

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
    PMM_unlockLPM5();
//    XT1_init(); // needs to be after unlockLPM5
//    UART_init();

    return 0;
}

/*
 * main.c
 */
int main(void) {
//    volatile unsigned int counter = 46;
    while (1) {
        postTask(sort_array_red, 2);
        postTask(sort_array_green, 5);
        postTask(green_red, 3);

        // while(!(UCA3IFG & UCRXIFG));
//        UCA3TXBUF = counter;                 // Load data onto buffer

        procTasks();
    }

    return 0;
}
