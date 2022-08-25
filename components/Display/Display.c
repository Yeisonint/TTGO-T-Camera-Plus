#include <stdio.h>
#include "Display.h"
#include "st7789.h"
#include "disp_spi.h"
#include "esp_log.h"

#define LV_TICK_PERIOD_MS 1
#define TAG "Display"

void lv_example(void) {
	printf("Call lv_init...\n");
	lv_init();

	lv_obj_t *label = lv_label_create(lv_scr_act());
	lv_label_set_text(label, "Button");
	lv_obj_center(label);

	printf("Exit with success!\n");
}


void init(void){

	ESP_LOGI(TAG, "Initializing SPI master for display");

	    lvgl_spi_driver_init(TFT_SPI_HOST,
	        DISP_SPI_MISO, DISP_SPI_MOSI, DISP_SPI_CLK,
	        SPI_BUS_MAX_TRANSFER_SZ, 1,
	        DISP_SPI_IO2, DISP_SPI_IO3);

	    disp_spi_add_device(TFT_SPI_HOST);
	st7789_init();
	//st7789_flush(drv, area, color_map);
}
