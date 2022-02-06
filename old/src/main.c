#include "../drivers.h"
#include "../SSD1680_EPD/epd.h"
#include "../SSD1680_EPD/epd_spi.h"
#include "led.h"
#include "1.h"

//unsigned char BW_Image[4000]; 	//Define canvas space
//unsigned char R_Image[4000];  	//Define canvas space

int main(void)
{
    blc_pm_select_internal_32k_crystal();
    cpu_wakeup_init();
    clock_init(SYS_CLK_24M_Crystal);

    led_init();						//LED pins init
    EPD_GPIO_Init();                //EPD GPIO  initialization
    EPD_init();                     //EPD init

    led(1, 500);
    sleep_ms(50);
    led(1, 50);
    sleep_ms(50);
    led(1, 50);

    PIC_display(gImage_BW1, gImage_R1); // Display bitmap image

    led(2, 500);

    EPD_sleep();                    	//EPD_sleep, Sleep instruction is necessary, please do not delete!

    while(1) {
        led(1, 10);
        sleep_ms(2000);
        led(2, 10);
        sleep_ms(2000);
    }
}
