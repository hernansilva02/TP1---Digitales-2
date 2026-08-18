#include "fsl_common.h"
#include <stdint.h>

volatile uint32_t msTicks = 0;

void Systick_Handler(void) {
    if (msTicks) {
        msTicks--;
    }
}
