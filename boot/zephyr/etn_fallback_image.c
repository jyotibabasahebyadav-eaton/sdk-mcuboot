/**
 *****************************************************************************************
 *	@file etn_fallback_image.c
 *
 *	@brief ETN fallback image source file
 *
 *	@details this is fallback image, used to store firmware image in fallback area. 
 *
 *	@version C Style Guide Version 1.0
 *
 *	@copyright 2022 ETN Corporation. All Rights Reserved.
 *
 *****************************************************************************************
 */

/*
 *****************************************************************************************
 *		Headers
 *****************************************************************************************
 */
#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/flash.h>
#include <device.h>
#include <etn_fallback_image.h>

const uint16_t table1[256] =
{
0x0000U, 0x1189U, 0x2312U, 0x329bU, 0x4624U, 0x57adU, 0x6536U, 0x74bfU,

0x8c48U, 0x9dc1U, 0xaf5aU, 0xbed3U, 0xca6cU, 0xdbe5U, 0xe97eU, 0xf8f7U,

0x1081U, 0x0108U, 0x3393U, 0x221aU, 0x56a5U, 0x472cU, 0x75b7U, 0x643eU,

0x9cc9U, 0x8d40U, 0xbfdbU, 0xae52U, 0xdaedU, 0xcb64U, 0xf9ffU, 0xe876U,

0x2102U, 0x308bU, 0x0210U, 0x1399U, 0x6726U, 0x76afU, 0x4434U, 0x55bdU,

0xad4aU, 0xbcc3U, 0x8e58U, 0x9fd1U, 0xeb6eU, 0xfae7U, 0xc87cU, 0xd9f5U,

0x3183U, 0x200aU, 0x1291U, 0x0318U, 0x77a7U, 0x662eU, 0x54b5U, 0x453cU,

0xbdcbU, 0xac42U, 0x9ed9U, 0x8f50U, 0xfbefU, 0xea66U, 0xd8fdU, 0xc974U,

0x4204U, 0x538dU, 0x6116U, 0x709fU, 0x0420U, 0x15a9U, 0x2732U, 0x36bbU,

0xce4cU, 0xdfc5U, 0xed5eU, 0xfcd7U, 0x8868U, 0x99e1U, 0xab7aU, 0xbaf3U,

0x5285U, 0x430cU, 0x7197U, 0x601eU, 0x14a1U, 0x0528U, 0x37b3U, 0x263aU,

0xdecdU, 0xcf44U, 0xfddfU, 0xec56U, 0x98e9U, 0x8960U, 0xbbfbU, 0xaa72U,

0x6306U, 0x728fU, 0x4014U, 0x519dU, 0x2522U, 0x34abU, 0x0630U, 0x17b9U,

0xef4eU, 0xfec7U, 0xcc5cU, 0xddd5U, 0xa96aU, 0xb8e3U, 0x8a78U, 0x9bf1U,

0x7387U, 0x620eU, 0x5095U, 0x411cU, 0x35a3U, 0x242aU, 0x16b1U, 0x0738U,

0xffcfU, 0xee46U, 0xdcddU, 0xcd54U, 0xb9ebU, 0xa862U, 0x9af9U, 0x8b70U,

0x8408U, 0x9581U, 0xa71aU, 0xb693U, 0xc22cU, 0xd3a5U, 0xe13eU, 0xf0b7U,

0x0840U, 0x19c9U, 0x2b52U, 0x3adbU, 0x4e64U, 0x5fedU, 0x6d76U, 0x7cffU,

0x9489U, 0x8500U, 0xb79bU, 0xa612U, 0xd2adU, 0xc324U, 0xf1bfU, 0xe036U,

0x18c1U, 0x0948U, 0x3bd3U, 0x2a5aU, 0x5ee5U, 0x4f6cU, 0x7df7U, 0x6c7eU,

0xa50aU, 0xb483U, 0x8618U, 0x9791U, 0xe32eU, 0xf2a7U, 0xc03cU, 0xd1b5U,

0x2942U, 0x38cbU, 0x0a50U, 0x1bd9U, 0x6f66U, 0x7eefU, 0x4c74U, 0x5dfdU,

0xb58bU, 0xa402U, 0x9699U, 0x8710U, 0xf3afU, 0xe226U, 0xd0bdU, 0xc134U,

0x39c3U, 0x284aU, 0x1ad1U, 0x0b58U, 0x7fe7U, 0x6e6eU, 0x5cf5U, 0x4d7cU,

0xc60cU, 0xd785U, 0xe51eU, 0xf497U, 0x8028U, 0x91a1U, 0xa33aU, 0xb2b3U,

0x4a44U, 0x5bcdU, 0x6956U, 0x78dfU, 0x0c60U, 0x1de9U, 0x2f72U, 0x3efbU,

0xd68dU, 0xc704U, 0xf59fU, 0xe416U, 0x90a9U, 0x8120U, 0xb3bbU, 0xa232U,

0x5ac5U, 0x4b4cU, 0x79d7U, 0x685eU, 0x1ce1U, 0x0d68U, 0x3ff3U, 0x2e7aU,

0xe70eU, 0xf687U, 0xc41cU, 0xd595U, 0xa12aU, 0xb0a3U, 0x8238U, 0x93b1U,

0x6b46U, 0x7acfU, 0x4854U, 0x59ddU, 0x2d62U, 0x3cebU, 0x0e70U, 0x1ff9U,

0xf78fU, 0xe606U, 0xd49dU, 0xc514U, 0xb1abU, 0xa022U, 0x92b9U, 0x8330U,

0x7bc7U, 0x6a4eU, 0x58d5U, 0x495cU, 0x3de3U, 0x2c6aU, 0x1ef1U, 0x0f78U

};

static struct fb_flash_data fb_data;

const char *extflashname1 = "IS25";
const struct device *dev_extflash1;
const char *intflashname = "image-0";
const struct device *dev_intflash;

struct champ_image_header img_hdr;

