# MSP430FR5994-SaveRestoreContext

Work developed for the undergraduate final project.

The final project implementation software is the folder **CTPLTest**.

This repository features the following Code Composer Studio projects:

1) ctpl_ex4_adc12_b_monitor_msp-exp430fr5994 -> Texas Instruments example project for the CTPL API using ADC readings to trigger the API call when a power loss occurs.
2) **CTLPTest** -> Task-based test program that uses a scheduler to process the tasks and calls the CTPL library after each task is executed to save its context.
3) CTPLTestADC -> An improved version of CTPLTest that uses ADC readings after every task to trigger the CTPL library. Work in progress!!!!
4) SaveContext -> Copy of another repository, it was an attempt at a save-restore application context library based on Hibernus++, before using CTPL.
