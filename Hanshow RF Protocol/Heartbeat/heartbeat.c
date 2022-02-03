#include "../aes128/aes128.h"
#include  "heartbeat.h"
#include  "three_event.h"
#include "storage_struct.h"
#include "lattice_epd/epd_data_struct.h"
#include "lattice_epd/scrn_public_fun.h"

uint16_t Send_heartbeat(uint8_t ctrl,uint8_t count)
{

    UINT8 i;
    UINT32 id_temp;
#pragma pack(1)

    struct esl_regist {
        UINT8 ctrl;
        UINT8 set_wkup_id[3];
        RFID eslid;
        UINT8 set_wkup_chn;
        UINT8 grp_wkup_chn;
        UINT8 data_chn;
        UINT8 esl_netmask;
        HARTESL_INFO_T info;
        UINT32 screen_id;
        UINT8 ser_wor_time;
        UINT8 temperture;
        UINT8 rom_version;
        UINT8 page_map;
        UINT8 page_crc_map;
        UINT16 default_page_crc; 
        UINT16 crc;
    }esl_regist_buf;
#pragma pack()

    esl_regist_buf.ctrl = ctrl ;
    memcpy(esl_regist_buf.set_wkup_id,(UINT8 *)&INFO_DATA.gRFInitData.wakeup_id,3);
    memcpy(&esl_regist_buf.eslid,(UINT8 *)&INFO_DATA.gRFInitData.esl_id,4);
    esl_regist_buf.set_wkup_chn =  INFO_DATA.gRFInitData.set_wkup_ch;
    esl_regist_buf.grp_wkup_chn = INFO_DATA.gRFInitData.grp_wkup_ch;
    esl_regist_buf.data_chn = INFO_DATA.gRFInitData.esl_data_ch;
    esl_regist_buf.esl_netmask = INFO_DATA.gRFInitData.esl_netmask;


    esl_regist_buf.info.battery = gelectric_quantity; //bit[2:0]//��ص���(adc_voltage())
    esl_regist_buf.info.flash_err = gflash_empty; //bit[7]//�ⲿflash�쳣��־

    esl_regist_buf.info.encryption_enable = aes128.flag.aes_enable; //bit[5] �Ƿ�֧�ּ���
    esl_regist_buf.info.isencryption = aes128.flag.isencryption; //bit[6] �Ƿ��Ѿ�����

    esl_regist_buf.screen_id = INFO_DATA.gRFInitData.screen_id;
    esl_regist_buf.ser_wor_time = def_sys_attr.sys_def_attribute.set_wkup_time;
    esl_regist_buf.temperture = disply_temperature;
    esl_regist_buf.rom_version = EPD_3_VERSION;

    esl_regist_buf.page_map =0;
    for(i=0;i<8;i++)
    {
        if(gSys_tp.page_map[i] == i)
            esl_regist_buf.page_map |= (0x01 << i);
    }
    esl_regist_buf.page_crc_map = page_crc_map;
    esl_regist_buf.default_page_crc = gdsi_info_st[gSys_tp.default_page_id].page_crc;
    esl_regist_buf.crc = my_cal_crc16(0,(UINT8 *)&esl_regist_buf,24);
    esl_regist_buf.crc  = my_cal_crc16(esl_regist_buf.crc ,(UINT8 *)&INFO_DATA.gRFInitData.esl_id,4);

    id_temp = rfid_to_u32(INFO_DATA.gRFInitData.master_id);
    set_rf_parameters(DATA_RATE_100K, RF_TX_POWER_2DB, 2401,0);
    while(count)
    {
        RF_EventMask result = Rf_tx_package(rfHandle, id_temp, HEARTBEAT_LEN, (UINT8 *)&esl_regist_buf);
        if(!(result & RF_EventLastCmdDone))
        {
            while(1);
        }
        count--;
    }
    adc_voltage();
    return 0;

}

uint16_t Send_table_heartbeat(uint8_t ctrl,uint8_t count)
{

    UINT32 id_temp;
#pragma pack(1)
    struct esl_table_regist{
        UINT8 ctrl;
        UINT32 product_id;
        UINT16 screen_high;
        UINT16 screen_width;
        UINT8  screen_dpi;
        UINT8  max_page;
        UINT16 flash_size;
        UINT16 max_package;
        UINT8  screen_delay_time;
        UINT8  osd_process_time;
        UINT16  screen_size;
        UINT8  reserve_buf[5];
        UINT16 crc;
    }esl_table_regist_buf;
#pragma pack()

    esl_table_regist_buf.ctrl = ctrl ;
    esl_table_regist_buf.product_id = INFO_DATA.gRFInitData.screen_id;
    esl_table_regist_buf.screen_high = screen_dis_t.h;
    esl_table_regist_buf.screen_width = screen_dis_t.w;
    esl_table_regist_buf.screen_size = screen_dis_t.screen_size;
    esl_table_regist_buf.max_page = max_page_fun(file_num);
    esl_table_regist_buf.flash_size = FLASH_ALL_SIZE;
    esl_table_regist_buf.max_package = UP_ALIGN( ((screen_dis_t.h+7)/8*8) * screen_dis_t.w/8)/20;
    esl_table_regist_buf.screen_delay_time = 20;
    if(screen_dis_t.src_color == BLACK_WHITE_RED)
    {
        esl_table_regist_buf.screen_delay_time = 40;
        esl_table_regist_buf.max_package = esl_table_regist_buf.max_package *2;
    }
    if(screen_dis_t.src_tmp == FREEZE_TMP )
    {
        esl_table_regist_buf.screen_delay_time = 60;
    }
    esl_table_regist_buf.osd_process_time= 1;
    memset(esl_table_regist_buf.reserve_buf , 0 ,sizeof(esl_table_regist_buf.reserve_buf));

    esl_table_regist_buf.crc = my_cal_crc16(0,(UINT8 *)&esl_table_regist_buf,24);
  //  esl_table_regist_buf.crc  = my_cal_crc16(esl_table_regist_buf.crc ,(UINT8 *)&INFO_DATA.gRFInitData.esl_id,4);

    id_temp = rfid_to_u32(INFO_DATA.gRFInitData.master_id);
    set_rf_parameters(DATA_RATE_100K, RF_TX_POWER_2DB, 2401,0);
    while(count)
    {
        RF_EventMask result = Rf_tx_package(rfHandle, id_temp, HEARTBEAT_LEN, (UINT8 *)&esl_table_regist_buf);
        if(!(result & RF_EventLastCmdDone))
        {
            while(1);
        }
        count--;
    }
    adc_voltage();
    return 0;
}

