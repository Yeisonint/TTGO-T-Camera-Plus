/*
 * devices.c
 *
 *  Created on: 13/09/2022
 *      Author: Yeisonint
 */
#include "devices.h"
static const char *TAG = "SDCard";

/*********************
 *      SPI BUS
 *********************/
#define SPI_HOST_DEVICE HSPI_HOST
#define SPI_DMA_CHAN    1

spi_bus_config_t bus_cfg = {
    .mosi_io_num = SPI_MOSI,
    .miso_io_num = SPI_MISO,
    .sclk_io_num = SPI_SCLK,
    .quadwp_io_num = DISP_SPI_IO2,
    .quadhd_io_num = DISP_SPI_IO3,
    .max_transfer_sz = SPI_BUS_MAX_TRANSFER_SZ,
};

/*********************
 *      SD CARD
 *********************/
// definitions
#define MOUNT_POINT "/sdcard"

// attributes
sdmmc_card_t *card;
const char mount_point[] = MOUNT_POINT;

esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = false,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
};
sdmmc_host_t host = SDSPI_HOST_DEFAULT();
sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();

/*********************
 *      DISPLAY
 *********************/

spi_device_interface_config_t devcfg={
    .clock_speed_hz = DISPLAY_CLOCK_SPEED_HZ,
    .mode = DISPLAY_SPI_MODE,
    .spics_io_num=TFT_CS,              // CS pin
    .input_delay_ns=DISPLAY_INPUT_DELAY_NS,
    .queue_size=DISPLAY_TRANSACTION_POOL_SIZE,
    .pre_cb=NULL,
    .post_cb=NULL
};


esp_err_t initDevices(void) {
	esp_err_t ret = ESP_FAIL;
	host.slot = SPI_HOST_DEVICE;

	/*********************
	 *      Init SPI Bus
	 *********************/
	ret = spi_bus_initialize(host.slot, &bus_cfg, SPI_DMA_CHAN);
	assert(ret == ESP_OK);

	/*********************
	 *      SD CARD
	 *********************/
	// This initializes the slot without card detect (CD) and write protect (WP) signals.
	// Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.

	slot_config.gpio_cs = SD_CS;
	slot_config.host_id = host.slot;

	ESP_LOGI(TAG, "Mounting filesystem");
	ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config,
			&mount_config, &card);

	if (ret != ESP_OK) {
		if (ret == ESP_FAIL) {
			ESP_LOGE(TAG, "Failed to mount filesystem. ");
		} else {
			ESP_LOGE(TAG, "Failed to initialize the card (%s). "
					"Make sure SD card lines have pull-up resistors in place.",
					esp_err_to_name(ret));
		}
		return ESP_FAIL;
	}
	ESP_LOGI(TAG, "Filesystem mounted");

	// Card has been initialized, print its properties
	sdmmc_card_print_info(stdout, card);
	/*********************
	 *      Display
	 *********************/
	disp_spi_add_device(SPI_HOST_DEVICE);
	disp_driver_init();

	return ESP_OK;
}

esp_err_t testSDCard(void) {
	esp_err_t ret = ESP_FAIL;
	//initSDCard();

	// Use POSIX and C standard library functions to work with files.

	// First create a file.
	const char *file_hello = MOUNT_POINT"/hello.txt";

	ESP_LOGI(TAG, "Opening file %s", file_hello);
	FILE *f = fopen(file_hello, "w");
	if (f == NULL) {
		ESP_LOGE(TAG, "Failed to open file for writing");
		return ret;
	}
	fprintf(f, "Hello %s!\n", card->cid.name);
	fclose(f);
	ESP_LOGI(TAG, "File written");

	const char *file_foo = MOUNT_POINT"/foo.txt";

	// Check if destination file exists before renaming
	struct stat st;
	if (stat(file_foo, &st) == 0) {
		// Delete it if it exists
		unlink(file_foo);
	}

	// Rename original file
	ESP_LOGI(TAG, "Renaming file %s to %s", file_hello, file_foo);
	if (rename(file_hello, file_foo) != 0) {
		ESP_LOGE(TAG, "Rename failed");
		return ret;
	}

	// Open renamed file for reading
	ESP_LOGI(TAG, "Reading file %s", file_foo);
	f = fopen(file_foo, "r");
	if (f == NULL) {
		ESP_LOGE(TAG, "Failed to open file for reading");
		return ret;
	}

	// Read a line from file
	char line[64];
	fgets(line, sizeof(line), f);
	fclose(f);

	// Strip newline
	char *pos = strchr(line, '\n');
	if (pos) {
		*pos = '\0';
	}
	ESP_LOGI(TAG, "Read from file: '%s'", line);
	//deinitSDCard();

	return ret;
}


