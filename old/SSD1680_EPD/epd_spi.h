#ifndef _DISPLAY_EPD_W21_SPI_
#define _DISPLAY_EPD_W21_SPI_

#define EPD_SPI_CS_PIN	 	GPIO_PB4
#define EPD_SPI_CK_PIN 		GPIO_PB5
#define EPD_SPI_DO_PIN 		GPIO_PB6
#define EPD_RESET_PIN 		GPIO_PD4
#define EPD_PWR_CTRL_PIN 	GPIO_PC5
#define EPD_BUSY_PIN 		GPIO_PA1
#define EPD_DC_PIN 			GPIO_PD7


void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char data);
void EPD_W21_WriteCMD(unsigned char command);
void EPD_GPIO_Init(void);

#endif  //#ifndef _MCU_SPI_H_

/***********************************************************
						end file
***********************************************************/
