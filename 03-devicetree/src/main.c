/*
 * Copyright (C) 2026, Miaow - All Rights Reserved
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/bindesc.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>

LOG_MODULE_REGISTER(03_devicetree, LOG_LEVEL_INF);

/* Define the device node using one of the following methods:
 * 1. DT_PATH: path to the device node in the device tree
 * 2. DT_NODELABEL: node label defined in the device tree
 * 3. DT_ALIAS: alias defined in the device tree for the node
 * 4. DT_INST: instance of a compatible device. instance have no gurantee to be stable
 *
 * Uncomment one of the following lines to define MY_DEVICE_NODE accordingly.
 */
#define MY_DEVICE_NODE DT_PATH(soc, device_abcd1234)
// #define MY_DEVICE_NODE DT_NODELABEL(device1)
// #define MY_DEVICE_NODE DT_ALIAS(my_device)
// #define MY_DEVICE_NODE DT_INST(0, miaow_my_device)
// #define MY_DEVICE_NODE DT_CHILD(DT_PATH(soc), device_abcd1234)
// #define MY_DEVICE_NODE DT_PARENT(DT_PATH(soc, device_abcd1234, subdevice_abcd1238))

/**
 * @brief Print the message of the day (MOTD) using built-in descriptors.
 *
 * This function retrieves and prints various build and host information
 * using built-in descriptors defined in the Zephyr build system. It includes
 * details about the Zephyr version, application version, build time, and host
 * information such as compiler details.
 */
void print_motd()
{
	/* Builtin descriptors */
	printk("Zephyr version %s\n\tmajor:minor %u:%u\n\tnumber %u\n\tpatch %u\n\tbuild %s\n", BINDESC_GET_STR(kernel_version_string),
		BINDESC_GET_UINT(kernel_version_major), BINDESC_GET_UINT(kernel_version_minor),
		BINDESC_GET_UINT(kernel_version_number), BINDESC_GET_UINT(kernel_version_patchlevel),
		BINDESC_GET_STR(kernel_build_version)
	);
	printk("App version %s\n\tmajor:minor %u:%u\n\tnumber %u\n\tpatch %u\n\tbuild %s\n", BINDESC_GET_STR(app_version_string),
		BINDESC_GET_UINT(app_version_major), BINDESC_GET_UINT(app_version_minor),
		BINDESC_GET_UINT(app_version_number), BINDESC_GET_UINT(app_version_patchlevel),
		BINDESC_GET_STR(app_build_version)
	);
	printk("Build time %s\n\tdate %s\n\ttime %s\n\tunix %u\n\tyear %u\n\tmonth %u\n\tday %u\n\thour %u\n\tminute %u\n\tsecond %u\n",
		BINDESC_GET_STR(build_date_time_string),
		BINDESC_GET_STR(build_date_string),
		BINDESC_GET_STR(build_time_string),
		BINDESC_GET_UINT(build_time_unix),
		BINDESC_GET_UINT(build_time_year), BINDESC_GET_UINT(build_time_month), BINDESC_GET_UINT(build_time_day),
		BINDESC_GET_UINT(build_time_hour), BINDESC_GET_UINT(build_time_minute), BINDESC_GET_UINT(build_time_second)
	);
	printk("Host info\n\thost %s\n\tcc %s %s\n\tc++ %s %s\n",
		BINDESC_GET_STR(host_name),
		BINDESC_GET_STR(c_compiler_name), BINDESC_GET_STR(c_compiler_version),
		BINDESC_GET_STR(cxx_compiler_name), BINDESC_GET_STR(cxx_compiler_version)
	);
}

/**
 * @brief Check for the presence of specific properties in the device node.
 */
void check_prop()
{
	printk("has prop clock_frequency: %d\n", DT_NODE_HAS_PROP(MY_DEVICE_NODE, clock_frequency));
	printk("has prop not_a_prop: %d\n", DT_NODE_HAS_PROP(MY_DEVICE_NODE, not_a_prop));
	printk("ccc prop has index 1: %d\n", DT_PROP_HAS_IDX(MY_DEVICE_NODE, ccc, 1));
	printk("ccc prop has index 2: %d\n", DT_PROP_HAS_IDX(MY_DEVICE_NODE, ccc, 2));
}

