/********************************************************************************************************
 * @file     timer_event.c
 *
 * @brief    This file provides set of functions to manage software TIMER
 *
 * @author   xiaodong.zong@telink-semi.com
 * @date     Oct. 8, 2016
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
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
#include "timer_event.h"
#include "../common.h"

ev_time_event_t timer_list[10];

static int inline ev_is_timer_expired(ev_time_event_t *e, u32 now)
{
    assert(e);
    return ((u32)(now - e->t) < (TIMER_SAFE_MARGIN_US*sys_tick_per_us));
}


__attribute__((section(".ram_code")))void ev_start_timer(ev_time_event_t * e)
{  
    assert(e);

    u8 r = irq_disable();

    u32 now = ClockTime();
    u32 t = now + e->interval;    // becare of overflow

    e->t = t;
    e->valid = 1;
   
    irq_restore(r);
}

__attribute__((section(".ram_code")))void ev_cancel_timer(ev_time_event_t * e)
{
    assert(e);

    u8 r = irq_disable();
    e->valid = 0;
    e->busy = 0;
    irq_restore(r);
}

__attribute__((section(".ram_code")))ev_time_event_t *ev_on_timer(ev_timer_callback_t cb, void *data, u32 t_us)
{
    int i;
    ev_time_event_t *e = NULL;

    assert(cb);

    for (i = 0; i < LengthOfArray(timer_list); i++)
    {
        if (timer_list[i].busy == 0)
        {
            timer_list[i].busy = 1;
            e = timer_list + i;
            break;
        }
    }
    if (e == NULL) {
        while(1);
    }
    e->interval = t_us * sys_tick_per_us;
    e->cb = cb;
    e->data = data;
    ev_start_timer(e);
    return e;
}

__attribute__((section(".ram_code")))void ev_unon_timer(ev_time_event_t ** e)
{
    assert(e && (*e));
    
    ev_cancel_timer(*e);
    *e = NULL;
}


/* Process time events */
__attribute__((section(".ram_code")))void ev_process_timer()
{
    u32 now = ClockTime();
    ev_time_event_t *te;
    for (te = timer_list; te < timer_list + LengthOfArray(timer_list); te++) {
        if ((!is_timer_expired(te)) && ev_is_timer_expired(te, now))
        {
            int t;
            if ((unsigned int)(te->cb) < 0x100 || (unsigned int)(te->cb) > 0x20000) {
                while(1);
            }
            t = te->cb(te->data);
            if(t < 0) {
                ev_cancel_timer(te);        // delete timer
            }
            else if(0 == t) {
                te->t = now + te->interval;    // becare of overflow
            }
            else {
                te->interval = t * sys_tick_per_us;
                te->t = now + te->interval;    // becare of overflow
            }
        }
    }
}

__attribute__((section(".ram_code")))int is_timer_expired(ev_time_event_t *e)
{
    if ( e == NULL ) {
        return TRUE;
    }
    if (e->valid == 1) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}
