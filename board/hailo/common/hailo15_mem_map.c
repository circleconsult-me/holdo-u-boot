// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019-2023 Hailo Technologies Ltd. All rights reserved.
 */

#include <common.h>
#include <asm/armv8/mmu.h>

/* original */
struct mm_region hailo15_mem_map[] = {
	{
		/* Updated by dram_init() */
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	},
	{
		/* Updated by dram_init() */
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	},
	{
		.virt = 0x0UL,
		.phys = 0x0UL,
		.size = 0x80000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	},
	{
		/* List terminator */
		0
	}
};

struct mm_region *mem_map = hailo15_mem_map;
