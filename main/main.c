#include <stdio.h>
#include <board_def.h>
#include <unistd.h>
#include "esp_log.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    printf("Hello from app_main!\n");
    ESP_LOGI(TAG, "Hello from app_main!\n");

    while (true) {
        sleep(1);
    }
}
