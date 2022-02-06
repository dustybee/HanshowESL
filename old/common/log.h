
#pragma once

#include "log_id.h"
#include "printf.h"


#ifndef LOG_IN_RAM
#define LOG_IN_RAM   0
#endif

#define		LOG_MASK_BEGIN		0x40
#define		LOG_MASK_END		0x00
#define		LOG_MASK_TGL		0xC0
#define		LOG_MASK_DAT		0x80

#define U8_SET(addr, v)			(*(volatile unsigned char  *)(addr) = (unsigned char)(v))
static inline void swire2usb_init (void) {
	U8_SET(0x800128, 0x00);
	U8_SET(0x80012d, 0);
	U8_SET(0x80013b, 32);
}

static inline void usb_log_init (void) {
	U8_SET(0x80013c, 0x40);
	U8_SET(0x80013d, 0x09);
}

#if (__LOG_RT_ENABLE__)
void log_write_data(int id, int type, u32 dat);
void log_task_begin(int id);
void log_task_end(int id);
void log_event(int id);
void log_data(int id, u32 dat);

#define	LOG_TICK(id,e)	do{log_task_begin(id); e; log_task_end(id);}while(0)

#define LOG(x, s,...) printf("(%s:%d)"  x "\r\n" , __FUNCTION__, __LINE__, ## s)

#else
#define log_write_data(id, type, dat)
#define log_task_begin(id)
#define log_task_end(id)
#define log_event(id)
#define log_data(id, dat)
#define	LOG_TICK(id,e)			do{e;}while (0)

#define LOG(x, s,...)

#endif

