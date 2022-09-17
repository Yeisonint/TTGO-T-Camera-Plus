/*
 * Display.h
 *
 *  Created on: 12/09/2022
 *      Author: Yeisonint
 */

#ifndef COMPONENTS_DISPLAY_H_
#define COMPONENTS_DISPLAY_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "lv_png.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"


/**********************
 *  STATIC PROTOTYPES
 **********************/
void lv_tick_task(void *arg);
void guiTask(void *pvParameter);
void create_demo_application(void);

void text1(void);
void img(void);
void img_lib_png(void);

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;


#endif


