#include <msp430.h>
#include <ctpl.h>
#include <stdlib.h>
#include <driverlib.h>
#include "scheduler.h"

#define ADC_MONITOR_THRESHOLD   3.0

void ADC_init(void) {
    ADC12_B_initParam initParam = {0};
    initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_SC;
    initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_ADC12OSC;
    initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
    initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
    initParam.internalChannelMap = ADC12_B_MAPINTCH0;
    ADC12_B_init(ADC12_B_BASE, &initParam);
    //Enable the ADC12_B module
    ADC12_B_enable(ADC12_B_BASE);

    /*
    * Base address of ADC12 Module
    * For memory buffers 0-7 sample/hold for 16 clock cycles
    * For memory buffers 8-15 sample/hold for 4 clock cycles (default)
    * Disable Multiple Sampling
    */
    ADC12_B_setupSamplingTimer(ADC12_B_BASE,
                               ADC12_B_CYCLEHOLD_16_CYCLES,
                               ADC12_B_CYCLEHOLD_4_CYCLES,
                               ADC12_B_MULTIPLESAMPLESDISABLE);

    //Configure Memory Buffer
    /*
    * Base address of the ADC12 Module
    * Configure memory buffer 0
    * Map input A0 to memory buffer 0
    * Vref+ = AVcc
    * Vref- = EXT Positive
    * Memory buffer 0 is not the end of a sequence
    */
    ADC12_B_configureMemoryParam configureMemoryParam = {0};
    configureMemoryParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
    configureMemoryParam.inputSourceSelect = ADC12_B_INPUT_A0;
    configureMemoryParam.refVoltageSourceSelect = ADC12_B_VREFPOS_EXTPOS_VREFNEG_VSS;
    configureMemoryParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
    configureMemoryParam.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_ENABLE;
    configureMemoryParam.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    ADC12_B_configureMemory(ADC12_B_BASE, &configureMemoryParam);

    ADC12_B_setWindowCompAdvanced(ADC12_B_BASE,
                                  (uint16_t)(4096*((ADC_MONITOR_THRESHOLD+0.1)/2)/(2.0)),
                                  (uint16_t)(4096*(ADC_MONITOR_THRESHOLD/2)/(2.0)));

    ADC12_B_enableInterrupt(ADC12_B_BASE,
          0,
          0,
          ADC12_B_HIIE);
}

void GPIO_init(void) {
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0 + GPIO_PIN1);
}

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

    /* Enable global interrupts. */
    __enable_interrupt();

    ADC_init();
    GPIO_init();
    PMM_unlockLPM5();

    return 0;
}

/*
 * main.c
 */
int main(void) {
    while (1) {
        postTask(sort_array_red, 2);
        postTask(sort_array_green, 5);
        postTask(green_red, 3);

        //Enable/Start sampling and conversion
        /*
         * Base address of ADC12B Module
         * Start the conversion into memory buffer 0
         * Use the single-channel, single-conversion mode
         */
        ADC12_B_startConversion(ADC12_B_BASE,
           ADC12_B_MEMORY_0,
           ADC12_B_SINGLECHANNEL);

        while (ADC12_B_isBusy(ADC12_B_BASE));

        procTasks();
    }

    return 0;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    switch(__even_in_range(ADC12IV, ADC12IV_ADC12LOIFG)) {
        case ADC12IV_NONE:        break;        // Vector  0: No interrupt
        case ADC12IV_ADC12OVIFG:  break;        // Vector  2: ADC12MEMx Overflow
        case ADC12IV_ADC12TOVIFG: break;        // Vector  4: Conversion time overflow
        case ADC12IV_ADC12HIIFG:                // Vector  6: Window comparator high side
            /* Disable the high side and enable the low side interrupt. */
            ADC12_B_clearInterrupt(ADC12_B_BASE,
                                   2,
                                   ADC12_B_HIIFG);

            ADC12_B_enableInterrupt(ADC12_B_BASE,
                                  0,
                                  0,
                                  ADC12_B_LOIE);

            break;
        case ADC12IV_ADC12LOIFG:                // Vector  8: Window comparator low side
            /* Enter device shutdown with 64ms timeout. */
            ctpl_enterShutdown(CTPL_SHUTDOWN_TIMEOUT_64_MS);

            /* Disable the low side and enable the high side interrupt. */
            ADC12_B_clearInterrupt(ADC12_B_BASE,
                                   2,
                                   ADC12_B_LOIFG);

            ADC12_B_enableInterrupt(ADC12_B_BASE,
                                    0,
                                    0,
                                    ADC12_B_HIIE);

            break;
        default: break;
    }
}
