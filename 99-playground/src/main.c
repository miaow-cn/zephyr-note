/*
 * Copyright (C) 2026, Miaow - All Rights Reserved
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/bindesc.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(99_playground, LOG_LEVEL_INF);

BINDESC_STR_DEFINE(my_string, 1, "Hello world!");
BINDESC_UINT_DEFINE(my_int, 2, 5);
BINDESC_BYTES_DEFINE(my_bytes, 3, ({1, 2, 3, 4}));

int main(void)
{
	/* Builtin descriptors */
	LOG_INF("Zephyr version %s\n\tmajor:minor %u:%u\n\tnumber %u\n\tpatch %u\n\tbuild %s", BINDESC_GET_STR(kernel_version_string),
		BINDESC_GET_UINT(kernel_version_major), BINDESC_GET_UINT(kernel_version_minor),
		BINDESC_GET_UINT(kernel_version_number), BINDESC_GET_UINT(kernel_version_patchlevel),
		BINDESC_GET_STR(kernel_build_version)
	);
	LOG_INF("App version %s\n\tmajor:minor %u:%u\n\tnumber %u\n\tpatch %u\n\tbuild %s", BINDESC_GET_STR(app_version_string),
		BINDESC_GET_UINT(app_version_major), BINDESC_GET_UINT(app_version_minor),
		BINDESC_GET_UINT(app_version_number), BINDESC_GET_UINT(app_version_patchlevel),
		BINDESC_GET_STR(app_build_version)
	);
	LOG_INF("Build time: %s\n\tdate", BINDESC_GET_STR(build_date_time_string));
	LOG_INF("Compiler: %s %s\n", BINDESC_GET_STR(c_compiler_name),
		BINDESC_GET_STR(c_compiler_version));

	/* Custom descriptors */
	LOG_INF("my_string: %s\n", BINDESC_GET_STR(my_string));
	LOG_INF("my_int: %d\n", BINDESC_GET_UINT(my_int));
	LOG_INF("my_bytes: ");
	for (size_t i = 0; i < BINDESC_GET_SIZE(my_bytes); i++) {
		LOG_INF("%02x ", BINDESC_GET_BYTES(my_bytes)[i]);
	}
	LOG_INF("\n");

	return 0;
}