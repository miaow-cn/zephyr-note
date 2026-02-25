/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/random/random.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(CONFIG_02_MODULE_LOG_LEVEL, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

int main(void)
{
	uint64_t rnd;

	while (1) {
		rnd = sys_rand64_get();
		LOG_HEXDUMP_INF(&rnd, sizeof(rnd), "Rnd:");
		LOG_ERR("value=%llu", rnd);
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
