#include <stdio.h>
#include <msp430.h> 
#include "save.h"

//int _system_pre_init(void)
//{
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
//    PM5CTL0 &= ~LOCKLPM5;
//
//    // Configure MPU
//    MPUCTL0 = MPUPW; // Write PWD to access MPU registers
//    MPUSEGB1 = 0x1000; // B1 = 0x10000; B2 = 0x12C00
//    MPUSEGB2 = 0x12C0; // Borders are assigned to segments
//
//    // Segment 1 – Allows read and write only
//    // Segment 2 – Allows read only
//    // Segment 3 – Allows read and execute only
//    MPUSAM = (MPUSEG1WE | MPUSEG1RE | MPUSEG2RE | MPUSEG3RE | MPUSEG3XE);
//    MPUCTL0 = MPUPW | MPUENA | MPUSEGIE; // Enable MPU protection
//    // MPU registers locked until BOR
//
//    /*==================================*/
//    /* Choose if segment initialization */
//    /* should be done or not. */
//    /* Return: 0 to omit initialization */
//    /* 1 to run initialization */
//    /*==================================*/
//    return 1;
//}

/**
 * hello.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

	SaveRegisters();

//  unsigned long our_fram_start = 0x10000;

//  printf("%d\n", *((unsigned int*)our_fram_start));
	
//	RestoreRegisters();

	return 0;
}
