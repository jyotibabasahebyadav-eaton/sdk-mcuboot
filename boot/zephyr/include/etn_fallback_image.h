/**
 *****************************************************************************************
 *	@file etn_fallback_image.h
 *
 *	@brief eaton mcuboot fallback image header file
 *
 *	@details this is fallback image, used to store firmware image in fallback area. 
 *
 *	@version C Style Guide Version 1.0
 *
 *	@copyright 2022 Eaton Corporation. All Rights Reserved.
 *
 *****************************************************************************************
 */
#ifndef ETN_FALLBACK_IMAGE_H
#define ETN_FALLBACK_IMAGE_H

/*
 *****************************************************************************************
 *		Headers
 *****************************************************************************************
 */
#include <zephyr.h>
#include <sys/printk.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXT_FLASH_START_ADDR                    0x00000
#define EXT_FLASH_END_ADDR                      0x100000

/*
#define EXT_FLASH_SECONDARY_AREA_START_ADDR     0x00000
#define EXT_FLASH_SECONDARY_AREA_END_ADDR       0x64000
#define EXT_FLASH_SECONDARY_AREA_SIZE           0x64000

#define EXT_FLASH_FALLBACK_AREA_START_ADDR      0x80000
#define EXT_FLASH_FALLBACK_AREA_END_ADDR        0xE4000
#define EXT_FLASH_FALLBACK_AREA_SIZE            0x64000

#define INT_FLASH_PRIMARY_AREA_START_ADDR      0xC000
#define INT_FLASH_PRIMARY_AREA_END_ADDR        0x70000
#define INT_FLASH_PRIMARY_AREA_SIZE            0x64000

*/

#define IMAGE_STORAGE_DATA_VALID                0x0107

#define INT_FLASH_PRIMARY_AREA_START_ADDR      0x10000
#define INT_FLASH_PRIMARY_AREA_END_ADDR        0x6e000
#define INT_FLASH_PRIMARY_AREA_SIZE            0x6e000

#define EXT_FLASH_SECONDARY_AREA_START_ADDR     0x00000
#define EXT_FLASH_SECONDARY_AREA_END_ADDR       0x60000
#define EXT_FLASH_SECONDARY_AREA_SIZE           0x60000

#define EXT_FLASH_FALLBACK_AREA_START_ADDR      0x80000
#define EXT_FLASH_FALLBACK_AREA_END_ADDR        0xE0000
#define EXT_FLASH_FALLBACK_AREA_SIZE            0x60000

#define EXT_FLASH_IMAGE_STATUS_START_ADDR       0xF2000
#define EXT_FLASH_IMAGE_STATUS_END_ADDR         0xF3000
#define EXT_FLASH_IMAGE_STATUS_SIZE             0x1000

#define DCI_NV_DATA_START                       0x7F000
#define DCI_NV_DATA_END                         0x80000
#define EXT_FLASH_SIZE_POST_DCI                 0x80000


#define EXT_FLASH_MIN_ERASE_SIZE                0x1000

#define READ_WRITE_SIZE 128

#define ERASE_EXTERNAL_FLASH_FIRST_TIME         0

#define MCUBOOT_REBOOT_THRESHOLD_MAX_VALUE     2
#define CHAMP_STABLE_THRESHOLD_MAX_VALUE       2

#define APP_STABILITY_CHECK_INTERVAL    10000

enum fb_copy_request{
    FB_CPY_RQT_NONE=0,
    FB_CPY_RQT_TO_FB,
    FB_CPY_RQT_TO_SE
};

enum fb_request_status{
    FB_RQT_STATUS_NONE=0,
    FB_RQT_STATUS_FAILED,
    FB_RQT_STATUS_COMPLETED,
};

enum fb_running_location{
    FB_RUN_NONE=0,
    FB_RUN_MCUBOOT,
    FB_RUN_CHAMP,
    FB_RUN_BOTH
};

enum fb_image_header{
    FB_IMAGE_HEADER_NONE=0,
    FB_IMAGE_HEADER_OK,
    FB_IMAGE_HEADER_WRONG    
};

enum fb_image_use{
    FB_IMAGE_USE_NONE=0,
    FB_IMAGE_USE_YES,
    FB_IMAGE_USE_NO   
};

enum fb_image_info_status
{
    IMG_INF_DONOT_USE=0,
    IMG_INF_INVALID_MAGIC_ID,
    IMG_INF_INIT_READ_DONE,
};

enum fb_flash_type{
    FLASH_TYPE_INTERNAL=0,
    FLASH_TYPE_EXTERNAL,
};