void etn_fallback_image_check(void)
{
    cb_fota_flash_init();

    //yogesh todo remove later
    if( ERASE_EXTERNAL_FLASH_FIRST_TIME )
    {
        if( fb_data.fb_running_loc == FB_RUN_MCUBOOT )
        {
            printk("erasing external flash\n");
            // etn_fb_flash_erase(FLASH_TYPE_EXTERNAL, EXT_FLASH_START_ADDR, EXT_FLASH_END_ADDR);
            /* Ubaid: To not erase reset flag value & DCI data value */
            etn_fb_flash_erase(FLASH_TYPE_EXTERNAL, EXT_FLASH_START_ADDR, DCI_NV_DATA_START);
            etn_fb_flash_erase(FLASH_TYPE_EXTERNAL, DCI_NV_DATA_END, EXT_FLASH_SIZE_POST_DCI);
        }
    }
    else
    {
        etn_fb_read_image_info(FB_DEBUG_YES);
        
        /*  testing fallback apis */
        //test_fallback_apis();
        etn_fb_check_image_info(PARTITION_TYPE_PRIMARY, FB_RUN_MCUBOOT);
        etn_fb_check_image_info(PARTITION_TYPE_SECONDARY,FB_RUN_MCUBOOT);
        etn_fb_check_image_info(PARTITION_TYPE_FALLBACK, FB_RUN_MCUBOOT);

        etn_fb_check_fallback_logic_parameters();
        

        if( fb_data.fb_running_loc == FB_RUN_MCUBOOT )
        {
            

            /* 
                when we are in mcuboot area means device rebooted. 
                1. check if image copied already from fallback to secondary area
                2. check mcuboot reboot counter
                    a. increment mcuboot counter
                    b. if greater than threshold, set fb_to_se_cpy_rqt
                    c. reset mcuboot_reboot_counter to 0
                3. check copy image primary to fallback request
                4. check copy image fallback to secondary request
            */

            etn_fb_check_is_fallback_copied_already_to_secondary();
            etn_fb_check_mcuboot_reboot_counter();
            etn_fb_check_image_copy_primary_to_fallback();
            etn_fb_check_image_copy_fallback_to_secondary();
        }

        if( fb_data.fb_running_loc == FB_RUN_CHAMP )
        {
            switch (fb_data.image_info.check.fb_test_state_machine)
            {
            case FB_TEST_STATE_NONE:
                printk("FB_TEST_STATE_NONE\n");
                printk("requesting mcuboot to copy image from primary to fallback\n");
                etn_fb_request_mcuboot_for_fallback_copy();
                printk("requesting mcuboot to copy image done\n");
                fb_data.image_info.check.fb_test_state_machine = FB_TEST_STATE_CPY_RQT_TO_FB;
                etn_fb_flash_save_image_status();
                printk("do manual reboot\n");

                break;

            case FB_TEST_STATE_CPY_RQT_TO_FB:
                printk("FB_TEST_STATE_CPY_RQT_TO_FB\n");
                if( fb_data.image_info.check.pm_to_fb_rqt_status == FB_RQT_STATUS_COMPLETED )
                {
                    printk("image copy to fallback completed\n");
                    fb_data.image_info.check.fb_test_state_machine = FB_TEST_STATE_CPY_RQT_SUCCESS;
                    etn_fb_flash_save_image_status();
                    printk("do manual reboot\n");
                }
                
                if( fb_data.image_info.check.pm_to_fb_rqt_status == FB_RQT_STATUS_FAILED )
                {
                    printk("image copy to fallback failed\n");
                    fb_data.image_info.check.fb_test_state_machine = FB_TEST_STATE_CPY_RQT_FAILED;
                    etn_fb_flash_save_image_status();
                    printk("do manual reboot\n");
                }

                if( fb_data.image_info.check.pm_to_fb_rqt_status == FB_RQT_STATUS_NONE )
                {
                    printk("image copy to fallback unknow state\n");
                    fb_data.image_info.check.fb_test_state_machine = FB_TEST_STATE_UNKNOW;
                    etn_fb_flash_save_image_status();
                    printk("do manual reboot\n");
                }

                break;
            
            case FB_TEST_STATE_CPY_RQT_SUCCESS:
                printk("FB_TEST_STATE_CPY_RQT_SUCCESS\n");
                break;

            case FB_TEST_STATE_CPY_RQT_FAILED:
                printk("FB_TEST_STATE_CPY_RQT_FAILED\n");
                break;

            case FB_TEST_STATE_UNKNOW:
                printk("FB_TEST_STATE_UNKNOW\n");
                printk("check your logic\n");
                break;

            default:
                printk("default\n");
                fb_data.image_info.check.fb_test_state_machine = FB_TEST_STATE_NONE;
                etn_fb_flash_save_image_status();
                printk("do manual reboot\n");
                break;
            }
        }
    }

}

void cb_fota_flash_init(void)
{
    uint8_t data_buf[READ_WRITE_SIZE];
    uint8_t cntr=0;
    uint32_t firmware_size;
    
    fb_data.enable_debug = FB_DEBUG_YES;

    fb_data.ext_flash_status = etn_fb_setup_ext_flash();
    fb_data.int_flash_status = etn_fb_setup_int_flash();
}

bool etn_fb_setup_ext_flash(void)
{
    bool status=0;

    /* get device binding to is25 */
	dev_extflash1 = device_get_binding(extflashname1);

	if (dev_extflash1 == NULL)
	{
		printk("device binding to external flash failed\n");
		status = 0;
	}
	else
	{
		printk("device binding to external flash success\n");
        status = 1;
	}

    return status;
}

bool etn_fb_setup_int_flash(void)
{
    bool status=0;

    /* get device binding to internal flash */
    dev_intflash = device_get_binding( DT_CHOSEN_ZEPHYR_FLASH_CONTROLLER_LABEL );

	if (dev_intflash == NULL)
	{
		printk("device binding to internal flash failed\n");
		status = 0;
	}
	else
	{
		printk("device binding to internal flash success\n");
        status = 1;
	}

    return status;
}

int  etn_fb_flash_erase(bool flash_type, uint32_t address, uint32_t length)
{
    int flash_status=0;

    if( flash_type == FLASH_TYPE_INTERNAL)
    {
        if( fb_data.int_flash_status == 0 )
        {
            printk("no erase operation, internal flash config failed\n");
            return 0;
        }
        else
        {
            flash_status = flash_erase( dev_intflash, address, length );
            if( flash_status == 0)
            {
                printk("internal flash erase successful addr:%04X len:%04X\n", address, length);
            }
            else
            {
                printk("internal flash erase failed addr:%04X len:%04X err:%d\n",address, length, flash_status);
            }
        }
    }
    else
    {
        if( fb_data.ext_flash_status == 0 )
        {
            printk("no erase operation, external flash config failed\n");
            return 0;
        }
        else
        {
            flash_status = flash_erase( dev_extflash1, address, length );
            if( flash_status == 0)
            {
                printk("external flash erase successful addr:%04X len:%04X\n", address, length);
            }
            else
            {
                printk("external flash erase failed addr:%04X len:%04X err:%d\n",address, length, flash_status);
            }
        }
    }
    return flash_status;
}

