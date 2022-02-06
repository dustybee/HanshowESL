#include "drivers.h"
#include "led.h"

void led_init() {
	// RED LED init
    gpio_set_func(RED_LED_PIN, AS_GPIO);
    gpio_set_output_en(RED_LED_PIN, 1);
    gpio_set_input_en(RED_LED_PIN, 0);
    // GREEN LED init
    gpio_set_func(GREEN_LED_PIN, AS_GPIO);
    gpio_set_output_en(GREEN_LED_PIN, 1);
    gpio_set_input_en(GREEN_LED_PIN, 0);

    // BLUE LED init
    gpio_set_func(BLUE_LED_PIN, AS_GPIO);
    gpio_set_output_en(BLUE_LED_PIN, 1);
    gpio_set_input_en(BLUE_LED_PIN, 0);

    gpio_write(RED_LED_PIN, 1); 		//RED LED
    gpio_write(GREEN_LED_PIN, 1); 		//GREEN LED
    gpio_write(BLUE_LED_PIN, 1); 		//BLUE LED
}

void led(int led, int duration) {
	switch(led) {
	case 1:
		gpio_write(RED_LED_PIN, 0);
		sleep_ms(duration);
		gpio_write(RED_LED_PIN, 1);
		break;
	case 2:
		gpio_write(GREEN_LED_PIN, 0);
		sleep_ms(duration);
		gpio_write(GREEN_LED_PIN, 1);
		break;
    case 3:
		gpio_write(BLUE_LED_PIN, 0);
		sleep_ms(duration);
		gpio_write(BLUE_LED_PIN, 1);
		break;
    default:
        gpio_write(RED_LED_PIN, 1);
        gpio_write(GREEN_LED_PIN, 1);
        gpio_write(BLUE_LED_PIN, 1);
        break;
	}
}
