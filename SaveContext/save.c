#include <stdlib.h>
#include <stdio.h>

//FRAM_REG_START 0x10000

void SaveRegisters(void){
    // Because registers are 20 bits, we allocate them every 32 bits (4 bytes) in-memory
    asm (" MOVA R2, &0x10000 ");
    asm (" MOVA R4, &0x10004 ");
    asm (" MOVA R5, &0x10008 ");
    asm (" MOVA R6, &0x1000C ");
    asm (" MOVA R7, &0x10010 ");
    asm (" MOVA R8, &0x10014 ");
    asm (" MOVA R9, &0x10018 ");
    asm (" MOVA R10, &0x1001C ");
    asm (" MOVA R11, &0x10020 ");
    asm (" MOVA R12, &0x10024 ");
    asm (" MOVA R13, &0x10028 ");
    asm (" MOVA R14, &0x1002C ");
    asm (" MOVA R15, &0x10030 ");
//    // saves R0/PC
//    asm (" MOVA 0(R1), R12 ");
//    asm (" MOVA R12, &0x10034 ");
//    // saves R1/SP
//    asm (" MOVA R1, R12 ");
//    asm (" ADDA #4, R12 ");
//    asm (" MOVA R12, &0x10038 ");
}

void RestoreRegisters(void){
    asm(" NOP ");
    asm (" MOV.W &0x10002, R2");
    asm(" NOP ");
    asm (" MOVA &0x10004, R4");
    asm (" MOVA &0x10008, R5");
    asm (" MOVA &0x1000C, R6");
    asm (" MOVA &0x10010, R7");
    asm (" MOVA &0x10014, R8");
    asm (" MOVA &0x10018, R9");
    asm (" MOVA &0x1001C, R10");
    asm (" MOVA &0x10020, R11");
    asm (" MOVA &0x10024, R12");
    asm (" MOVA &0x10028, R13");
    asm (" MOVA &0x1002C, R14");
    asm (" MOVA &0x10030, R15");
}
