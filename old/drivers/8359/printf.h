
/********************************************************************************************************
 * @file     printf.h 
 *
 * @brief    This is the header file for TLSR8258
 *
 * @author	 Driver Group
 * @date     May 8, 2018
 *
 * @par      Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *           The information contained herein is confidential property of Telink
 *           Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *           of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *           Co., Ltd. and the licensee or the terms described here-in. This heading
 *           MUST NOT be removed from this file.
 *
 *           Licensees are granted free, non-transferable use of the information in this
 *           file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 * @par      History:
 * 			 1.initial release(DEC. 26 2018)
 *
 * @version  A001
 *         
 *******************************************************************************************************/
#include "gpio.h"
#pragma once

#define DEBUG_MODE 1

#if(DEBUG_MODE)

#define  DEBUG_IO		1
#define  DEBUG_USB		2

#define  DEBUG_BUS  	1

#if (DEBUG_BUS==DEBUG_USB)
/**
 * @brief      This function serves to printf string by USB.
 * @param[in]  *format  -  format string need to print
 * @param[in]  ...   	-  variable number of data
 * @return     none.
 */
void usb_printf(const char *format, ...);
#define  printf		usb_printf
#elif (DEBUG_BUS==DEBUG_IO)
#define PRINT_BAUD_RATE             		115200  	//1M baud rate,should Not bigger than 1Mb/s
#define DEBUG_INFO_TX_PIN           		GPIO_PC5
#define TX_PIN_GPIO_EN()					gpio_set_func(DEBUG_INFO_TX_PIN , AS_GPIO);
#define TX_PIN_PULLUP_1M()					gpio_setup_up_down_resistor(DEBUG_INFO_TX_PIN, PM_PIN_PULLUP_1M);
#define TX_PIN_OUTPUT_EN()					gpio_set_output_en(DEBUG_INFO_TX_PIN,1)
#define TX_PIN_OUTPUT_REG					(0x583+((DEBUG_INFO_TX_PIN>>8)<<3))

/**
 * @brief      This function serves to printf string by IO.
 * @param[in]  *format  -  format string need to print
 * @param[in]  ...   	-  variable number of data
 * @return     none.
 */
void io_printf(const char *format, ...);

#define  printf		io_printf
#endif
#else

static inline void no_printf(const char *format, ...)
{
    return;
}
#define  printf     no_printf

#endif



/**
 * @brief  This function initializes the USB interface for printing log message
 * @param  none
 * @return none
 */
extern void usb_loginit(void);

/**
 * @brief     This function serves to print the log message via USB interface
 * @param[in] Str - pointer to the prompting string of the log message
 * @param[in] Content - pointer to the actual content of the log message
 * @return none
 */
extern void log_msg(char *Str, unsigned char *Content, int Len);





