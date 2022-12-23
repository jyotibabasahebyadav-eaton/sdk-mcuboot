/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <hal/nrf_gpio.h>
#include <nrfx.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/flash.h>
#include <logging/log.h>

/* board init priority */
#define BOARD_INIT_PRIORITY	70

/* gpio initial state */
#define GPIO_INIT_STATE		1

/* power control pin */
#define INIT_PIN_PWR_CNTRL	31

#define SERIAL_FLASH_START_ADDRESS  0x00000
#define SERIAL_FLASH_END_ADDRESS	0x72000

gpio_flags_t init_flag_pwr_cntrl = GPIO_OUTPUT | GPIO_ACTIVE_HIGH;

static int setup(void)
{

//#if !defined(CONFIG_TRUSTED_EXECUTION_SECURE)
	const struct device *dev_gpio0;
	

	int err;
	int ret;

	printk("\nBoard system init started \n");

	/* get device binding to port gpio0 */
	dev_gpio0 = device_get_binding("GPIO_0");

	if (dev_gpio0 == NULL)
	{
		printk("device binding to port gpio0 failed\n");
		return;
	}
	else
	{
		printk("device binding to port gpio0 sucess\n");
	}

	/* configure led pins as output */
	ret = gpio_pin_configure(dev_gpio0, INIT_PIN_PWR_CNTRL, init_flag_pwr_cntrl);
	if (ret != 0)
	{
		printk("pin pwr cntrl configuration failed\n");
		return;
	}
	else
	{
		printk("pin pwr cntrl configuration sucess\n");
	}

	gpio_pin_set(dev_gpio0, INIT_PIN_PWR_CNTRL, GPIO_INIT_STATE);

	printk("Board system init done\n");

	//setup_is25();
	//read_from_serial_flash(SERIAL_FLASH_START_ADDRESS, SERIAL_FLASH_END_ADDRESS,0);

	return 0;
}

SYS_INIT(setup, POST_KERNEL, BOARD_INIT_PRIORITY);
