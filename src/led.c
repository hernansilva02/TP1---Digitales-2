#include "fsl_gpio.h"
#include "led.h"

void leds_initialize() {
    gpio_pin_config_t config = {
        kGPIO_DigitalOutput,
        1
    };

    GPIO_PortInit(GPIO, LEDS_PORT);

    GPIO_PinInit(GPIO, LEDS_PORT, GREEN_LED_PIN, &config);
    GPIO_PinInit(GPIO, LEDS_PORT, BLUE_LED_PIN, &config);
    GPIO_PinInit(GPIO, LEDS_PORT, RED_LED_PIN, &config);
}

static void leds_on_off(uint8_t pin) {
    switch (pin) {
        case GREEN_LED_PIN:
            GPIO_PinWrite(GPIO, LEDS_PORT, GREEN_LED_PIN, 0U);
            GPIO_PinWrite(GPIO, LEDS_PORT, BLUE_LED_PIN, 1U);
            GPIO_PinWrite(GPIO, LEDS_PORT, RED_LED_PIN, 1U);
            break;
        case BLUE_LED_PIN:
            GPIO_PinWrite(GPIO, LEDS_PORT, BLUE_LED_PIN, 0U);
            GPIO_PinWrite(GPIO, LEDS_PORT, GREEN_LED_PIN, 1U);
            GPIO_PinWrite(GPIO, LEDS_PORT, RED_LED_PIN, 1U);
            break;
        case RED_LED_PIN:
            GPIO_PinWrite(GPIO, LEDS_PORT, RED_LED_PIN, 0U);
            GPIO_PinWrite(GPIO, LEDS_PORT, GREEN_LED_PIN, 1U);
            GPIO_PinWrite(GPIO, LEDS_PORT, BLUE_LED_PIN, 1U);
            break;
        default:
            GPIO_PinWrite(GPIO, LEDS_PORT, RED_LED_PIN, 1U);
            GPIO_PinWrite(GPIO, LEDS_PORT, GREEN_LED_PIN, 1U);
            GPIO_PinWrite(GPIO, LEDS_PORT, BLUE_LED_PIN, 1U);
    }
}

void select_led_on(float amps) {
    if (amps >= 1.5f && amps <= 4.5f) {
        leds_on_off(BLUE_LED_PIN);
    } else if (amps > 4.5f && amps <= 9.75f) {
        leds_on_off(GREEN_LED_PIN);
    } else if(amps > 9.75f) {
        leds_on_off(RED_LED_PIN);
    } else {
        leds_on_off(SMALL_CURRENT);
    }
}
