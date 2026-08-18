#ifndef MY_LEDS_H
#define MY_LEDS_H 
#include <stdint.h>

#define LEDS_PORT     1U
#define GREEN_LED_PIN 0U
#define BLUE_LED_PIN  1U
#define RED_LED_PIN   2U
#define SMALL_CURRENT 3U


void leds_initialize();
void select_led_on(float amps);
#endif // MY_LEDS_H
