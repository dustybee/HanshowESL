
#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "global_variable.h"


#define SOC_MUC_CC2640

#ifdef SOC_MUC_CC2640
#define HEARTBEAT_LEN                    26
#define CTRL_HBR_NORMAL                 (0x81)
#define CTRL_HBR_REED                   (0x82)
#define CTRL_HBR_REQ                    (0x83)

#define CTRL_TABLE_HBR                  (0x84)
#else
#define HEARTBEAT_LEN                    16
#define CTRL_HBR_NORMAL                 (0xf0)
#define CTRL_HBR_ESL_VERSION            (0x50)
#define CTRL_HBR_REQ                    (0xe0)
#define CTRL_HBR_REED                   (0x10)

#define CTRL_HBR_NFC                    (0x30)
#define CTRL_HBR_ACK                    (0x20)
//#define VERSION_OP5                      100
#endif

typedef struct
{
    UINT8 battery:3;
    UINT8 reserve1:2;
    UINT8 encryption_enable:1;
    UINT8 isencryption:1;
    UINT8 flash_err:1;
}HARTESL_INFO_T;

uint16_t Send_heartbeat(uint8_t ctrl,uint8_t count);
uint16_t Send_table_heartbeat(uint8_t ctrl,uint8_t count);

#endif
