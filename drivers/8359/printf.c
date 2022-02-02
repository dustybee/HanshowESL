/********************************************************************************************************
 * @file     printf.c 
 *
 * @brief    This is the source file for TLSR8258
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

#include "register.h"
#include "printf.h"
#include "usbhw.h"
#include "timer.h"

#if(DEBUG_MODE)

#define VA_START(list, param) (list = (char*)((int)&param + sizeof(param)))
#define VA_ARG(list, type) ((type *)(list += sizeof(type)))[-1]


#ifndef   NULL
#define   NULL				0
#endif
/**
 * @brief     This function set the length of buffer in hardware for USB print
 * @param[in] BufLen - the length of buffer in hardware
 * @return    none
 */
void print_bufInit(unsigned char BufLen)
{
    write_reg8(0x80013c, BufLen);
}
/**
 * @brief     This function send the data to usb print device
 * @param[in] *p - point to the buffer
 * @param[in] n  - the length of buffer in hardware
 * @return    none
 */
void send_status_to_usb(unsigned char *p, int n)
{
    int i;
    write_reg8(0x800118, n); //reg_usb_ep8_dat = n;
    if (n) {     // print DATA
        for (i = 1; i < n+1; i++) {
            write_reg8(0x800118, *p); //reg_usb_ep8_dat = *p++;
            p++;
        }
    }
    else {       //print ASCII
        for ( i = 1; i < 60; i++) {
            if (*p) {
                write_reg8(0x800118, *p); //reg_usb_ep8_dat = *p++;
                p++;
            }
            else {
                //reg_usb_ep8_dat = 0;
                write_reg8(0x800118, 0);
                break;
            }
        }
    }
    // reg_usb_ep8_ctrl = BIT(7);
    write_reg8(0x800120, BIT(7));
}
/**
 * @brief  This function initializes the USB interface for printing log message
 * @param  none
 * @return none
 */
void usb_loginit(void)
{
    write_reg8(0x80013c, 0x40);
    write_reg8(0x80013d, 0x09);
}
/**
 * @brief     This function serves to print the log message via USB interface
 * @param[in] Str - pointer to the prompting string of the log message
 * @param[in] Content - pointer to the actual content of the log message
 * @return none
 */
void log_msg(char *Str, unsigned char *Content, int Len)
{
    if (Str) {
        send_status_to_usb((unsigned char *)Str, 0);
    }
    if (Len > 32) {
        Len = 32;
    }
    if (Len > 0) {
        send_status_to_usb(Content, Len);
    }
}
#if (DEBUG_BUS==DEBUG_USB)
#define   FIFOTHRESHOLD  	4
#define   BLOCK_MODE   		1

/**
 * @brief      This function serves to foramt string.
 * @param[in]  c  -  a character need to print 
 * @return     none.
 */
void usb_putchar (char c)
{
#if(BLOCK_MODE)
	while (reg_usb_ep8_fifo_mode & BIT(1));
#endif
  reg_usb_ep8_dat = c;
}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  c  -  a number need to print 
 * @return     none.
 */
void usb_putnum(unsigned char c) {
	unsigned char nib = c >> 4;
	if (nib > 9)	nib = nib + 87;
	else		nib = nib + 48;
	usb_putchar (nib);

	nib = c & 15;
	if (nib > 9)	nib = nib + 87;
	else		nib = nib + 48;
	usb_putchar (nib);
}


/**
 * @brief      This function serves to foramt string.
 * @param[in]  w  -  a integer need to print 
 * @return     none.
 */
void usb_putnumber(unsigned int w,int len) {
	int i;
	int c = w;

	for(i=len-1;i>=0;i--)
	{
		c = w >>(i*8);
		usb_putnum(c);
	}
}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  w  -  a integer need to print 
 * @return     none.
 */
void usb_putint(unsigned int w)
{
	unsigned char buf[12],tmp,*p;
	int u;
	p = buf + 11;
	*p = '\0';
	u = w;
	do{ // at least one time..
        tmp = u % 10;
		*--p = tmp + '0';
		u /= 10;
	}while(u);
	while(*p){
        usb_putchar(*p);
        p++;
    }

}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  *str  -  string need to print 
 * @return     none.
 */
void  usb_putstring(char * str)
{
    char *s;
	s = str;
	if(s == NULL){
        s = "(null)";
    }
	while(*s){
           usb_putchar(*s);
           s++;
	}
}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  *f -  string need to format
 * @param[in]  a  -  string need to print 
 * @return     none.
 */
static char *usb_format_msg(char *f, int a)
{		
	char c;
	int fieldwidth = 0;
	int flag = 0;
	//when the character is not NUL(ASCAII value =0x00)
	while ((c = *f++) != 0)
	{
		if (c >= '0' && c <= '9')
		{
			//number in character is changed to number in real
			fieldwidth = (fieldwidth * 10) + (c - '0');
		}
		else
		{
			switch (c)
			{
				case 'x':
					flag = 16;
					break;
				case 'd':
					flag = 10;
					break;
				case 's':
					flag = 99;
					break;
				default:
					usb_putchar('*');
					flag = -1;
					break;
			}
		}
		if(flag!=0)
		{
			if(fieldwidth==0)  fieldwidth=8;
			break;
		}
	}
	if(flag == 16)
	usb_putnumber(a,fieldwidth);
	else if(flag == 10)
	usb_putint(a);
	else if(flag==99)
	usb_putstring((char *)a);
	return f;

}

/**
 * @brief      This function serves to printf string by USB.
 * @param[in]  *format  -  format string need to print
 * @param[in]  ...   	-  variable number of data
 * @return     none.
 */