int  etn_fb_flash_write(bool flash_type, uint32_t address, uint32_t length, uint8_t debug, uint8_t debug_type, const void * data)
{
    int status=0;
    int loop_cntr=0;

    if( flash_type == FLASH_TYPE_INTERNAL)
    {
        if( fb_data.int_flash_status == 0 )
        {
            printk("no write operation, internal flash config failed\n");
            return -1;
        }
        else
        {
            status = flash_write(dev_intflash, address,data,length);
            if(status == 0)
            {
                if( debug )
                {
                    printk("internal flash write success\n");
                    if(debug_type == 0 )
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%02X ", ((uint8_t*) data)[loop_cntr]);
                        }
                        printk("\n");
                    }
                    else
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%c", ((uint8_t*) data)[loop_cntr]);
                        }
                        printk("\n");
                    }
                }
            }
            else
            {
                printk("internal flash write failed err:%d\n", status);
            }
        }
    }
    else
    {
        if( fb_data.ext_flash_status == 0 )
        {
            printk("no write operation, external flash config failed\n");
            return -1;
        }
        else
        {
            status = flash_write(dev_extflash1, address,data,length);
            if(status == 0)
            {                
                if( debug )
                {
                    printk("external flash write success\n");
                    if(debug_type == 0 )
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%02X ", ((uint8_t*) data)[loop_cntr]);
                        }
                        printk("\n");
                    }
                    else
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%c", ((uint8_t*) data)[loop_cntr]);
                        }
                        printk("\n");
                    }
                }
            }
            else
            {
                printk("external flash write failed err:%d\n", status);
            }
        }
    }
    
    return status;
}

int  etn_fb_flash_read(bool flash_type, uint32_t address, uint32_t length, uint8_t debug, uint8_t debug_type)
{
    int flash_status=0;
    int loop_cntr;
    uint8_t data_buf[READ_WRITE_SIZE];
	uint32_t len=0;

    if( flash_type == FLASH_TYPE_INTERNAL)
    {
        if( fb_data.int_flash_status == 0 )
        {
            printk("no read operation, internal flash config failed\n");
            return 0;
        }
        else
        {
            printk("\ninternal reading %04X bytes from address %04X\n", length, address);
            while( len < length )
            {
                flash_status = flash_read( dev_intflash, address, data_buf, READ_WRITE_SIZE );
                if( flash_status == 0)
                {
                    if(debug_type == 0 )
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%02X ", data_buf[loop_cntr]);
                        }
                        printk("\n");
                    }
                    else
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%c", data_buf[loop_cntr]);
                        }
                        printk("\n");
                    }
                }
                else
                {
                    printk("internal flash read failed at %d\n", address);
                }
                address = address + READ_WRITE_SIZE;
                len = len + READ_WRITE_SIZE;
            }
        }
    }
    else
    {
        if( fb_data.ext_flash_status == 0 )
        {
            printk("no read operation, external flash config failed\n");
            return 0;
        }
        else
        {
            printk("\n external reading %04X bytes from address %04X\n", length, address);
            while( len < length )
            {
                flash_status = flash_read( dev_extflash1, address, data_buf, READ_WRITE_SIZE );
                if( flash_status == 0)
                {
                    if(debug_type == 0 )
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%02X ", data_buf[loop_cntr]);
                        }
                        printk("\n");
                    }
                    else
                    {
                        for(loop_cntr=0;loop_cntr<READ_WRITE_SIZE;loop_cntr++)
                        {
                            printk("%c", data_buf[loop_cntr]);
                        }
                        printk("\n");
                    }
                }
                else
                {
                    printk("serial flash read failed at %d\n", address);
                }
                address = address + READ_WRITE_SIZE;
                len = len + READ_WRITE_SIZE;
            }
        }
    }

    return flash_status;
}

int  etn_fb_flash_read_to_buf(bool flash_type, uint32_t address, uint32_t length, void *data, uint8_t debug)
{
    int flash_status=0;

    if( flash_type == FLASH_TYPE_INTERNAL)
    {
        if( fb_data.int_flash_status == 0 )
        {
            printk("no read operation, internal flash config failed\n");
            return -1;
        }
        else
        {
            if( debug )
            {
                printk("\ninternal reading %04X bytes from address %04X\n", length, address);
            }
            flash_status = flash_read( dev_intflash, address, data, length );
        }
    }
    else
    {
        if( fb_data.ext_flash_status == 0 )
        {
            printk("no read operation, external flash config failed\n");
            return -1;
        }
        else
        {
            if( debug )
            {
                printk("\nexternal reading %04X bytes from address %04X\n", length, address);
            }
            flash_status = flash_read( dev_extflash1, address, data, length );
        }
    }

    if( flash_status != 0 )
    {
        printk("reading data failed\n");
    }

    return flash_status;
}

