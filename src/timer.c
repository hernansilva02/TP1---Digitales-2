#include "timer.h"

static volatile uint32_t msTicks = 5000;
volatile bool TimerReady = false;

void SysTick_Handler(void) {
    if (msTicks > 0U) {
        msTicks--;
        if (msTicks == 0 ) {
            TimerReady = true;
        }
    }
}

void Report_Interval_Act(uint32_t interval) {
    msTicks = interval;
}

/* Not Needed
void SysDelay(uint32_t delay) {
    msTicks = delay;
    if (TimerReady) {

    }
}
*/
