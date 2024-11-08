/* SPDX-License-Identifier: GPL-2.0+ */
#ifndef __HOLDO_HAILO15_H
#define __HOLDO_HAILO15_H

#include "hailo15_common.h"

#ifdef CONFIG_HAILO15_DDR_ENABLE_ECC
/* Bank 0 size using ECC */
#define PHYS_SDRAM_1_SIZE (0x70000000)
/* Bank 1 address/size using ECC */
#define PHYS_SDRAM_2 (0x100000000)
#define PHYS_SDRAM_2_SIZE (0x70000000)
#else
/* Bank 0 size not using ECC */
#define PHYS_SDRAM_1_SIZE (0x100000000)
#endif

#endif /* __HOLDO_HAILO15_H */