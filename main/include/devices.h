/*
 * devices.h
 *
 *  Created on: 13/09/2022
 *      Author: Yeisonint
 */

#ifndef MAIN_INCLUDE_DEVICES_H_
#define MAIN_INCLUDE_DEVICES_H_

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "board_def.h"
#include "lvgl_tft/disp_spi.h"
#include "lv_png.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"

/*********************
 *      DEFINES
 *********************/
#define LV_TICK_PERIOD_MS 1
#define DISPLAY_TRANSACTION_POOL_SIZE 50
#define DISPLAY_CLOCK_SPEED_HZ  (40*1000*1000)
#define DISPLAY_SPI_MODE    (2)
#define DISPLAY_INPUT_DELAY_NS (0)
#define DISPLAY_BUS_MAX_TRANSFER_SZ 240*240
#define DISPLAY_SPI_IO2 -1
#define DISPLAY_SPI_IO3 -1


esp_err_t initDevices(void);
esp_err_t testSDCard(void);

#endif /* MAIN_INCLUDE_DEVICES_H_ */