void usb_printf(const char *format, ...) {
	//va_list args;
	char *  args;
	char *  pcStr = (char*)format;
	static int  first_time = 1;
	if(first_time==1)
	{
      reg_usb_ep8_send_thre = FIFOTHRESHOLD;
	}

	VA_START( args, format);

	while (*pcStr)
	{                       /* this works because args are all ints */
    	if (*pcStr == '%')
        	pcStr = usb_format_msg(pcStr + 1, VA_ARG(args, int));
    	else
        	usb_putchar(*pcStr++);
	}
}

#elif (DEBUG_BUS==DEBUG_IO)

#ifndef		BIT_INTERVAL
#define		BIT_INTERVAL	(sys_tick_per_us*1000*1000/PRINT_BAUD_RATE)
#endif

/**
 * @brief      This function serves to foramt string.
 * @param[in]  byte  -  a byte need to print
 * @return     none.
 */
_attribute_ram_code_  void io_putchar(unsigned char byte){
	unsigned char j = 0;
	unsigned int t1 = 0,t2 = 0;
	static unsigned char init_flag = 1;
	if(init_flag==1)
	{
		TX_PIN_GPIO_EN();
		TX_PIN_PULLUP_1M();
		TX_PIN_OUTPUT_EN();//Enable output

		init_flag = 0;
	}

	unsigned char tmp_bit0 = read_reg8(TX_PIN_OUTPUT_REG) & (~(DEBUG_INFO_TX_PIN & 0xff));
	unsigned char tmp_bit1 = read_reg8(TX_PIN_OUTPUT_REG) | (DEBUG_INFO_TX_PIN & 0xff);
	unsigned char bit[10] = {0};

	bit[0] = tmp_bit0;
	bit[1] = (byte & 0x01)? tmp_bit1 : tmp_bit0;
	bit[2] = ((byte>>1) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[3] = ((byte>>2) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[4] = ((byte>>3) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[5] = ((byte>>4) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[6] = ((byte>>5) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[7] = ((byte>>6) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[8] = ((byte>>7) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[9] = tmp_bit1;

	t1 = read_reg32(0x740);
	for(j = 0;j<10;j++)
	{
		t2 = t1;
		while(t1 - t2 < BIT_INTERVAL){
			t1  = read_reg32(0x740);
		}
		write_reg8(TX_PIN_OUTPUT_REG,bit[j]);        //send bit0
	}
}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  c  -  a number need to print
 * @return     none.
 */
void io_putnum(unsigned char c) {
	unsigned char nib = c >> 4;
	if (nib > 9)	nib = nib + 87;
	else		nib = nib + 48;
	io_putchar (nib);

	nib = c & 15;
	if (nib > 9)	nib = nib + 87;
	else		nib = nib + 48;
	io_putchar (nib);
}


/**
 * @brief      This function serves to foramt string.
 * @param[in]  w  -  a integer need to print
 * @return     none.
 */
void io_putnumber(unsigned int w,int len) {
	int i;
	int c = w;

	for(i=len-1;i>=0;i--)
	{
		c = w >>(i*8);
		io_putnum(c);
	}
}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  w  -  a integer need to print
 * @return     none.
 */
void io_putint(unsigned int w)
{
	unsigned char buf[12],tmp,*p;
	int u;
	p = buf + 11;
	*p = '\0';
	u = w;
	do{ // at least one time..
        tmp = u % 10;
		*--p = tmp + '0';
		u /= 10;
	}while(u);
	while(*p){
        io_putchar(*p);
        p++;
    }

}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  *str  -  string need to print
 * @return     none.
 */
void  io_putstring(char * str)
{
    char *s;
	s = str;
	if(s == NULL){
        s = "(null)";
    }
	while(*s){
           io_putchar(*s);
           s++;
	}
}

/**
 * @brief      This function serves to foramt string.
 * @param[in]  *f -  string need to format
 * @param[in]  a  -  string need to print
 * @return     none.
 */
static char *io_format_msg(char *f, int a)
{
	char c;
	int fieldwidth = 0;
	int flag = 0;
	//when the character is not NUL(ASCAII value =0x00)
	while ((c = *f++) != 0)
	{
		if (c >= '0' && c <= '9')
		{
			//number in character is changed to number in real
			fieldwidth = (fieldwidth * 10) + (c - '0');
		}
		else
		{
			switch (c)
			{
				case 'x':
					flag = 16;
					break;
				case 'd':
					flag = 10;
					break;
				case 's':
					flag = 99;
					break;
				default:
					io_putchar('*');
					flag = -1;
					break;
			}
		}
		if(flag!=0)
		{
			if(fieldwidth==0)  fieldwidth=8;
			break;
		}
	}
	if(flag == 16)
	io_putnumber(a,fieldwidth);
	else if(flag == 10)
	io_putint(a);
	else if(flag==99)
	io_putstring((char *)a);
	return f;

}

/**
 * @brief      This function serves to printf string by IO.
 * @param[in]  *format  -  format string need to print
 * @param[in]  ...   	-  variable number of data
 * @return     none.
 */
void io_printf(const char *format, ...) {
	//va_list args;
	char *  args;
	char *  pcStr = format;
	static unsigned char re_enter_flag = 0;
	if(!re_enter_flag){
		re_enter_flag = 1;
		VA_START( args, format);

		while (*pcStr)
		{                       /* this works because args are all ints */
			if (*pcStr == '%')
				pcStr = io_format_msg(pcStr + 1, VA_ARG(args, int));
			else
				io_putchar(*pcStr++);
		}
	}
	re_enter_flag = 0;
}

#endif
#endif