int  etn_fb_read_image_info(uint8_t debug)
{
    int flash_status;

    flash_status = etn_fb_flash_read_to_buf(FLASH_TYPE_EXTERNAL, EXT_FLASH_IMAGE_STATUS_START_ADDR, sizeof(struct champ_image_info), &fb_data.image_info, 1);
    if( flash_status !=0 )
    {
        printk("fail to read image info err:%d\n", flash_status);
    }
    else
    {
        if( debug )
        {
            if( fb_data.fb_running_loc == FB_RUN_MCUBOOT )
            {
                printk("champ image info loc mcuboot\n");
            }
            
            if( fb_data.fb_running_loc == FB_RUN_CHAMP )
            {
                printk("champ image info loc champ\n");
            }
            
            printk("\n\n\n\n\n\n");
            printk("primary mcuboot: ");
            printk("valid:%X ", fb_data.image_info.pm_mcuboot.valid);
            printk("type:%X ", fb_data.image_info.pm_mcuboot.type);
            printk("version:%X ", fb_data.image_info.pm_mcuboot.version);
            printk("header_size:%X ", fb_data.image_info.pm_mcuboot.header_size);
            printk("header_crc:%X ", fb_data.image_info.pm_mcuboot.header_crc);
            printk("image_size:%X ", fb_data.image_info.pm_mcuboot.image_size);
            printk("image_crc:%X ", fb_data.image_info.pm_mcuboot.image_crc);
            printk("header_status:%X ", fb_data.image_info.pm_mcuboot.header_status);
            printk("use_flag:%X ", fb_data.image_info.pm_mcuboot.use_flag);
            printk("status:%X\n", fb_data.image_info.pm_mcuboot.status);

            printk("secondary mcuboot: ");
            printk("valid:%X ", fb_data.image_info.se_mcuboot.valid);
            printk("type:%X ", fb_data.image_info.se_mcuboot.type);
            printk("version:%X ", fb_data.image_info.se_mcuboot.version);
            printk("header_size:%X ", fb_data.image_info.se_mcuboot.header_size);
            printk("header_crc:%X ", fb_data.image_info.se_mcuboot.header_crc);
            printk("image_size:%X ", fb_data.image_info.se_mcuboot.image_size);
            printk("image_crc:%X ", fb_data.image_info.se_mcuboot.image_crc);
            printk("header_status:%X ", fb_data.image_info.se_mcuboot.header_status);
            printk("use_flag:%X ", fb_data.image_info.se_mcuboot.use_flag);
            printk("status:%X\n", fb_data.image_info.se_mcuboot.status);

            printk("fallback mcuboot: ");
            printk("valid:%X ", fb_data.image_info.fb_mcuboot.valid);
            printk("type:%X ", fb_data.image_info.fb_mcuboot.type);
            printk("version:%X ", fb_data.image_info.fb_mcuboot.version);
            printk("header_size:%X ", fb_data.image_info.fb_mcuboot.header_size);
            printk("header_crc:%X ", fb_data.image_info.fb_mcuboot.header_crc);
            printk("image_size:%X ", fb_data.image_info.fb_mcuboot.image_size);
            printk("image_crc:%X ", fb_data.image_info.fb_mcuboot.image_crc);
            printk("header_status:%X ", fb_data.image_info.fb_mcuboot.header_status);
            printk("use_flag:%X ", fb_data.image_info.fb_mcuboot.use_flag);
            printk("status:%X\n", fb_data.image_info.fb_mcuboot.status);


            printk("mcuboot_reboot_cntr:%X\n", fb_data.image_info.check.mcuboot_reboot_cntr);
            printk("mcuboot_reboot_threshold:%X\n", fb_data.image_info.check.mcuboot_reboot_threshold);
            printk("mcuboot_fallback_enable_flag:%X\n", fb_data.image_info.check.mcuboot_fallback_enable_flag);
            printk("champ_app_stable_flag:%X\n", fb_data.image_info.check.champ_app_stable_flag);
            printk("champ_app_stable_cntr:%X\n", fb_data.image_info.check.champ_app_stable_cntr);
            printk("app_stable_check_interval:%X\n", fb_data.image_info.check.app_stable_check_interval);
            printk("champ_app_stable_threshold:%X\n", fb_data.image_info.check.champ_app_stable_threshold);
            printk("pm_to_fb_cpy_rqt:%X\n", fb_data.image_info.check.pm_to_fb_cpy_rqt);
            printk("fb_to_se_cpy_rqt:%X\n", fb_data.image_info.check.fb_to_se_cpy_rqt);
            printk("pm_to_fb_rqt_status:%X\n", fb_data.image_info.check.pm_to_fb_rqt_status);
            printk("fb_to_se_rqt_status:%X\n", fb_data.image_info.check.fb_to_se_rqt_status);
            printk("fb_test_state_machine:%X\n", fb_data.image_info.check.fb_test_state_machine);
            printk("init_variable_done:%X\n", fb_data.image_info.check.init_variable_done);

            printk("\n\n\n\n\n\n");
        }
    }
    
    return flash_status;
}

int etn_fb_flash_save_image_status(void)
{
    int flash_status=0;

    flash_status = etn_fb_flash_erase(FLASH_TYPE_EXTERNAL, EXT_FLASH_IMAGE_STATUS_START_ADDR, EXT_FLASH_IMAGE_STATUS_SIZE);
    if( flash_status == 0 )
    {
        flash_status = etn_fb_flash_write(FLASH_TYPE_EXTERNAL, EXT_FLASH_IMAGE_STATUS_START_ADDR, sizeof(struct champ_image_info), 0,0,&(fb_data.image_info));
        if(flash_status != 0)
        {
            printk("write image info failed err:%d\n", flash_status);
        }
        else
        {
            printk("write image info success\n", flash_status);
            //etn_fb_read_image_info(FB_DEBUG_NO);
        }
    }
    else
    {
        printk("erase image info failed err:%d\n", flash_status);
    }
    
    return flash_status;
}

