#include "drivers.h"
#define GREEN_LED_PIN   GPIO_PD3
#define RED_LED_PIN     GPIO_PD2
#define BLUE_LED_PIN    GPIO_PA7

void led_init();
void led(int led, int duration);
