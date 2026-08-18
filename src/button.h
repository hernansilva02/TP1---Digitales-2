#ifndef BUTTON_H
#define BUTTON_H
#include <stdbool.h>

typedef enum {
    FORMAT_AMPS = 0,
    FORMAT_WATTS,
    FORMAT_COST,
} output_format_t;

#define BUTTON_PORT 0U
#define BUTTON_PIN  5U

void Pint_Config(void);
output_format_t Change_Format(void);
extern volatile bool buttonReady;
extern volatile output_format_t currentFormat;

#endif // BUTTON_H