int  etn_fb_check_image_info(uint8_t partition_type, uint8_t loc)
{
    struct partition_image_info img_info;
    int flash_status;
    int return_status;
    bool save_flag=0;
    uint32_t crc_start_addr=0;
    uint32_t len;
    bool process_flag=0;
    uint8_t flash_type=0;

    printk("checking image info partition %d\n",partition_type);

    if( loc == FB_RUN_MCUBOOT)
    {
        switch (partition_type)
        {
        case PARTITION_TYPE_PRIMARY:
            img_info = fb_data.image_info.pm_mcuboot;
            process_flag=1;
            crc_start_addr = INT_FLASH_PRIMARY_AREA_START_ADDR;
            flash_type = FLASH_TYPE_INTERNAL;
            break;
        case PARTITION_TYPE_SECONDARY:
            img_info= fb_data.image_info.se_mcuboot;
            crc_start_addr = EXT_FLASH_SECONDARY_AREA_START_ADDR;
            process_flag=1;
            flash_type = FLASH_TYPE_EXTERNAL;
            break;
        case PARTITION_TYPE_FALLBACK:
            img_info= fb_data.image_info.fb_mcuboot;
            process_flag=1;
            crc_start_addr = EXT_FLASH_FALLBACK_AREA_START_ADDR;
            flash_type = FLASH_TYPE_EXTERNAL;
            break;
        default:
            process_flag=0;
            break;
        }
    }
    
    if( process_flag )
    {
        /* if not valid, make it valid one */
        if( img_info.valid != 0x0107 )
        {
            img_info.valid = 0x0107;
            img_info.status = IMG_INF_DONOT_USE;
            save_flag = 1;
        }

        /* check for image header status */
        if(img_info.header_status != FB_IMAGE_HEADER_OK)
        {
            flash_status = etn_fb_read_image_header(partition_type);
            if(flash_status == 0)
            {
                if(img_hdr.ih_magic == 0x96F3B83D)
                {
                    img_info.version = img_hdr.ih_ver.iv_major;
                    img_info.version <<=8;
                    img_info.version |= img_hdr.ih_ver.iv_minor;
                    img_info.type = partition_type;
                    
                    img_info.header_size = img_hdr.ih_hdr_size;
                    len = img_info.header_size;
                    img_info.header_crc = etn_fb_flash_cal_crc(flash_type, crc_start_addr, len);

                    img_info.image_size = img_hdr.ih_img_size;
                    crc_start_addr += img_hdr.ih_hdr_size;
                    len = img_info.image_size + 338; //yogesh check this;
                    img_info.image_crc  = etn_fb_flash_cal_crc(flash_type, crc_start_addr, len);
                    
                    img_info.status = IMG_INF_INIT_READ_DONE;
                    img_info.header_status = FB_IMAGE_HEADER_OK;
                }
                else
                {
                    img_info.status = IMG_INF_INVALID_MAGIC_ID;
                    img_info.header_status = FB_IMAGE_HEADER_WRONG;
                    img_info.use_flag = FB_IMAGE_USE_YES;
                    printk("invalid magic number at partition %d\n",partition_type );
                }
            }
            else
            {
                img_info.use_flag = FB_IMAGE_USE_NO;
            } 
            save_flag = 1;
        }
    }

    if( save_flag )
    {
        if( loc == FB_RUN_MCUBOOT)
        {
            switch (partition_type)
            {
            case PARTITION_TYPE_PRIMARY:
                fb_data.image_info.pm_mcuboot = img_info;
                break;
            case PARTITION_TYPE_SECONDARY:
                fb_data.image_info.se_mcuboot = img_info;
                break;
            case PARTITION_TYPE_FALLBACK:
                fb_data.image_info.fb_mcuboot = img_info;
                break;
            default:
                break;
            }
        }

        etn_fb_flash_save_image_status();
        etn_fb_read_image_info(FB_DEBUG_YES);

        /*flash_status = etn_fb_flash_write(FLASH_TYPE_EXTERNAL, EXT_FLASH_IMAGE_STATUS_START_ADDR, sizeof(struct champ_image_info), 0,0,&(fb_data.image_info));
        if(flash_status != 0)
        {
            printk(" write image info failed err:%d\n", flash_status);
        }*/
    }

    return return_status;   
}

int etn_fb_check_fallback_logic_parameters(void)
{
    bool save_flag=0;

    if( fb_data.image_info.check.init_variable_done != 1 )
    {
        fb_data.image_info.check.init_variable_done = 1;
        fb_data.image_info.check.mcuboot_reboot_cntr = 0;
        fb_data.image_info.check.champ_app_stable_cntr = 0;
        fb_data.image_info.check.mcuboot_fallback_enable_flag=0;
        fb_data.image_info.check.champ_app_stable_flag=0;
        fb_data.image_info.check.mcuboot_reboot_threshold = MCUBOOT_REBOOT_THRESHOLD_MAX_VALUE;
        fb_data.image_info.check.champ_app_stable_threshold = CHAMP_STABLE_THRESHOLD_MAX_VALUE;
        fb_data.image_info.check.app_stable_check_interval = APP_STABILITY_CHECK_INTERVAL;
        fb_data.image_info.check.fb_test_state_machine = FB_TEST_STATE_NONE;
        fb_data.image_info.check.pm_to_fb_cpy_rqt = FB_CPY_RQT_NONE;
        fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_NONE;
        fb_data.image_info.check.pm_to_fb_rqt_status=FB_RQT_STATUS_NONE;
        fb_data.image_info.check.fb_to_se_rqt_status=FB_RQT_STATUS_NONE;

        save_flag = 1;
    }

    if( save_flag )
    {
        etn_fb_flash_save_image_status();
        /*flash_status = etn_fb_flash_write(FLASH_TYPE_EXTERNAL, EXT_FLASH_IMAGE_STATUS_START_ADDR, sizeof(struct champ_image_info), 0,0,&(fb_data.image_info));
        if(flash_status != 0)
        {
            printk(" write image info failed err:%d\n", flash_status);
        }*/
    }
}

int etn_fb_copy_content(uint8_t from_partition, uint8_t to_partition, uint32_t from_address, uint32_t to_address, uint32_t length)
{
    uint32_t len=0;
    uint8_t data_buf[READ_WRITE_SIZE];
    int flash_status;
    struct device *dev_from;
    struct device *dev_to;

    switch (from_partition)
    {
    case PARTITION_TYPE_PRIMARY:
        dev_from = dev_intflash;
        break;
    case PARTITION_TYPE_SECONDARY:
        dev_from = dev_extflash1;
        break;
    case PARTITION_TYPE_FALLBACK:
        dev_from = dev_extflash1;
        break;
    default:
        break;
    }

    switch (to_partition)
    {
    case PARTITION_TYPE_PRIMARY:
        dev_to = dev_intflash;
        break;
    case PARTITION_TYPE_SECONDARY:
        dev_to = dev_extflash1;
        break;
    case PARTITION_TYPE_FALLBACK:
        dev_to = dev_extflash1;
        break;
    default:
        break;
    }

    while( len < length )
    {
        flash_status = flash_read( dev_from, from_address, data_buf, READ_WRITE_SIZE );    

        if( flash_status == 0)
        {
            flash_status = flash_write(dev_to, to_address, data_buf, READ_WRITE_SIZE);
            if( flash_status != 0)
            {
                printk("fail to write data to %d, breaking copy chain\n", to_partition);
                len = length;
            }
        }
        else
        {
            printk("fail to read data from %d, breaking copy chain\n", from_partition);
            len = length;    
        }

        len += READ_WRITE_SIZE;
        from_address += READ_WRITE_SIZE;
        to_address += READ_WRITE_SIZE;

        //k_sleep(K_MSEC(1));
    }

    return flash_status;
}

void etn_fallback_set_run_location(uint8_t loc)
{
    fb_data.fb_running_loc = loc;
}

int etn_fb_check_is_fallback_copied_already_to_secondary(void)
{
    int return_status=0;

    printk("need to write code for etn_fb_check_is_fallback_copied_already_to_secondary()\n");
    return return_status;
}

