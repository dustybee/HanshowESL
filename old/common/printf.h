
#pragma once
#if(!__PROJECT_8263_BLE_MODULE__)
#ifdef WIN32
#include <stdio.h>
#else
int my_printf(const char *fmt, ...);
int my_sprintf(char* s, const char *fmt, ...);

#define printf	my_printf
#define sprintf	my_sprintf

#endif
#endif

