#include "st7789.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "disp_spi.h"
#include "esp_log.h"
#include "sdkconfig.h"

#define LV_TICK_PERIOD_MS 1

void lv_example(void);
void init_Display(void);
void guiTask(void *pvParameter);
void create_demo_application(void);
void lv_tick_task(void *arg);

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;