enum fb_partition_type{
    PARTITION_TYPE_NONE=0,
    PARTITION_TYPE_PRIMARY,
    PARTITION_TYPE_SECONDARY,
    PARTITION_TYPE_FALLBACK,
};

enum fb_debug{
    FB_DEBUG_NO=0,
    FB_DEBUG_YES
};

enum fb_test_sm{
    FB_TEST_STATE_NONE=0,
    FB_TEST_STATE_CPY_RQT_TO_FB,
    FB_TEST_STATE_CPY_RQT_SUCCESS,
    FB_TEST_STATE_CPY_RQT_FAILED,
    FB_TEST_STATE_UNKNOW
};

struct fallback_process_check{

    uint8_t init_variable_done;
    uint8_t mcuboot_reboot_cntr;
    uint8_t mcuboot_reboot_threshold;
    uint8_t mcuboot_fallback_enable_flag;

    uint8_t  champ_app_stable_flag;
    uint8_t  champ_app_stable_cntr;
    uint16_t app_stable_check_interval;
    uint8_t  champ_app_stable_threshold;
    
    uint8_t  pm_to_fb_cpy_rqt;
    uint8_t  fb_to_se_cpy_rqt;

    uint8_t  pm_to_fb_rqt_status;
    uint8_t  fb_to_se_rqt_status;

    uint8_t fb_test_state_machine;
};

struct partition_image_info{
    uint16_t valid;
    uint16_t type;
    uint16_t version;
    uint32_t header_size;
    uint32_t image_size;
    uint16_t header_crc;
    uint16_t image_crc;
    uint16_t status;
    uint8_t  header_status;
    uint8_t  use_flag;
};

struct champ_image_info{
    struct partition_image_info pm_mcuboot;
    struct partition_image_info se_mcuboot;
    struct partition_image_info fb_mcuboot;

    struct fallback_process_check check;
};

struct fb_flash_data{
    bool ext_flash_status;
    bool int_flash_status;
    uint8_t fb_running_loc;
    bool enable_debug;
    struct champ_image_info image_info;
};



struct champ_image_version {
    uint8_t iv_major;
    uint8_t iv_minor;
    uint16_t iv_revision;
    uint32_t iv_build_num;
};

/** Image header.  All fields are in little endian byte order. */
struct champ_image_header {
    uint32_t ih_magic;
    uint32_t ih_load_addr;
    uint16_t ih_hdr_size;           /* Size of image header (bytes). */
    uint16_t ih_protect_tlv_size;   /* Size of protected TLV area (bytes). */
    uint32_t ih_img_size;           /* Does not include header. */
    uint32_t ih_flags;              /* IMAGE_F_[...]. */
    struct champ_image_version ih_ver;
    uint32_t _pad1;
};


void etn_fallback_image_test(void);
void etn_fallback_image_check(void);

void etn_fb_flash_init(void);
bool etn_fb_setup_ext_flash(void);
bool etn_fb_setup_int_flash(void);

int  etn_fb_flash_erase(bool flash_type, uint32_t address, uint32_t length);
int  etn_fb_flash_write(bool flash_type, uint32_t address, uint32_t length, uint8_t debug, uint8_t debug_type, const void * data);
int  etn_fb_flash_read(bool flash_type, uint32_t address, uint32_t length, uint8_t debug, uint8_t debug_type);
int  etn_fb_flash_read_to_buf(bool flash_type, uint32_t address, uint32_t length, void *data, uint8_t debug);

int etn_fb_flash_save_image_status(void);

uint16_t etn_fb_flash_cal_crc(bool flash_type, uint32_t address, uint32_t length);

void etn_fallback_set_run_location(uint8_t loc);

int  etn_fb_read_image_info(uint8_t debug);

int  etn_fb_check_image_info(uint8_t partition_type,uint8_t loc);

int etn_fb_check_mcuboot_reboot_counter(void);
int etn_fb_check_fallback_logic_parameters(void);
int etn_fb_check_is_fallback_copied_already_to_secondary(void);

int etn_fb_copy_content(uint8_t from_partition, uint8_t to_partition, uint32_t from_address, uint32_t to_address, uint32_t length);

int etn_fb_write_mcuboot_trailer(uint8_t partition_type);

int etn_fb_read_image_header(uint8_t partition_type);
 
uint16_t cb_cal_crc16( uint8_t const* data, uint32_t length, uint16_t init_crc );


void etn_fb_request_mcuboot_for_fallback_copy(void);
void etn_fb_check_image_copy_primary_to_fallback(void);
void etn_fb_check_image_copy_fallback_to_secondary(void);

void test_fallback_apis(void);
void test_copy_content(void);
void test_crc_calculation(void);
void test_check_image_info(void);

#ifdef __cplusplus
}
#endif

#endif