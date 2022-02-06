#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"
#include "vendor/common/user_config.h"

extern void app (void);

void irq_handler (void)
{
	irq_blt_sdk_handler();
}


int main (void)    //must run in ramcode
{
	blc_pm_select_internal_32k_crystal();
	cpu_wakeup_init();
	int deepRetWakeUp = pm_is_MCU_deepRetentionWakeup();  //MCU deep retention wakeUp
	gpio_init( !deepRetWakeUp );  //analog resistance will keep available in deepSleep mode, so no need initialize again
	blc_app_loadCustomizedParameters();  //load customized freq_offset cap value
	app_init();
    irq_enable();

	while (1) {
		app ();
	}
}

