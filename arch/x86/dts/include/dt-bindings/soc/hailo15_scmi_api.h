/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019-2024 Hailo Technologies Ltd. All rights reserved.
 */

#ifndef HAILO15_SCMI_API_H
#define HAILO15_SCMI_API_H

#define HAILO_SOC_HAILO15 1
#define HAILO_SOC_HAILO15L 2

#ifndef HAILO_SOC_TYPE
#    error "HAILO_SOC_TYPE is not defined"
#endif

#define HAILO15_SCMI_SENSOR_IDX_PVT_TEMPERATURE_SENSOR_0 0
#define HAILO15_SCMI_SENSOR_IDX_PVT_TEMPERATURE_SENSOR_1 1

/* Clocks IDs */
#define HAILO15_SCMI_CLOCK_IDX_HCLK 0
#define HAILO15_SCMI_CLOCK_IDX_SDIO_0_M_HCLK 1
#define HAILO15_SCMI_CLOCK_IDX_SDIO_1_M_HCLK 2
#define HAILO15_SCMI_CLOCK_IDX_DSP_CONFIG 3
#define HAILO15_SCMI_CLOCK_IDX_DSP_PLL 4
#define HAILO15_SCMI_CLOCK_IDX_DSP 5
#define HAILO15_SCMI_CLOCK_IDX_ETHERNET_PCLK 6
#define HAILO15_SCMI_CLOCK_IDX_ETHERNET_ACLK 7
#define HAILO15_SCMI_CLOCK_IDX_SDIO_0_CARD_CLK 8
#define HAILO15_SCMI_CLOCK_IDX_SDIO_1_CARD_CLK 9
#define HAILO15_SCMI_CLOCK_IDX_VISION_HCLK 10
#define HAILO15_SCMI_CLOCK_IDX_ISP_WRAPPER_PCLK 11
#define HAILO15_SCMI_CLOCK_IDX_CSI_RX0_PCLK 12
#define HAILO15_SCMI_CLOCK_IDX_CSI_RX1_PCLK 13
#define HAILO15_SCMI_CLOCK_IDX_CSI_TX0_PCLK 14
#define HAILO15_SCMI_CLOCK_IDX_VISION_CLK 15
#define HAILO15_SCMI_CLOCK_IDX_ISP_WRAPPER_CLK 16
#define HAILO15_SCMI_CLOCK_IDX_CSI_RX0_CLK 17
#define HAILO15_SCMI_CLOCK_IDX_CSI_RX1_CLK 18
#define HAILO15_SCMI_CLOCK_IDX_CSI_TX0_CLK 19
#define HAILO15_SCMI_CLOCK_IDX_CSI_RX0_XTAL_CLK 20
#define HAILO15_SCMI_CLOCK_IDX_CSI_RX1_XTAL_CLK 21
#define HAILO15_SCMI_CLOCK_IDX_CSI_TX0_XTAL_CLK 22
#define HAILO15_SCMI_CLOCK_IDX_MIPI_REF_CLK 23
#define HAILO15_SCMI_CLOCK_IDX_MIPI_ESC_CLK 24
#define HAILO15_SCMI_CLOCK_IDX_SDIO_0_CLK_DIV_BYPASS 25
#define HAILO15_SCMI_CLOCK_IDX_SDIO_1_CLK_DIV_BYPASS 26
#define HAILO15_SCMI_CLOCK_IDX_PCIE_REFCLK 27
#define HAILO15_SCMI_CLOCK_IDX_H265_HCLK 28
#define HAILO15_SCMI_CLOCK_IDX_H265_CLK 29
#define HAILO15_SCMI_CLOCK_IDX_USB_PCLK 30
#define HAILO15_SCMI_CLOCK_IDX_USB_LPM_CLK 31
#define HAILO15_SCMI_CLOCK_IDX_USB2_REFCLK 32
#define HAILO15_SCMI_CLOCK_IDX_USB_ACLK 33
#define HAILO15_SCMI_CLOCK_IDX_USB_SOF_CLK 34
#define HAILO15_SCMI_CLOCK_IDX_PCIE_PCLK 35
#define HAILO15_SCMI_CLOCK_IDX_PCIE_ACLK 36
#define HAILO15_SCMI_CLOCK_IDX_VIRTUAL_DSP 37
#if HAILO_SOC_TYPE == HAILO_SOC_HAILO15
#    define HAILO15_SCMI_CLOCK_IDX_I2S_CLK_DIV 38
#endif /* HAILO_SOC_HAILO15 */
#if HAILO_SOC_TYPE == HAILO_SOC_HAILO15L
#    define HAILO15_SCMI_CLOCK_IDX_ISP_HDR_STITCH 38
#    define HAILO15_SCMI_CLOCK_IDX_I2C_0 39
#    define HAILO15_SCMI_CLOCK_IDX_I2C_1 40
#    define HAILO15_SCMI_CLOCK_IDX_I2C_2 41
#    define HAILO15_SCMI_CLOCK_IDX_I2C_3 42
#    define HAILO15_SCMI_CLOCK_IDX_SPI_0_GATE 43
#    define HAILO15_SCMI_CLOCK_IDX_SPI_1_GATE 44
#    define HAILO15_SCMI_CLOCK_IDX_SPI_2_GATE 45
#    define HAILO15_SCMI_CLOCK_IDX_SPI_3_GATE 46
#endif /* HAILO_SOC_HAILO15L */

/* Resets IDs */
#define HAILO15_SCMI_RESET_IDX_CORE_CPU 0
#define HAILO15_SCMI_RESET_IDX_NN_CORE 1
#define HAILO15_SCMI_RESET_IDX_SDIO1_8BIT_MUX 2
#define HAILO15_SCMI_RESET_IDX_DSP 3
#define HAILO15_SCMI_RESET_IDX_SDIO_0_CD_FROM_PINMUX 4
#define HAILO15_SCMI_RESET_IDX_SDIO_1_CD_FROM_PINMUX 5
#define HAILO15_SCMI_RESET_IDX_PCIE_PHY_LANE_0 6
#define HAILO15_SCMI_RESET_IDX_PCIE_PHY_LANE_1 7
#define HAILO15_SCMI_RESET_IDX_PCIE_PHY_LANE_2 8
#define HAILO15_SCMI_RESET_IDX_PCIE_PHY_LANE_3 9
#define HAILO15_SCMI_RESET_IDX_PCIE_PHY 10

/* Power domain IDs */
#if HAILO_SOC_TYPE == HAILO_SOC_HAILO15
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_CSI_RX0 0
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_CSI_RX1 1
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_CSI_TX0 2
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_VISION_SUBSYS 3
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_PCIE 4
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_USB 5
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_SYSTOP 6
#    define HAILO15_SCMI_POWER_DOMAIN_COUNT 7
#elif HAILO_SOC_TYPE == HAILO_SOC_HAILO15L
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_CSI_RX0 0
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_CSI_TX0 1
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_VISION_SUBSYS 2
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_PCIE 3
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_USB 4
#    define HAILO15_SCMI_POWER_DOMAIN_IDX_SYSTOP 5
#    define HAILO15_SCMI_POWER_DOMAIN_COUNT 6
#endif

/* DVFS domain IDs */
#define HAILO15_SCMI_DVFS_DOMAIN_IDX_AP 0
#define HAILO15_SCMI_DVFS_DOMAIN_IDX_NN_CORE 1
#define HAILO15_SCMI_DVFS_DOMAIN_IDX_DSP 2
#define HAILO15_SCMI_DVFS_DOMAIN_COUNT 3

#endif /* HAILO15_SCMI_API_H */
