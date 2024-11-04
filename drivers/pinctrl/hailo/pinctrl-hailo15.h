// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019-2023 Hailo Technologies Ltd. All rights reserved. 
 */
 
#ifndef _PINCTRL_HAILO15_H
#define _PINCTRL_HAILO15_H

#include <linux/types.h>

struct pinctrl_pin_desc
{
	unsigned number;
	const char *name;
	void *drv_data;
};

#define PINCTRL_PIN(a, b)      \
	{                          \
		.number = a, .name = b \
	}
#define H15_PINMUX_PIN_IN_BANK_COUNT (16)
#define H15_PINMUX_BANK_COUNT (2)
#define H15_PINMUX_PIN_COUNT (H15_PINMUX_PIN_IN_BANK_COUNT * H15_PINMUX_BANK_COUNT)
#define H15_GENERAL_PIN_COUNT (44)
#define H15_PINCTRL_PIN_COUNT (H15_PINMUX_PIN_COUNT + H15_GENERAL_PIN_COUNT)

#define GPIO_PADS_CONFIG__GPIO_PE (0x0)
#define GPIO_PADS_CONFIG__GPIO_PS (0x4)
#define GPIO_PADS_CONFIG__GPIO_IO_INPUT_EN_CTRL_BYPASS_EN (0x2c)
#define GPIO_PADS_CONFIG__GPIO_IO_OUTPUT_EN_N_CTRL_BYPASS_EN (0x34)

#define GENERAL_PADS_CONFIG__DS_SHIFT (11)
#define GENERAL_PADS_CONFIG__DS_MASK (0xF << GENERAL_PADS_CONFIG__DS_SHIFT)
#define GENERAL_PADS_CONFIG__DS_MODIFY(src, dst)    \
	(dst = ((dst & ~GENERAL_PADS_CONFIG__DS_MASK) | \
			(src) << GENERAL_PADS_CONFIG__DS_SHIFT))
#define GENERAL_PADS_CONFIG__OFFSET (4)
#define GENERAL_PADS_CONFIG__PADS_PINMUX (0xb8)

#define H15_PIN_DIRECTION_IN 0x0
#define H15_PIN_DIRECTION_OUT 0x1
#define H15_PIN_DIRECTION_BIDIR 0x2


/*
	Struct for a certain pin set.
*/
struct h15_pin_set_runtime_data {
	/*
	 * Bit mask of the possible modes for this set.
	 * This value is updated depending on the selected functions and their pin group and modes.
	*/
	uint32_t possible_modes;

	/*
	 * The one mode that currently selected from the possible modes.
	 * The first set bit in possible_modes.
	*/
	uint32_t current_mode;
};

struct h15_pin_data {
	/*
	 * The selected function for that pin.
	*/
	unsigned func_selector;
};

enum h15_pin_set_value {
	H15_PIN_SET_VALUE__1_0,
	H15_PIN_SET_VALUE__3_2,
	H15_PIN_SET_VALUE__5_4,
	H15_PIN_SET_VALUE__7_6,
	H15_PIN_SET_VALUE__15_8,
	H15_PIN_SET_VALUE__31_16,
	H15_PIN_SET_VALUE__COUNT,
	H15_PIN_SET_VALUE__INVALID = -1,
};

struct h15_pin_set_modes {
	/*
	 * Pin set index.
	*/
	enum h15_pin_set_value set;

	/*
	 * Bit mask of pinmux mode for the pin set index.
	*/
	uint32_t modes;
};

#define H15_PIN_SET_MODES(set_value, modes_value)                              \
	{                                                                      \
		.set = set_value, .modes = modes_value,                        \
	}

#define __COUNT_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _n, X...) _n
#define COUNT_ARGS(X...) __COUNT_ARGS(, ##X, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define __CONCAT(a, b) a ## b
#define CONCATENATE(a, b) __CONCAT(a, b)

#define __H15_PIN_DIRECTION(pin_direction) H15_PIN_DIRECTION_##pin_direction

#define __H15_PIN_DIRECTION_1(a, ...) __H15_PIN_DIRECTION(a)
#define __H15_PIN_DIRECTION_2(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_1(__VA_ARGS__)
#define __H15_PIN_DIRECTION_3(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_2(__VA_ARGS__)
#define __H15_PIN_DIRECTION_4(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_3(__VA_ARGS__)
#define __H15_PIN_DIRECTION_5(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_4(__VA_ARGS__)
#define __H15_PIN_DIRECTION_6(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_5(__VA_ARGS__)
#define __H15_PIN_DIRECTION_7(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_6(__VA_ARGS__)
#define __H15_PIN_DIRECTION_8(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_7(__VA_ARGS__)
#define __H15_PIN_DIRECTION_9(a, ...)                                          \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_8(__VA_ARGS__)
#define __H15_PIN_DIRECTION_10(a, ...)                                         \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_9(__VA_ARGS__)
#define __H15_PIN_DIRECTION_11(a, ...)                                         \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_10(__VA_ARGS__)
#define __H15_PIN_DIRECTION_12(a, ...)                                         \
	__H15_PIN_DIRECTION(a), __H15_PIN_DIRECTION_11(__VA_ARGS__)
#define H15_PIN_DIRECTIONS(...)                                                \
	{                                                                      \
		CONCATENATE(__H15_PIN_DIRECTION_, COUNT_ARGS(__VA_ARGS__))     \
		(__VA_ARGS__)                                                  \
	}

struct h15_pin_group {
	/*
	 * Array of pins used by this group.
	*/
	const unsigned *pins;

	/*
	 * Array of pins used by this group.
	*/
	const unsigned *pin_directions;

	/*
	 * Total number of pins used by this group.
	*/
	unsigned num_pins;

	/*
	 * Name of the group.
	*/
	const char *name;

	/*
	 * For the pins in the group, store the pin set indexes and for every pin set index the pinmux mode value.
	*/
	const struct h15_pin_set_modes *set_modes;

	/*
	 * Total number of set_modes.
	*/
	unsigned num_set_modes;
};

#define H15_PIN_GROUP(group_name)                                              \
	{                                                                      \
		.name = __stringify(group_name) "_grp",                        \
		.pins = group_name##_pins,                                     \
		.pin_directions = group_name##_pin_directions,                 \
		.num_pins = ARRAY_SIZE(group_name##_pins),                     \
		.set_modes = group_name##_set_modes,                           \
		.num_set_modes = ARRAY_SIZE(group_name##_set_modes),           \
	}

struct h15_pin_function {
	/*
	 * Name of the function.
	*/
	const char *name;

	/*
	 * Size of the name of the function.
	*/
	const unsigned int name_size;

	/*
	 * Array of groups that can be supported by this function
	*/
	const char *const *groups;

	/*
	 * Total number of groups that can be supported by this function.
	*/
	unsigned num_groups;
};

#define H15_PIN_FUNCTION(func)                                                 \
	{                                                                      \
		.name = #func, .name_size = sizeof(#func),                     \
		.groups = func##_grps, .num_groups = ARRAY_SIZE(func##_grps),  \
	}

struct h15_pin_set {
	/*
	 * The number of possible modes for that pin set
	*/
	uint8_t modes_count;

	/*
	 * Name of the pin set.
	*/
	const char *name;
};

#define H15_PIN_SET(set_name, modes_count_value)                               \
	[set_name] = { .name = __stringify(set_name),                          \
		       .modes_count = modes_count_value }

#endif /* _PINCTRL_HAILO15_H */