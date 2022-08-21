#ifndef SDCARD_H_
#define SDCARD_H_

// includes
#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "board_def.h"

// definitions
#define MOUNT_POINT "/sdcard"
#define SPI_DMA_CHAN    1

// attributes
sdmmc_card_t *card;

// functions
esp_err_t initSDCard(void);
esp_err_t deinitSDCard(void);
esp_err_t testSDCard(void);

#endif
