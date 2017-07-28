/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 *
 * Configuration settings for VoltaStream ZERO.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __VOLTASTREAM0_CONFIG_H
#define __VOLTASTREAM0_CONFIG_H


#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include "mx6_common.h"
#include <asm/imx-common/gpio.h>

#ifdef CONFIG_SECURE_BOOT
#ifndef CONFIG_CSF_SIZE
#define CONFIG_CSF_SIZE 0x4000
#endif
#endif

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_MXC_GPIO

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART1_BASE

/* MMC Configs */
#ifdef CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR
#define CONFIG_SYS_FSL_USDHC_NUM	1
#endif

/* I2C configs */
#ifdef CONFIG_CMD_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_SPEED		100000
#endif

#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"mmcautodetect=yes\0" \
	"swbank=2\0" \
	"switch= if test ${swbank} -eq 1; then " \
			"setenv swbank 2; saveenv; " \
		"else " \
			"setenv swbank 1; saveenv; " \
		"fi;\0" \
	"mmcargs=setenv bootargs console=ttymxc0,115200 " \
		"root=/dev/mmcblk1p${swbank} coherent_pool=4M net.ifnames=0 rootwait rw\0" \
	"loadimage=ext4load mmc 0:${swbank} 0x80800000 /boot/zImage\0" \
	"loadfdt=ext4load mmc 0:${swbank} 0x83000000 /boot/imx6ull-voltastream0.dtb\0" \
	"mmcboot=echo Booting from swbank=${swbank} ...; " \
		"run mmcargs; " \
		"if run loadfdt; then " \
			"bootz 0x80800000 - 0x83000000; " \
		"else " \
			"echo WARN: Cannot load the DT - ABORTING; " \
		"fi; " \

#define CONFIG_BOOTCOMMAND \
	   "mmc dev 0;" \
	   "mmc dev 0;" \
	   "if mmc rescan; then " \
           	"if run loadimage; then " \
	   		"run mmcboot; " \
		"else " \
			"echo No kernel found - switching bank!; " \
			"run switch; " \
			"if run loadimage; then " \
	   			"run mmcboot; " \
			"fi; " \
           	"fi; " \
	   "fi;"

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x8000000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* environment organization */
#define CONFIG_SYS_MMC_ENV_DEV		0	/* USDHC2 */
#define CONFIG_SYS_MMC_ENV_PART		0	/* user area */
#define CONFIG_MMCROOT			"/dev/mmcblk1p2"  /* USDHC2 */

#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_SIZE			SZ_8K
#define CONFIG_ENV_OFFSET		(12 * SZ_64K)

#define CONFIG_IMX_THERMAL

#define CONFIG_IOMUX_LPSR

#define CONFIG_SOFT_SPI

#endif