void etn_fb_check_image_copy_fallback_to_secondary(void)
{
    int return_status=0;
    uint16_t from_crc;
    uint16_t to_crc;
    uint32_t from_addr;
    uint32_t to_addr;
    uint32_t length;

    if( fb_data.image_info.check.fb_to_se_cpy_rqt == FB_CPY_RQT_TO_SE)
    {
        printk("copy image fallback to secondary requested\n");
        
        if(fb_data.image_info.fb_mcuboot.status == IMG_INF_INIT_READ_DONE)
        {
            printk("erasing secondary partition\n");
            return_status = etn_fb_flash_erase(FLASH_TYPE_EXTERNAL, EXT_FLASH_SECONDARY_AREA_START_ADDR, EXT_FLASH_SECONDARY_AREA_SIZE);
            if( return_status == 0 )
            {
                printk("erasing secodary success\n");
                printk("coping fallback header from fallback to secondary\n");
                from_addr = EXT_FLASH_FALLBACK_AREA_START_ADDR;
                to_addr = EXT_FLASH_SECONDARY_AREA_START_ADDR;
                length =  fb_data.image_info.fb_mcuboot.header_size;
                return_status = etn_fb_copy_content(PARTITION_TYPE_FALLBACK, PARTITION_TYPE_SECONDARY, from_addr, to_addr, length);
                if(return_status == 0)
                {
                    printk("copying header to secondary done checking crc\n");
                    to_crc = etn_fb_flash_cal_crc(FLASH_TYPE_EXTERNAL, EXT_FLASH_SECONDARY_AREA_START_ADDR, length);
                    if( fb_data.image_info.fb_mcuboot.header_crc == to_crc )
                    {
                        printk("header crc matching\n");
                        printk("coping fallback image to secondary area\n");
                        from_addr = EXT_FLASH_FALLBACK_AREA_START_ADDR + fb_data.image_info.fb_mcuboot.header_size;
                        to_addr = EXT_FLASH_SECONDARY_AREA_START_ADDR + fb_data.image_info.fb_mcuboot.header_size;
                        length =  fb_data.image_info.fb_mcuboot.image_size + 338; //yogesh check this;
                        return_status = etn_fb_copy_content(PARTITION_TYPE_FALLBACK, PARTITION_TYPE_SECONDARY, from_addr, to_addr, length);
                        if( return_status == 0 )
                        {
                            printk("copying image to secondary done checking crc\n");
                            to_crc = etn_fb_flash_cal_crc(FLASH_TYPE_EXTERNAL, to_addr, length);
                            if( fb_data.image_info.fb_mcuboot.image_crc == to_crc )
                            {
                                printk("image crc matching and copy done\n");
                                printk("adding mcuboot triler to secondary\n");
                                return_status = etn_fb_write_mcuboot_trailer(PARTITION_TYPE_SECONDARY);
                                if( return_status == 0)
                                {
                                    printk("adding mcuboot triler to secondary success\n");
                                    fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_NONE;
                                    fb_data.image_info.check.fb_to_se_rqt_status = FB_RQT_STATUS_COMPLETED;
                                    etn_fb_flash_save_image_status();
                                    etn_fb_check_image_info(PARTITION_TYPE_SECONDARY,FB_RUN_MCUBOOT);
                                    //etn_fb_flash_read(FLASH_TYPE_EXTERNAL, EXT_FLASH_SECONDARY_AREA_START_ADDR, EXT_FLASH_SECONDARY_AREA_SIZE, 1, 0);
                                }
                                else
                                {
                                    printk("adding mcuboot triler to secondary failed\n");
                                    fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_NONE;
                                    fb_data.image_info.check.fb_to_se_rqt_status = FB_RQT_STATUS_FAILED;
                                    etn_fb_flash_save_image_status();
                                }
                            }
                            else
                            {
                                printk("image crc mismatching\n");
                                fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_NONE;
                                fb_data.image_info.check.fb_to_se_rqt_status = FB_RQT_STATUS_FAILED;
                                etn_fb_flash_save_image_status();
                            }
                        }
                        else
                        {
                            printk("fail to copy fallback image to secondary\n");
                            fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_NONE;
                            fb_data.image_info.check.fb_to_se_rqt_status = FB_RQT_STATUS_FAILED;
                            etn_fb_flash_save_image_status();
                        }
                    }
                    else
                    {
                        //yogesh todo:: fail reason
                        printk("fail to match header crc with fallback and secondary crc:%X exp:%X\n", to_crc, fb_data.image_info.pm_mcuboot.header_crc);
                        fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_NONE;
                        fb_data.image_info.check.fb_to_se_rqt_status = FB_RQT_STATUS_FAILED;
                        etn_fb_flash_save_image_status();
                    }
                }
                else
                {
                    printk("fail to copy fallback image header to secondary header\n");
                    fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_NONE;
                    fb_data.image_info.check.fb_to_se_rqt_status = FB_RQT_STATUS_FAILED;
                    etn_fb_flash_save_image_status();
                }
            }
            else
            {
                printk("erasing secondary failed err:%d\n", return_status);
            }
        }
        else
        {
            printk("mcuboot fallback image not valid to copy\n");
        }
    }
    else
    {
        printk("no fallback to secondary copy request\n");
    }
}

int etn_fb_check_mcuboot_reboot_counter(void)
{
    int return_status=0;
    bool save_flag=0;

    printk("incrementing reboot counter inside mcuboot\n");
    
    fb_data.image_info.check.mcuboot_reboot_cntr++;
    etn_fb_flash_save_image_status();
    
    /* check if counter is greater than threshold */
    if( fb_data.image_info.check.champ_app_stable_flag == false )
    {
        if( fb_data.image_info.check.mcuboot_reboot_cntr >  fb_data.image_info.check.mcuboot_reboot_threshold)
        {
            printk("device rebooting more than threshold limit\n");
            printk("requesting copy image from fallback to secondary\n");
            fb_data.image_info.check.fb_to_se_cpy_rqt = FB_CPY_RQT_TO_SE;
            fb_data.image_info.check.mcuboot_reboot_cntr=0;
            printk("resetting mcuboot_reboot_cntr to 0\n");
            etn_fb_flash_save_image_status();
        }
    }
    else
    {
        printk("image is stable\n");
    }
    return return_status;
}

