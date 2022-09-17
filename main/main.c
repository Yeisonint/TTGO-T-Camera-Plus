#include "main.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    printf("Hello from app_main!\n");
    ESP_LOGI(TAG, "Hello from app_main!\n");

    assert(initDevices() == ESP_OK);

    xTaskCreatePinnedToCore(guiTask, "gui", 4096*2, NULL, 0, NULL, 1);

    while (true) {
    	//testSDCard();
    	printf("Show text!\n");
    	text1();
        sleep(5);
        printf("Show img!\n");
        img_lib_png();
        sleep(5);
    }
}
