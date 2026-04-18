// /*
//  * Copyright (C) 2026, Miaow - All Rights Reserved
//  *
//  * SPDX-License-Identifier: GPL-3.0-or-later
//  */
// #include <stdio.h>
// #include <zephyr/kernel.h>
// #include <zephyr/bindesc.h>
// #include <zephyr/logging/log.h>

// LOG_MODULE_REGISTER(99_playground, LOG_LEVEL_INF);

// BINDESC_STR_DEFINE(my_string, 1, "Hello world!");
// BINDESC_UINT_DEFINE(my_int, 2, 5);
// BINDESC_BYTES_DEFINE(my_bytes, 3, ({1, 2, 3, 4}));

// int main(void)
// {
// 	// /* Builtin descriptors */
// 	// LOG_INF("Zephyr version %s\n\tmajor:minor %u:%u\n\tnumber %u\n\tpatch %u\n\tbuild %s", BINDESC_GET_STR(kernel_version_string),
// 	// 	BINDESC_GET_UINT(kernel_version_major), BINDESC_GET_UINT(kernel_version_minor),
// 	// 	BINDESC_GET_UINT(kernel_version_number), BINDESC_GET_UINT(kernel_version_patchlevel),
// 	// 	BINDESC_GET_STR(kernel_build_version)
// 	// );
// 	// LOG_INF("App version %s\n\tmajor:minor %u:%u\n\tnumber %u\n\tpatch %u\n\tbuild %s", BINDESC_GET_STR(app_version_string),
// 	// 	BINDESC_GET_UINT(app_version_major), BINDESC_GET_UINT(app_version_minor),
// 	// 	BINDESC_GET_UINT(app_version_number), BINDESC_GET_UINT(app_version_patchlevel),
// 	// 	BINDESC_GET_STR(app_build_version)
// 	// );
// 	// LOG_INF("Build time: %s\n\tdate", BINDESC_GET_STR(build_date_time_string));
// 	// LOG_INF("Compiler: %s %s\n", BINDESC_GET_STR(c_compiler_name),
// 	// 	BINDESC_GET_STR(c_compiler_version));

// 	// /* Custom descriptors */
// 	// LOG_INF("my_string: %s\n", BINDESC_GET_STR(my_string));
// 	// LOG_INF("my_int: %d\n", BINDESC_GET_UINT(my_int));
// 	// LOG_INF("my_bytes: ");
// 	// for (size_t i = 0; i < BINDESC_GET_SIZE(my_bytes); i++) {
// 	// 	LOG_INF("%02x ", BINDESC_GET_BYTES(my_bytes)[i]);
// 	// }
// 	// LOG_INF("\n");

// 	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

// 	return 0;
// }

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		printf("LED state: %s\n", led_state ? "ON" : "OFF");
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
