/********************************************************************************************************
 * @file     app_att.c
 *
 * @brief    for TLSR chips
 *
 * @author	 public@telink-semi.com;
 * @date     Sep. 18, 2015
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *			 The information contained herein is confidential and proprietary property of Telink
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in.
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"
#include "application/print/u_printf.h"

typedef struct
{
	/** Minimum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
	u16 intervalMin;
	/** Maximum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
	u16 intervalMax;
	/** Number of LL latency connection events (0x0000 - 0x03e8) */
	u16 latency;
	/** Connection Timeout (0x000A - 0x0C80 * 10 ms) */
	u16 timeout;
} gap_periConnectParams_t;

static const u16 clientCharacterCfgUUID = GATT_UUID_CLIENT_CHAR_CFG;

static const u16 extReportRefUUID = GATT_UUID_EXT_REPORT_REF;

static const u16 reportRefUUID = GATT_UUID_REPORT_REF;

static const u16 characterPresentFormatUUID = GATT_UUID_CHAR_PRESENT_FORMAT;

static const u16 userdesc_UUID = GATT_UUID_CHAR_USER_DESC;

static const u16 serviceChangeUUID = GATT_UUID_SERVICE_CHANGE;

static const u16 my_primaryServiceUUID = GATT_UUID_PRIMARY_SERVICE;

static const u16 my_characterUUID = GATT_UUID_CHARACTER;

static const u16 my_devServiceUUID = SERVICE_UUID_DEVICE_INFORMATION;

static const u16 my_PnPUUID = CHARACTERISTIC_UUID_PNP_ID;

static const u16 my_devNameUUID = GATT_UUID_DEVICE_NAME;

static const u16 my_gapServiceUUID = SERVICE_UUID_GENERIC_ACCESS;

static const u16 my_appearanceUIID = GATT_UUID_APPEARANCE;

static const u16 my_periConnParamUUID = GATT_UUID_PERI_CONN_PARAM;

static const u16 my_appearance = GAP_APPEARE_UNKNOWN;

static const gap_periConnectParams_t my_periConnParameters = {20, 40, 0, 1000};

static const u16 my_gattServiceUUID = SERVICE_UUID_GENERIC_ATTRIBUTE;

static u16 serviceChangeVal[2] = {0};

static u8 serviceChangeCCC[2] = {0, 0};

#define MY_DEV_NAME "HanshowESL"
extern u8 ble_devName[];

static const u8 my_PnPtrs[] = {0x02, 0x8a, 0x24, 0x66, 0x82, 0x01, 0x00};

//////////////////////// OTA  ////////////////////////////////////////////////////
static const u8 my_OtaUUID[16] = TELINK_SPP_DATA_OTA;
static const u8 my_OtaServiceUUID[16] = TELINK_OTA_UUID_SERVICE;
static u8 my_OtaData = 0x00;
static const u8 my_OtaName[] = {'O', 'T', 'A'};

////////////////////// SPP ////////////////////////////////////
static const u8 TelinkSppServiceUUID[16] = TELINK_SPP_UUID_SERVICE;
static const u8 TelinkSppDataServer2ClientUUID[16] = TELINK_SPP_DATA_SERVER2CLIENT;
static const u8 TelinkSppDataClient2ServerUUID[16] = TELINK_SPP_DATA_CLIENT2SERVER;

// Spp data from Server to Client characteristic variables
static u8 SppDataServer2ClientDataCCC[2] = {0};

// this array will not used for sending data(directly calling HandleValueNotify API), so cut array length from 20 to 1, saving some SRAM

static u8 SppData_1[1] = {0}; // SppDataServer2ClientData[20]
// Spp data from Client to Server characteristic variables
// this array will not used for receiving data(data processed by Attribute Write CallBack function), so cut array length from 20 to 1, saving some SRAM
static u8 SppData_2[1] = {0}; // SppDataClient2ServerData[20]

// SPP data descriptor
static const u8 Telink_Descriptor_1[] = "Telink SPP: Module<->Phone";

