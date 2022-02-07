/********************************************************************************************************
 * @file     app.c
 *
 *
 * @par      User file for system initialization, data processing and low power management.
 *           
 *******************************************************************************************************/

#include "app.h"

// Telink
#include "tl_common.h"
#include "drivers.h"
#include "app_config.h"

// BLE 
#include <stack/ble/ble.h>
#include "vendor/common/blt_common.h"
#include "vendor/common/blt_soft_timer.h"

// App
#include "led.h"
#include "1.h"
#include "epd.h"

void user_init_normal(void)
{
    led_init();      // LED pins init
    EPD_GPIO_Init(); // EPD GPIO  initialization
    EPD_init();      // EPD init
    ble_init_normal();  // BLE init
}

void app(void)
{
    
    // led(1, 500);
    // led(1, 50);
    // sleep_ms(50);
    // led(1, 50);

    // PIC_display(gImage_BW1, gImage_R1); // Display bitmap image

    // led(2, 500);

    // EPD_sleep(); // EPD_sleep, Sleep instruction is necessary, please do not delete!

    blt_sdk_main_loop(); // BLE logic and data processing
}