void etn_fb_check_image_copy_primary_to_fallback(void)
{
    int return_status=0;
    uint16_t from_crc;
    uint16_t to_crc;
    uint32_t from_addr;
    uint32_t to_addr;
    uint32_t length;

    if( fb_data.image_info.check.pm_to_fb_cpy_rqt == FB_CPY_RQT_TO_FB)
    {
        printk("copy image to fallback requested \n");
        
        if(fb_data.image_info.pm_mcuboot.status == IMG_INF_INIT_READ_DONE)
        {
            printk("erasing fallback partition\n");
            return_status = etn_fb_flash_erase(FLASH_TYPE_EXTERNAL, EXT_FLASH_FALLBACK_AREA_START_ADDR, EXT_FLASH_FALLBACK_AREA_SIZE);
            if( return_status == 0 )
            {
                printk("erasing fallback success\n");
                printk("coping mcuboot header from primary to fallback\n");
                from_addr = INT_FLASH_PRIMARY_AREA_START_ADDR;
                to_addr = EXT_FLASH_FALLBACK_AREA_START_ADDR;
                length =  fb_data.image_info.pm_mcuboot.header_size;
                return_status = etn_fb_copy_content(PARTITION_TYPE_PRIMARY, PARTITION_TYPE_FALLBACK, from_addr, to_addr, length);
                if(return_status == 0)
                {
                    printk("copying header to fallback done checking crc\n");
                    to_crc = etn_fb_flash_cal_crc(FLASH_TYPE_EXTERNAL, EXT_FLASH_FALLBACK_AREA_START_ADDR, length);
                    if( fb_data.image_info.pm_mcuboot.header_crc == to_crc )
                    {
                        printk("header crc matching\n");
                        printk("coping primary image to fallback area\n");
                        from_addr = INT_FLASH_PRIMARY_AREA_START_ADDR + fb_data.image_info.pm_mcuboot.header_size;
                        to_addr = EXT_FLASH_FALLBACK_AREA_START_ADDR + fb_data.image_info.pm_mcuboot.header_size;
                        length =  fb_data.image_info.pm_mcuboot.image_size + 338; //yogesh check this
                        return_status = etn_fb_copy_content(PARTITION_TYPE_PRIMARY, PARTITION_TYPE_FALLBACK, from_addr, to_addr, length);
                        if( return_status == 0 )
                        {
                            printk("copying image to fallback done checking crc\n");
                            to_crc = etn_fb_flash_cal_crc(FLASH_TYPE_EXTERNAL, to_addr, length);
                            if( fb_data.image_info.pm_mcuboot.image_crc == to_crc )
                            {
                                printk("image crc matching and copy done\n");
                                fb_data.image_info.check.pm_to_fb_cpy_rqt = FB_CPY_RQT_NONE;
                                fb_data.image_info.check.pm_to_fb_rqt_status = FB_RQT_STATUS_COMPLETED;
                                etn_fb_flash_save_image_status();
                                etn_fb_check_image_info(PARTITION_TYPE_FALLBACK,FB_RUN_MCUBOOT);
                                //etn_fb_flash_read(FLASH_TYPE_INTERNAL, INT_FLASH_PRIMARY_AREA_START_ADDR, INT_FLASH_PRIMARY_AREA_SIZE, 1, 0);
                                //printk("\n\n\n\n\n\n");
                                //etn_fb_flash_read(FLASH_TYPE_EXTERNAL, EXT_FLASH_FALLBACK_AREA_START_ADDR, EXT_FLASH_FALLBACK_AREA_SIZE, 1, 0);
                                //printk("\n\n\n\n\n\n");
                            }
                            else
                            {
                                printk("image crc mismatching\n");
                                fb_data.image_info.check.pm_to_fb_cpy_rqt = FB_CPY_RQT_NONE;
                                fb_data.image_info.check.pm_to_fb_rqt_status = FB_RQT_STATUS_FAILED;
                                etn_fb_flash_save_image_status();
                            }
                        }
                        else
                        {
                            printk("fail to copy primaey image to fallback\n");
                            fb_data.image_info.check.pm_to_fb_cpy_rqt = FB_CPY_RQT_NONE;
                            fb_data.image_info.check.pm_to_fb_rqt_status = FB_RQT_STATUS_FAILED;
                            etn_fb_flash_save_image_status();
                        }
                    }
                    else
                    {
                        //yogesh todo:: fail reason
                        printk("fail to match header crc with primary and fallback crc:%X exp:%X\n", to_crc, fb_data.image_info.pm_mcuboot.header_crc);
                        fb_data.image_info.check.pm_to_fb_cpy_rqt = FB_CPY_RQT_NONE;
                        fb_data.image_info.check.pm_to_fb_rqt_status = FB_RQT_STATUS_FAILED;
                        etn_fb_flash_save_image_status();
                    }
                }
                else
                {
                    printk("fail to copy primaey image header to fallback header\n");
                    fb_data.image_info.check.pm_to_fb_cpy_rqt = FB_CPY_RQT_NONE;
                    fb_data.image_info.check.pm_to_fb_rqt_status = FB_RQT_STATUS_FAILED;
                    etn_fb_flash_save_image_status();
                }
            }
            else
            {
                printk("erasing fallback failed err:%d\n", return_status);
            }
        }
        else
        {
            printk("mcuboot primary image not valid to copy\n");
        }
    }
}

void etn_fb_request_mcuboot_for_fallback_copy(void)
{
    fb_data.image_info.check.pm_to_fb_cpy_rqt = FB_CPY_RQT_TO_FB;
    fb_data.image_info.check.pm_to_fb_rqt_status = FB_RQT_STATUS_NONE;
    etn_fb_flash_save_image_status();
}

void etn_fallback_image_test(void)
{
    uint8_t cntr;

    cntr=1;
    while(cntr)
    {
        printk("etn_fallback_image_test\n");
	    k_sleep(K_MSEC(1000));
        cntr--;
    }
}

int etn_fb_read_image_header(uint8_t partition_type)
{
    int flash_status;

    if( partition_type == PARTITION_TYPE_PRIMARY )
    {
        flash_status = etn_fb_flash_read_to_buf(FLASH_TYPE_INTERNAL, INT_FLASH_PRIMARY_AREA_START_ADDR, sizeof(struct champ_image_header), &img_hdr,1);
    }
    else if( partition_type == PARTITION_TYPE_SECONDARY )
    {
        flash_status = etn_fb_flash_read_to_buf(FLASH_TYPE_EXTERNAL, EXT_FLASH_SECONDARY_AREA_START_ADDR, sizeof(struct champ_image_header), &img_hdr,1);
    }
    else if( partition_type == PARTITION_TYPE_FALLBACK )
    {
        flash_status = etn_fb_flash_read_to_buf(FLASH_TYPE_EXTERNAL, EXT_FLASH_FALLBACK_AREA_START_ADDR, sizeof(struct champ_image_header), &img_hdr,1);
    }
    else
    {
        printk("Wrong partition type %d\n", partition_type);
    }

    if( flash_status == 0 )
    {
        printk("mcuboot image header info from partition %d:\n", partition_type);
        /*printk("ih_magic:%X ", img_hdr.ih_magic);
        printk("ih_load_addr:%X ", img_hdr.ih_load_addr);
        printk("ih_hdr_size:%X ", img_hdr.ih_hdr_size);
        printk("ih_protect_tlv_size:%X ", img_hdr.ih_protect_tlv_size);
        printk("ih_img_size:%X ", img_hdr.ih_img_size);
        printk("ih_flags:%X ", img_hdr.ih_flags);
        printk("iv_major:%X ", img_hdr.ih_ver.iv_major);
        printk("iv_minor:%X ", img_hdr.ih_ver.iv_minor);
        printk("iv_revision:%X ", img_hdr.ih_ver.iv_revision);
        printk("iv_build_num:%X ", img_hdr.ih_ver.iv_build_num);
        printk("_pad1:%X ", img_hdr._pad1);*/
    }
    else
    {
        printk("failed to read image header\n");
    }

    return flash_status;
}