//// GAP attribute values
static const u8 my_devNameCharVal[5] = {
	CHAR_PROP_READ | CHAR_PROP_NOTIFY,
	U16_LO(GenericAccess_DeviceName_DP_H), U16_HI(GenericAccess_DeviceName_DP_H),
	U16_LO(GATT_UUID_DEVICE_NAME), U16_HI(GATT_UUID_DEVICE_NAME)};
static const u8 my_appearanceCharVal[5] = {
	CHAR_PROP_READ,
	U16_LO(GenericAccess_Appearance_DP_H), U16_HI(GenericAccess_Appearance_DP_H),
	U16_LO(GATT_UUID_APPEARANCE), U16_HI(GATT_UUID_APPEARANCE)};
static const u8 my_periConnParamCharVal[5] = {
	CHAR_PROP_READ,
	U16_LO(CONN_PARAM_DP_H), U16_HI(CONN_PARAM_DP_H),
	U16_LO(GATT_UUID_PERI_CONN_PARAM), U16_HI(GATT_UUID_PERI_CONN_PARAM)};

//// GATT attribute values
static const u8 my_serviceChangeCharVal[5] = {
	CHAR_PROP_INDICATE,
	U16_LO(GenericAttribute_ServiceChanged_DP_H), U16_HI(GenericAttribute_ServiceChanged_DP_H),
	U16_LO(GATT_UUID_SERVICE_CHANGE), U16_HI(GATT_UUID_SERVICE_CHANGE)};

static const attribute_t my_Attributes[] = {

	{ATT_END_H - 1, 0, 0, 0, 0, 0}, // total num of attribute

	// 0001 - 0007  gap
	{3, ATT_PERMISSIONS_READ, 2, 2, (u8 *)(&my_primaryServiceUUID), (u8 *)(&my_gapServiceUUID), 0},
	{0, ATT_PERMISSIONS_READ, 2, sizeof(my_devNameCharVal), (u8 *)(&my_characterUUID), (u8 *)(my_devNameCharVal), 0},
	{0, ATT_PERMISSIONS_READ, 2, MAX_DEV_NAME_LEN, (u8 *)(&my_devNameUUID), (u8 *)(ble_devName), 0},
	// {0,ATT_PERMISSIONS_READ,2,sizeof(my_appearanceCharVal),(u8*)(&my_characterUUID), (u8*)(my_appearanceCharVal), 0},
	// {0,ATT_PERMISSIONS_READ,2,sizeof (my_appearance), (u8*)(&my_appearanceUIID), 	(u8*)(&my_appearance), 0},
	// {0,ATT_PERMISSIONS_READ,2,sizeof(my_periConnParamCharVal),(u8*)(&my_characterUUID), (u8*)(my_periConnParamCharVal), 0},
	// {0,ATT_PERMISSIONS_READ,2,sizeof (my_periConnParameters),(u8*)(&my_periConnParamUUID), 	(u8*)(&my_periConnParameters), 0},

	// // 0008 - 000b gatt
	// {4,ATT_PERMISSIONS_READ,2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_gattServiceUUID), 0},
	// {0,ATT_PERMISSIONS_READ,2,sizeof(my_serviceChangeCharVal),(u8*)(&my_characterUUID), 		(u8*)(my_serviceChangeCharVal), 0},
	// {0,ATT_PERMISSIONS_READ,2,sizeof (serviceChangeVal), (u8*)(&serviceChangeUUID), 	(u8*)(&serviceChangeVal), 0},
	// {0,ATT_PERMISSIONS_RDWR,2,sizeof (serviceChangeCCC),(u8*)(&clientCharacterCfgUUID), (u8*)(serviceChangeCCC), 0},
};

void my_att_init(void)
{
	bls_att_setAttributeTable((u8 *)my_Attributes);

	u8 device_name[] = MY_DEV_NAME;
	bls_att_setDeviceName(MY_DEV_NAME, sizeof(MY_DEV_NAME));
}