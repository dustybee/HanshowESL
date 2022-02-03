/********************************************************************************************************
 * @file     driver_8258.h 
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
 *         
 *******************************************************************************************************/
#pragma once



#include "drivers/8359/bsp.h"
#include "drivers/8258/aes.h"
#include "drivers/8359/analog.h"
#include "drivers/8359/compiler.h"
#include "drivers/8359/register.h"
#include "drivers/8359/gpio.h"
#include "drivers/8359/pwm.h"
#include "drivers/8359/irq.h"
#include "drivers/8359/clock.h"
#include "drivers/8359/random.h"
#include "drivers/8359/flash.h"
#include "drivers/8359/rf_drv.h"
#include "drivers/8359/pm.h"
#include "drivers/8359/audio.h"
#include "drivers/8359/adc.h"
#include "drivers/8359/i2c.h"
#include "drivers/8359/spi.h"
#include "drivers/8359/uart.h"
#include "drivers/8359/register.h"
#include "drivers/8359/watchdog.h"
#include "drivers/8359/usb8258.h"
#include "drivers/8359/usbhw_i.h"
#include "drivers/8359/usbhw.h"
#include "drivers/8359/register.h"
#include "drivers/8359/dfifo.h"
#include "drivers/8359/dma.h"
#include "drivers/8359/emi.h"
/*! \mainpage API User guide for TLSR8258F512
\n
__Keyword:__ \n
Bluetooth Low Energy;BLE Mesh;6LoWPAN;Thread;Zigbee;RF4CE;HomeKit;2.4GHz;Features;Package;Pin layout;Memory;MCU;Working modes; Wakeup sources;RF Transceiver;Clock;Timers; Interrupt;PWM;Audio;QDEC;ADC;PGA;Temperature sensor;Low power comparator; AES; Electrical specification; \n
\n
__Brief:__\n
This manual is dedicated for Telink BLE + IEEE802.15.4 multi-standard SoC TLSR8258F512. In this manual,key features, working mode,main modules, electrical specification and application of the TLSR8258F512 are introduced. \n
\n
__Published by__ \n
__Telink Semiconductor__ \n
\n
__Bldg 3, 1500 Zuchongzhi Rd,__ \n
__Zhangjiang Hi-Tech Park, Shanghai, China__ \n
\n
__Telink Semiconductor__ \n
__All Right Reserved__ \n
\n
__Legal Disclaimer:__ \n
    Telink Semiconductor reserves the right to make changes without further notice to any products herein to improve reliability, function or design. Telink Semiconductor disclaims any and all liability for any errors, inaccuracies or incompleteness contained herein or in any other disclosure relating to any product.\n
	\n
    Telink Semiconductor does not assume any liability arising out of the application or use of any product or circuit described herein; neither does it convey any license under its patent rights, nor the rights of others \n
	\n
    The products shown herein are not designed for use in medical, life-saving, or life-sustaining applications. Customers using or selling Telink Semiconductor products not expressly indicated for use in such applications do so entirely at their own risk and agree to fully indemnify Telink Semiconductor for any damages arising or resulting from such use or sale.\n
	\n
__Information:__ \n
For further information on the technology, product and business term, please contact [Telink Semiconductor Company](http://www.telink-semi.com "Telink") \n
For sales or technical support, please send email to the address of:\n
<telinkcnsales@telink-semi.com> \n
<telinkcnsupport@telink-semi.com> \n
For more details about this SoC, please look through [Datasheet for Telink BLE+IEEE802.15.4 Multi-Standard Wireless SoC TLSR8258](E:/1_wtcdb/prj/kite/doc/DS_TLSR8258-E2_Datasheet for Telink BLE+IEEE802.15.4 Multi-Standard Wireless SoC TLSR8258.pdf) \n
\n
__Revision History:__ \n

| Version | Major Changes   | Date         | Author |
| :-----: | :-------------: | :----------: | :----: |
| 1.0.0   | initial release | Dec. 11 2018 | LJW/ZJY/ZL/LR/SP/YY |

\n

*/