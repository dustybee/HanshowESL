/********************************************************************************************************
 * @file     app_config.h
 *
 *
 * @par      The user configuration file “app_config.h” serves to configure parameters of the whole system, including
 *           parameters related to BLE, GPIO, PM (low-power management), and etc.
 *
 *******************************************************************************************************/

#pragma once

/////////////////// FEATURE SELECT /////////////////////////////////
#define BLE_APP_PM_ENABLE 0
#define PM_DEEPSLEEP_RETENTION_ENABLE 1
#define TEST_CONN_CURRENT_ENABLE 0 // test curr, disable keyscan concerned
#define BLE_REMOTE_SECURITY_ENABLE 0

/////////////////// Clock  /////////////////////////////////
#define CLOCK_SYS_CLOCK_HZ 24000000

enum
{
	CLOCK_SYS_CLOCK_1S = CLOCK_SYS_CLOCK_HZ,
	CLOCK_SYS_CLOCK_1MS = (CLOCK_SYS_CLOCK_1S / 1000),
	CLOCK_SYS_CLOCK_1US = (CLOCK_SYS_CLOCK_1S / 1000000),
};

/////////////////// BLE /////////////////////////////////
typedef enum
{
	ATT_H_START = 0,
	//// Gap ////
	/**********************************************************************************************/
	GenericAccess_PS_H,			   // UUID: 2800, 	VALUE: uuid 1800
	GenericAccess_DeviceName_CD_H, // UUID: 2803, 	VALUE:  			Prop: Read | Notify
	GenericAccess_DeviceName_DP_H, // UUID: 2A00,   VALUE: device name
	GenericAccess_Appearance_CD_H, // UUID: 2803, 	VALUE:  			Prop: Read
	GenericAccess_Appearance_DP_H, // UUID: 2A01,	VALUE: appearance
	CONN_PARAM_CD_H,			   // UUID: 2803, 	VALUE:  			Prop: Read
	CONN_PARAM_DP_H,			   // UUID: 2A04,   VALUE: connParameter

	//// gatt ////
	/**********************************************************************************************/
	GenericAttribute_PS_H,				   // UUID: 2800, 	VALUE: uuid 1801
	GenericAttribute_ServiceChanged_CD_H,  // UUID: 2803, 	VALUE:  			Prop: Indicate
	GenericAttribute_ServiceChanged_DP_H,  // UUID:	2A05,	VALUE: service change
	GenericAttribute_ServiceChanged_CCB_H, // UUID: 2902,	VALUE: serviceChangeCCC

	//// device information ////
	/**********************************************************************************************/
	DeviceInformation_PS_H,		  // UUID: 2800, 	VALUE: uuid 180A
	DeviceInformation_pnpID_CD_H, // UUID: 2803, 	VALUE:  			Prop: Read
	DeviceInformation_pnpID_DP_H, // UUID: 2A50,	VALUE: PnPtrs

	//// SPP ////
	/**********************************************************************************************/
	SPP_PS_H, // UUID: 2800, 	VALUE: telink spp service uuid

	// server to client
	SPP_SERVER_TO_CLIENT_CD_H,	 // UUID: 2803, 	VALUE:  			Prop: read | Notify
	SPP_SERVER_TO_CLIENT_DP_H,	 // UUID: telink spp s2c uuid,  VALUE: SppDataServer2ClientData
	SPP_SERVER_TO_CLIENT_CCB_H,	 // UUID: 2902, 	VALUE: SppDataServer2ClientDataCCC
	SPP_SERVER_TO_CLIENT_DESC_H, // UUID: 2901, 	VALUE: TelinkSPPS2CDescriptor

	ATT_END_H,

} ATT_HANDLE;

/////////////////// watchdog  //////////////////////////////
#define MODULE_WATCHDOG_ENABLE 0
#define WATCHDOG_INIT_TIMEOUT 500 // ms

#include "vendor/common/default_config.h"
