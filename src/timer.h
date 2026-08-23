#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#include <stdbool.h>

extern volatile bool TimerReady;

void Report_Interval_Act(uint32_t interval);

// void SysDelay(uint32_t delay);
#endif // TIMER_H
