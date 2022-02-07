#include <stack/ble/ble.h>
#include "tl_common.h"
#include "drivers.h"
#include "app_config.h"
#include "vendor/common/blt_led.h"
#include "vendor/common/blt_soft_timer.h"
#include "vendor/common/blt_common.h"

//#define		MY_RF_POWER_INDEX	RF_POWER_P10p29dBm //  10.29 dbm
#define MY_RF_POWER_INDEX RF_POWER_P0p04dBm

#define RX_FIFO_SIZE 64
#define RX_FIFO_NUM 8

#define TX_FIFO_SIZE 40
#define TX_FIFO_NUM 16

u8 blt_rxfifo_b[RX_FIFO_SIZE * RX_FIFO_NUM] = {0};
my_fifo_t blt_rxfifo = {
	RX_FIFO_SIZE,
	RX_FIFO_NUM,
	0,
	0,
	blt_rxfifo_b,
};

u8 blt_txfifo_b[TX_FIFO_SIZE * TX_FIFO_NUM] = {0};
my_fifo_t blt_txfifo = {
	TX_FIFO_SIZE,
	TX_FIFO_NUM,
	0,
	0,
	blt_txfifo_b,
};

void connect_callback(u8 e, u8 *p, int n)
{
	bls_l2cap_requestConnParamUpdate(8, 8, 99, 400); // 1 S
	at_print((unsigned char *)"\r\n+BLE_CONNECTED\r\n");
}

void disconnect_callback(u8 e, u8 *p, int n)
{
	at_print((unsigned char *)"\r\n+BLE_DISCONNECTED\r\n");
}

void conn_para_req_callback(u8 e, u8 *p, int n)
{
	at_print((unsigned char *)"\r\n+BLE_CONN_PARA_REQ\r\n");
}

void conn_para_up_callback(u8 e, u8 *p, int n)
{
	at_print((unsigned char *)"\r\n+BLE_CONN_PARA_UP\r\n");
}
void ble_init_normal(void)
{
	random_generator_init();

	u8 mac_public[6];
	u8 mac_random_static[6];
	blc_initMacAddress(CFG_ADR_MAC, mac_public, mac_random_static);

	////// Got this from atc1441 ATC_TLSR_Paper //////
	u8 ble_name[] = {11, 0x09, 'E', 'S', 'L', '_', '0', '0', '0', '0', '0', '0'};

	const char *hex_ascii = {"0123456789ABCDEF"};
	ble_name[6] = hex_ascii[mac_public[2] >> 4];
	ble_name[7] = hex_ascii[mac_public[2] & 0x0f];
	ble_name[8] = hex_ascii[mac_public[1] >> 4];
	ble_name[9] = hex_ascii[mac_public[1] & 0x0f];
	ble_name[10] = hex_ascii[mac_public[0] >> 4];
	ble_name[11] = hex_ascii[mac_public[0] & 0x0f];
	////// end copy from atc1441 //////

	////// Controller Initialization  //////////
	blc_ll_initBasicMCU();
	blc_ll_initStandby_module(mac_public);
	blc_ll_initAdvertising_module(mac_public);
	blc_ll_initConnection_module();
	blc_ll_initSlaveRole_module();

	////// Host Initialization  //////////
	blc_gap_peripheral_init(); // gap initialization
	extern void my_att_init();
	my_att_init();										  // gatt initialization
	blc_l2cap_register_handler(blc_l2cap_packet_receive); // l2cap initialization

	blc_smp_setSecurityLevel(No_Security);

	bls_ll_setAdvData((u8 *)ble_name, sizeof(ble_name));

	bls_ll_setScanRspData(NULL, 0);

	u8 status = bls_ll_setAdvParam(ADV_INTERVAL_50MS,
								   ADV_INTERVAL_50MS,
								   ADV_TYPE_CONNECTABLE_UNDIRECTED,
								   OWN_ADDRESS_PUBLIC,
								   0,
								   NULL,
								   BLT_ENABLE_ADV_ALL,
								   ADV_FP_NONE);

	rf_set_power_level_index(MY_RF_POWER_INDEX);

	bls_ll_setAdvEnable(1);

	bls_app_registerEventCallback(BLT_EV_FLAG_CONNECT, &connect_callback);
	bls_app_registerEventCallback(BLT_EV_FLAG_TERMINATE, &disconnect_callback);

	bls_app_registerEventCallback(BLT_EV_FLAG_CONN_PARA_REQ, &conn_para_req_callback);
	bls_app_registerEventCallback(BLT_EV_FLAG_CONN_PARA_UPDATE, &conn_para_up_callback);

	app_uart_init();

	irq_enable();
}