/**
 * @brief Retrieve and print properties of the device node.
 */
void get_prop()
{
	const char compatible[] = DT_PROP(MY_DEVICE_NODE, compatible);
	const char label[] = DT_PROP(MY_DEVICE_NODE, label);
	const int reg[] = DT_PROP(MY_DEVICE_NODE, reg);
	const char status[] = DT_PROP(MY_DEVICE_NODE, status);
	const unsigned char b[] = DT_PROP(MY_DEVICE_NODE, bbb);
	const size_t b_item_count = DT_PROP_LEN(MY_DEVICE_NODE, bbb);
	const char *const c[] = DT_PROP(MY_DEVICE_NODE, ccc);
	const size_t c_item_count = DT_PROP_LEN(MY_DEVICE_NODE, ccc);

	printk("compatible=%s\n", compatible);
	printk("label=%s\n", label);

	printk("reg[]=");
	for (size_t i = 0; i < ARRAY_SIZE(reg); i++)
		printk("0x%x, ", reg[i]);
	printk("\n");

	printk("status=%s\n", status);

	printk("b[]=");
	for (size_t i = 0; i < b_item_count; i++)
		printk("%x, ", (int)b[i]);
	printk("\n");

	printk("c[]=");
	for (size_t i = 0; i < c_item_count; i++)
		printk("%s ", c[i]);
	printk("\n");
}

/**
 * @brief Retrieve and print the 'reg' properties of the device node.
 */
void reg_prop()
{
	size_t reg_count = DT_NUM_REGS(MY_DEVICE_NODE);
	printk("Number of reg blocks = %d\n", reg_count);
	uint32_t addr[] = {DT_REG_ADDR_BY_IDX(MY_DEVICE_NODE, 0), DT_REG_ADDR_BY_IDX(MY_DEVICE_NODE, 1)};
	uint32_t size[] = {DT_REG_SIZE_BY_IDX(MY_DEVICE_NODE, 0), DT_REG_SIZE_BY_IDX(MY_DEVICE_NODE, 1)};
	printk("reg[0].addr = 0x%x, .size = 0x%x\n", addr[0], size[0]);
	printk("reg[1].addr = 0x%x, .size = 0x%x\n", addr[1], size[1]);
}

/**
 * @brief Retrieve a device using a phandle property and check if it is ready.
 */
void phandle_prop()
{
	char *node1 = STRINGIFY(DT_PHANDLE(MY_DEVICE_NODE, phandle1));
	printk("phandle1 points to node %s\n", node1);
	
	char *node2 = STRINGIFY(DT_PHANDLE_BY_IDX(MY_DEVICE_NODE, phandle2, 1));
	printk("phandle2[1] points to node %s\n", node2);

	char *node3 = STRINGIFY(DT_PHANDLE_BY_NAME(MY_DEVICE_NODE, miaows, first));
	printk("miaows[first] points to node %s\n", node3);

	int c1_value = DT_PHA_BY_IDX(MY_DEVICE_NODE, miaows, 1, c1);
	printk("miaows[1].c1 = %d\n", c1_value);

	int flag = DT_PHA_HAS_CELL_AT_IDX(MY_DEVICE_NODE, miaows, 1, c2);
	printk("does miaows[1] have a cell named c2? %d\n", flag);
}

int main(void)
{
	print_motd();

	LOG_INF("Init done!");
	
	/* Check if the device node has certain properties and print their values */
	LOG_INF("Check prop of device node %s...", STRINGIFY(MY_DEVICE_NODE));
	check_prop();
	k_msleep(100);

	/* Retrieve and print properties of the device node */
	LOG_INF("Retrieve prop of device node %s...", STRINGIFY(MY_DEVICE_NODE));
	get_prop();
	k_msleep(100);

	/* Reg properties of the device node */
	LOG_INF("Reg properties of device node %s...", STRINGIFY(MY_DEVICE_NODE));
	reg_prop();
	k_msleep(100);

	/* Phandle properties of the device node */
	LOG_INF("Phandle properties of device node %s...", STRINGIFY(MY_DEVICE_NODE));
	phandle_prop();
	k_msleep(100);

	return 0;
}