int etn_fb_write_mcuboot_trailer(uint8_t partition_type)
{
    int flash_status;

    uint8_t trailer[48]={
							0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
							0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
							0x77,0xC2,0x95,0xF3,0x60,0xD2,0xEF,0x7F,0x35,0x52,0x50,0x0F,0x2C,0xB6,0x79,0x80
						};
    
    if( partition_type  == PARTITION_TYPE_SECONDARY)
    {
        flash_status = etn_fb_flash_write(FLASH_TYPE_EXTERNAL, (EXT_FLASH_SECONDARY_AREA_END_ADDR-48),48,1, 0, trailer);
    }
    
    if( partition_type  == PARTITION_TYPE_FALLBACK)
    {
        flash_status = etn_fb_flash_write(FLASH_TYPE_EXTERNAL, (EXT_FLASH_FALLBACK_AREA_END_ADDR-48),48,1, 0, trailer);
    }

    if( partition_type  == PARTITION_TYPE_PRIMARY)
    {
        flash_status = etn_fb_flash_write(FLASH_TYPE_INTERNAL, (INT_FLASH_PRIMARY_AREA_END_ADDR-48),48,1, 0, trailer);
    }

    return flash_status;
}   

uint16_t etn_fb_flash_cal_crc(bool flash_type, uint32_t address, uint32_t length)
{
    int flash_status=0;
    uint16_t crc_value=0;
    uint32_t len=0;
    uint8_t data_buf[128];

    while(len < length)
    {
        flash_status = etn_fb_flash_read_to_buf(flash_type, address, 128, &data_buf,0);
        if( flash_status == 0 )
        {
            crc_value += cb_cal_crc16(&data_buf, 128, 0);
        }
        else
        {
            printk("Error in flash read err:%d breaking chain\n", flash_status);
            len = length;
        }

        len += 128;
        address += 128;
    }

    return crc_value;
}

uint16_t cb_cal_crc16( uint8_t const* data, uint32_t length, uint16_t init_crc )
{
	uint16_t temp_crc;

	temp_crc = init_crc;

    while ( length > 0U )
	{
        length--;
        temp_crc = ( ( temp_crc >> 8 ) ^ table1[( (uint8_t)( temp_crc ) ^ *data ) & 0xFFU] );
        data++;
    }

    return ( temp_crc );
}

void test_fallback_apis(void)
{
    //test_copy_content();
    //test_crc_calculation();
    test_check_image_info();
}

void test_copy_content(void)
{
    int return_status;

    if( fb_data.fb_running_loc == FB_RUN_MCUBOOT )
    {
        //etn_fb_flash_read(FLASH_TYPE_INTERNAL, INT_FLASH_PRIMARY_AREA_START_ADDR, 0x1000, 1, 0);
        printk("testing copy content api\n");
        printk("erasing 4K of flash area at fallback partition\n");
        return_status = etn_fb_flash_erase( FLASH_TYPE_EXTERNAL, EXT_FLASH_FALLBACK_AREA_START_ADDR, 0x1000 );
        if( return_status == 0 )
        {
            printk("copying 4K of data from primary partition to fallback partition\n");
            return_status = etn_fb_copy_content(PARTITION_TYPE_PRIMARY, PARTITION_TYPE_FALLBACK, INT_FLASH_PRIMARY_AREA_START_ADDR, EXT_FLASH_FALLBACK_AREA_START_ADDR, 0x1000);
            if(return_status == 0)
            {
                printk("copying content success\n");            
            }
            else
            {
                printk("copying content failed\n");            
            }
        }
        else
        {
            printk("fail to erase 4K flash ar fallback flash\n");
        }
    }
    else
    {
        //etn_fb_flash_read(FLASH_TYPE_EXTERNAL, EXT_FLASH_FALLBACK_AREA_START_ADDR, 0x1000, 1, 0);
    }
}

void test_crc_calculation(void)
{
    uint16_t crc_val;

    printk("testing image_crc calculation\n");

    if( fb_data.fb_running_loc == FB_RUN_MCUBOOT )
    {
        printk("calculating 4K image_crc from primary location\n");
        crc_val =  etn_fb_flash_cal_crc(FLASH_TYPE_INTERNAL, INT_FLASH_PRIMARY_AREA_START_ADDR, 0x1000);
        printk("cal image_crc:%X\n", crc_val);
    }
    else
    {
        printk("calculating 4K image_crc from fallback location\n");
        crc_val =  etn_fb_flash_cal_crc(FLASH_TYPE_EXTERNAL, EXT_FLASH_FALLBACK_AREA_START_ADDR, 0x1000);
        printk("cal image_crc:%X\n", crc_val);
    }
}

void test_check_image_info(void)
{
    int return_status;

    printk("testing check image info \n");

    if( fb_data.fb_running_loc == FB_RUN_MCUBOOT )
    {
        printk("erasing image status loaction\n");
        return_status = etn_fb_flash_erase( FLASH_TYPE_EXTERNAL, EXT_FLASH_IMAGE_STATUS_START_ADDR, EXT_FLASH_IMAGE_STATUS_SIZE );
        if(return_status == 0)
        {
            etn_fb_check_image_info(PARTITION_TYPE_PRIMARY, FB_RUN_MCUBOOT);
            etn_fb_check_image_info(PARTITION_TYPE_SECONDARY,FB_RUN_MCUBOOT);
            etn_fb_check_image_info(PARTITION_TYPE_FALLBACK, FB_RUN_MCUBOOT);
        }
        else
        {
            printk("fail to erase 4K flash ar fallback flash\n");
        }    
    }

}