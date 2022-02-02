#include "epd_spi.h"
#include "epd.h"
#include "../drivers.h"
#include "../common.h"

void delay_xms(unsigned int xms)
{
	unsigned int i;
	while (xms--)
	{
		i = 12000;
		while (i--)
			;
	}
}

void EPD_W21_Init(void)
{
	gpio_set_func(EPD_RESET_PIN, AS_GPIO);
	gpio_set_output_en(EPD_RESET_PIN, 1);
	gpio_set_input_en(EPD_RESET_PIN, 0);
	gpio_write(EPD_RESET_PIN, 0); // Module reset
	delay_xms(10);				  //At least 10ms delay
	gpio_write(EPD_RESET_PIN, 1);
	delay_xms(10); //At least 10ms delay
}

void EPD_Display(unsigned char *BW_Image, unsigned char *R_Image)
{
	unsigned int Width, Height, i, j;
	Width = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
	Height = EPD_HEIGHT;

	EPD_W21_WriteCMD(0x24);
	for (j = 0; j < Height; j++)
	{
		for (i = 0; i < Width; i++)
		{
			EPD_W21_WriteDATA(BW_Image[i + j * Width]);
		}
	}

	EPD_W21_WriteCMD(0x26);
	for (j = 0; j < Height; j++)
	{
		for (i = 0; i < Width; i++)
		{
			EPD_W21_WriteDATA(~R_Image[i + j * Width]);
		}
	}
	//update
	EPD_W21_WriteCMD(0x22); //Display Update Control
	EPD_W21_WriteDATA(0xF7);
	EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
							// Epaper_READBUSY();
}
//SSD1680
void EPD_init(void)
{
	EPD_W21_Init();

	Epaper_READBUSY();
	EPD_W21_WriteCMD(0x12); //SWRESET
	Epaper_READBUSY();

	EPD_W21_WriteCMD(0x01); //Driver output control
	EPD_W21_WriteDATA(0xF9);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x0F); //0x0F-->(15+1)*8=128

	EPD_W21_WriteCMD(0x45);	 //set Ram-Y address start/end position
	EPD_W21_WriteDATA(0xF9); //0xF9-->(249+1)=250
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);

	EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);

	EPD_W21_WriteCMD(0x21); //  Display update control
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x80);

	EPD_W21_WriteCMD(0x4E); // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F); // set RAM y address count to 0X199;
	EPD_W21_WriteDATA(0xF9);
	EPD_W21_WriteDATA(0x00);
	Epaper_READBUSY();
}
//SSD1680
void EPD_init_GUI(void)
{
	EPD_W21_Init();

	Epaper_READBUSY();
	EPD_W21_WriteCMD(0x12); //SWRESET
	Epaper_READBUSY();

	EPD_W21_WriteCMD(0x01); //Driver output control
	EPD_W21_WriteDATA(0x27);
	EPD_W21_WriteDATA(0x01);
	EPD_W21_WriteDATA(0x01); //Show mirror

	EPD_W21_WriteCMD(0x11); //data entry mode
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x0F); //0x0F-->(15+1)*8=128

	EPD_W21_WriteCMD(0x45);	 //set Ram-Y address start/end position
	EPD_W21_WriteDATA(0x27); //0x0127-->(295+1)=296
	EPD_W21_WriteDATA(0x01);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);

	EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);

	EPD_W21_WriteCMD(0x21); //  Display update control
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x80);

	EPD_W21_WriteCMD(0x4E); // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F); // set RAM y address count to 0X199;
	EPD_W21_WriteDATA(0x27);
	EPD_W21_WriteDATA(0x01);
	Epaper_READBUSY();
}
void EPD_sleep(void)
{
	EPD_W21_WriteCMD(0x10); //enter deep sleep
	EPD_W21_WriteDATA(0x01);
	delay_xms(100);
}

void PIC_display(const unsigned char *BW_datas, const unsigned char *R_datas)
{
	unsigned int i;
	EPD_W21_WriteCMD(0x24); //write RAM for black(0)/white (1)
	for (i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
	{
		EPD_W21_WriteDATA(*BW_datas);
		BW_datas++;
	}
	EPD_W21_WriteCMD(0x26); //write RAM for black(0)/white (1)
	for (i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
	{
		EPD_W21_WriteDATA(~(*R_datas));
		R_datas++;
	}
	//update
	EPD_W21_WriteCMD(0x22); //Display Update Control
	EPD_W21_WriteDATA(0xF7);
	EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
	Epaper_READBUSY();
}
void PIC_display_Clear(void)
{
	unsigned int i;
	EPD_W21_WriteCMD(0x24); //write RAM for black(0)/white (1)
	for (i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
	{
		EPD_W21_WriteDATA(0xff);
	}
	EPD_W21_WriteCMD(0x26); //write RAM for black(0)/white (1)
	for (i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
	{
		EPD_W21_WriteDATA(0x00);
	}
	//update
	EPD_W21_WriteCMD(0x22); //Display Update Control
	EPD_W21_WriteDATA(0xF7);
	EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
	Epaper_READBUSY();
}

void Epaper_READBUSY(void)
{
	while (1)
	{ //=1 BUSY
		if (gpio_read(EPD_BUSY_PIN) == 0)
			break;
	}
}

/***********************************************************
						end file
***********************************************************/
