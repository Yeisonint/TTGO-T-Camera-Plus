/**
 * @file lv_fs_if.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
/*File system interface*/
#define LV_USE_FS_IF	1
#if LV_USE_FS_IF
#  define LV_FS_IF_FATFS    'S'
#  define LV_FS_IF_PC       '\0'
#endif  /*LV_USE_FS_IF*/

#if LV_USE_FS_IF

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
#if LV_FS_IF_FATFS != '\0'
void lv_fs_if_fatfs_init(void);
#endif

#if LV_FS_IF_PC != '\0'
void lv_fs_if_pc_init(void);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif
