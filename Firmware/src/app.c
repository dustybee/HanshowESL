#include "app.h"
#include <stack/ble/ble.h>
#include "tl_common.h"
#include "drivers.h"
#include "app_config.h"
#include "vendor/common/blt_soft_timer.h"
#include "vendor/common/blt_common.h"
#include "led.h"
#include "1.h"
#include "epd.h"

void app_init(void)
{
    led_init();      // LED pins init
    EPD_GPIO_Init(); // EPD GPIO  initialization
    EPD_init();      // EPD init
}

void app(void)
{
    led(1, 500);
    sleep_ms(50);
    led(1, 50);
    sleep_ms(50);
    led(1, 50);

    PIC_display(gImage_BW1, gImage_R1); // Display bitmap image

    led(2, 500);

    EPD_sleep(); // EPD_sleep, Sleep instruction is necessary, please do not delete!

    while (1)
    {
        led(1, 10);
        sleep_ms(2000);
        led(2, 10);
        sleep_ms(2000);
    }
}