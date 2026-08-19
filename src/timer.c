#include "timer.h"
#include "fsl_adc.h"

static volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
    if (msTicks != 0U) {
        msTicks--;
    }
}

void SysDelay(uint32_t delay) {
    msTicks = delay;
    while (msTicks != 0U);
}
