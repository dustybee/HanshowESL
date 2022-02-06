#include "epd_spi.h"
#include "drivers.h"
#include "tl_common.h"

void EPD_GPIO_Init(void)
{
	//reset pin configuration
	gpio_set_func(EPD_RESET_PIN, AS_GPIO);
	gpio_set_output_en(EPD_RESET_PIN, 1);
	gpio_set_input_en(EPD_RESET_PIN, 0);
	gpio_write(EPD_RESET_PIN, 0);
	//BS1 pin configuration
	//select 4-lines SPI interface
	//EPD power supply control pin configuration
	gpio_set_func(EPD_PWR_CTRL_PIN, AS_GPIO);
	gpio_set_output_en(EPD_PWR_CTRL_PIN, 1);
	gpio_set_input_en(EPD_PWR_CTRL_PIN, 0);
	gpio_write(EPD_PWR_CTRL_PIN, 0);
	//EPD Data/Command control pin configuration
	gpio_set_func(EPD_DC_PIN, AS_GPIO);
	gpio_set_output_en(EPD_DC_PIN, 1);
	gpio_set_input_en(EPD_DC_PIN, 0);
	gpio_write(EPD_DC_PIN, 0);
	//EPD Busy Status pin configuratioin
	gpio_set_func(EPD_BUSY_PIN, AS_GPIO);
	gpio_set_output_en(EPD_BUSY_PIN, 0);
	gpio_set_input_en(EPD_BUSY_PIN, 1);
	// gpio_setup_up_down_resistor(EPD_BUSY_PIN, PM_PIN_PULLUP_1M);

	//cs pin configuration
	gpio_set_func(EPD_SPI_CS_PIN, AS_GPIO);
	gpio_set_output_en(EPD_SPI_CS_PIN, 1);
	gpio_set_input_en(EPD_SPI_CS_PIN, 0);
	gpio_write(EPD_SPI_CS_PIN, 1);
	//clk pin configuration
	gpio_set_func(EPD_SPI_CK_PIN, AS_GPIO);
	gpio_set_output_en(EPD_SPI_CK_PIN, 1);
	gpio_set_input_en(EPD_SPI_CK_PIN, 0);
	gpio_write(EPD_SPI_CK_PIN, 0);
	//DO pin configuration
	gpio_set_func(EPD_SPI_DO_PIN, AS_GPIO);
	gpio_set_output_en(EPD_SPI_DO_PIN, 1);
	gpio_set_input_en(EPD_SPI_DO_PIN, 0);
	gpio_write(EPD_SPI_DO_PIN, 1);
}

void SPI_Write(unsigned char value)
{
	unsigned char i;

	for (i = 0; i < 8; i++)
	{
		gpio_write(EPD_SPI_CK_PIN, 0);
		if (value & 0x80)
			gpio_write(EPD_SPI_DO_PIN, 1);
		else
			gpio_write(EPD_SPI_DO_PIN, 0);
		value = (value << 1);
		gpio_write(EPD_SPI_CK_PIN, 1);
	}
}

void EPD_W21_WriteCMD(unsigned char command)
{
	gpio_write(EPD_SPI_CS_PIN, 0);
	gpio_write(EPD_DC_PIN, 0); // command write
	SPI_Write(command);
	gpio_write(EPD_SPI_CS_PIN, 1);
}
void EPD_W21_WriteDATA(unsigned char data)
{
	gpio_write(EPD_SPI_CS_PIN, 0);
	gpio_write(EPD_DC_PIN, 1); // data write
	SPI_Write(data);
	gpio_write(EPD_SPI_CS_PIN, 1);
}

/***********************************************************
						end file
***********************************************************/
