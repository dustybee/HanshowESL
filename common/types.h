
#pragma once


#define u8 u8_old
typedef unsigned char u8 ;

#define s8  s8_old
typedef signed char s8;

#define u16 u16_old
typedef unsigned short u16;

#define s16 s16_old
typedef signed short s16;

#define s32 s32_old
typedef int s32;

#define u32 u32_old
typedef unsigned int u32;

#define s64  s64_old
typedef long long s64;

#define u64 u64_old
typedef unsigned long long u64;

#ifndef NULL
#define NULL 	0
#endif

#ifndef __cplusplus

//typedef u8 bool;
typedef enum
{
	false,
	true
}bool;
#ifndef FALSE
#define FALSE 	0
#endif
#ifndef TRUE
#define TRUE 	(!FALSE)
#endif

#define false 	FALSE
#define true 	TRUE

#endif

// There is no way to directly recognise whether a typedef is defined
// http://stackoverflow.com/questions/3517174/how-to-check-if-a-datatype-is-defined-with-typedef
#ifdef __GNUC__
typedef	u16	wchar_t;		
#endif

#ifndef WIN32
typedef u32 size_t;
#endif

#define U32_MAX ((u32)0xffffffff)
#define U16_MAX ((u16)0xffff)
#define U8_MAX ((u8)0xff)
#define U31_MAX ((u32)0x7fffffff)
#define U15_MAX ((u16)0x7fff)
#define U7_MAX ((u8)0x7f)


#ifdef WIN32
#   ifndef FALSE
#        define FALSE 0
#    endif

#   ifndef TRUE
#        define TRUE 1
#   endif
#endif

#define SUCCESS                   0x00
#define FAILURE                   0x01

typedef u32 UTCTime;
typedef u32 arg_t;
typedef u32 status_t;


