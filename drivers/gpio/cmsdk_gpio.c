#include <asm/gpio.h>
#include <asm/io.h>
#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>

#define CMSDK_GPIO_MAX_NGPIO (16)

typedef struct GPIO_BLOCK_regs_s
{
	volatile uint32_t DATA;
	volatile uint32_t DATAOUT;
	volatile uint32_t reserved_0[2];
	volatile uint32_t OUTENSET;
	volatile uint32_t OUTENCLR;
	volatile uint32_t ALTFUNCSET;
	volatile uint32_t ALTFUNCCLR;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t INTTYPESET;
	volatile uint32_t INTTYPECLR;
	volatile uint32_t INTPOLSET;
	volatile uint32_t INTPOLCLR;
	union
	{
		volatile uint32_t INTSTATUS;
		volatile uint32_t INTCLEAR;
	};
	volatile uint32_t reserved_1[241];
	volatile uint32_t MASKLOWBYTE;
	volatile uint32_t reserved_2[255];
	volatile uint32_t MASKHIGHBYTE;
	volatile uint32_t reserved_3[499];
	volatile uint32_t PID4;
	volatile uint32_t PID5;
	volatile uint32_t PID6;
	volatile uint32_t PID7;
	volatile uint32_t PID0;
	volatile uint32_t PID1;
	volatile uint32_t PID2;
	volatile uint32_t PID3;
	volatile uint32_t CID0;
	volatile uint32_t CID1;
	volatile uint32_t CID2;
	volatile uint32_t CID3;
} GPIO_BLOCK_regs_s;

struct gpio_range {
	unsigned int start; /* Start of the range */
	unsigned int size;  /* Size of the range */
};

struct cmsdk_gpio
{
	struct udevice *pinctrl;
	GPIO_BLOCK_regs_s *regs;
	void *gpio_pads_config_base;
	unsigned int gpio_index_module_offset;
};


/**
 * Get the value of a GPIO pin.
 *
 * This function retrieves the current value of a GPIO pin specified by the
 * given offset.
 *
 * @param dev	 Pointer to the GPIO device structure
 * @param offset  Offset of the GPIO pin
 * @return		The current value of the GPIO pin (0 or 1)
 */
static int cmsdk_gpio_get_value(struct udevice *dev, unsigned offset)
{
	struct cmsdk_gpio *priv = dev_get_priv(dev);

	return !!(readl(&priv->regs->DATA) & BIT(offset));
}

/**
 * Set the value of a GPIO pin.
 *
 * This function sets the value of a GPIO pin specified by the given offset.
 *
 * @param dev	   Pointer to the GPIO device structure
 * @param offset	Offset of the GPIO pin
 * @param value	 Value to be set (0 or 1)
 * @return		  0 on success, negative error code on failure
 */
static int cmsdk_gpio_set_value(struct udevice *dev, unsigned offset,
				int value)
{
	struct cmsdk_gpio *priv = dev_get_priv(dev);
	volatile unsigned long data_reg = readl(&priv->regs->DATAOUT);

	if (value)
		generic_set_bit(offset, &data_reg);
	else
		generic_clear_bit(offset, &data_reg);

	writel(data_reg, &priv->regs->DATAOUT);

	return 0;
}

/**
 * Get the function of a specific GPIO pin.
 *
 * This function retrieves the function of the GPIO pin specified by the offset parameter.
 *
 * @param dev	 Pointer to the udevice structure representing the GPIO device.
 * @param offset  The offset of the GPIO pin.
 * @return		The function of the GPIO pin.
 */
static int cmsdk_gpio_get_function(struct udevice *dev, unsigned offset)
{
	struct cmsdk_gpio *priv = dev_get_priv(dev);
	int value = pinctrl_get_gpio_mux(priv->pinctrl, priv->gpio_index_module_offset / CMSDK_GPIO_MAX_NGPIO, offset);

	if (value != GPIOF_INPUT && value != GPIOF_OUTPUT)
		return value;

	if (readl(&priv->regs->OUTENCLR) & BIT(offset))
		return GPIOF_OUTPUT;

	return GPIOF_INPUT;
}

/**
 * Sets the direction of a GPIO pin to input.
 *
 * This function is used to configure the direction of a GPIO pin as input.
 *
 * @param dev	 Pointer to the GPIO device structure
 * @param offset  The offset of the GPIO pin
 * @return		0 on success, negative error code on failure
 */
static int cmsdk_gpio_direction_input(struct udevice *dev, unsigned offset)
{
	struct cmsdk_gpio *priv = dev_get_priv(dev);

	writel(BIT(offset), &priv->regs->OUTENCLR);

	return 0;
}

/**
 * Set the direction of a GPIO pin to output.
 *
 * This function sets the direction of a GPIO pin to output mode.
 *
 * @param dev	 Pointer to the GPIO device structure
 * @param offset  The offset of the GPIO pin
 *
 * @return 0 on success, negative error code on failure
 */
static int cmsdk_gpio_direction_output(struct udevice *dev, unsigned offset,
									   int value)
{
	struct cmsdk_gpio *priv = dev_get_priv(dev);

	writel(BIT(offset), &priv->regs->OUTENSET);

	return cmsdk_gpio_set_value(dev, offset, value);
}

/**
 * @brief Probes the CMSDK GPIO device
 *
 * This function is responsible for probing the CMSDK GPIO device and initializing
 * its state. It is called during the device initialization process.
 *
 * @param dev Pointer to the udevice structure representing the CMSDK GPIO device
 * @return 0 on success, negative error code on failure
 */
static int cmsdk_gpio_probe(struct udevice *dev)
{
	struct cmsdk_gpio *priv = dev_get_priv(dev);
	struct gpio_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	char buf[20];
	int ret;

	ret = uclass_first_device_err(UCLASS_PINCTRL, &priv->pinctrl);
	if (ret)
		return ret;

	priv->regs = (GPIO_BLOCK_regs_s *)dev_read_addr_index(dev, 0);
	if (!priv->regs)
		return -EINVAL;

	priv->gpio_pads_config_base = (void *)dev_read_addr_index(dev, 1);
	if (!priv->gpio_pads_config_base)
		return -EINVAL;

	ret = dev_read_u32(dev, "cmsdk_gpio,gpio-offset",
			   &priv->gpio_index_module_offset);
	if (ret)
		return -EINVAL;

	ret = dev_read_u32(dev, "cmsdk_gpio,ngpio", &uc_priv->gpio_count);
	if (ret)
		return -EINVAL;

	if (uc_priv->gpio_count > CMSDK_GPIO_MAX_NGPIO)
		return -EINVAL;

	snprintf(buf, sizeof(buf), "cmsdk-gpio-%u-",
		 priv->gpio_index_module_offset / CMSDK_GPIO_MAX_NGPIO);
	uc_priv->bank_name = strdup(buf);
	if (!uc_priv->bank_name)
		return -ENOMEM;

	return 0;
}

/**
 * @brief Requests a GPIO pin from the CMSDK GPIO driver.
 *
 * This function is used to request a GPIO pin from the CMSDK GPIO driver.
 * It takes a pointer to the device structure, the offset of the GPIO pin,
 * and the flags for the GPIO pin request.
 *
 * @param dev Pointer to the udevice structure representing the CMSDK GPIO device.
 * @param offset Offset of the GPIO pin to request.
 * @param flags Flags for the GPIO pin request.
 * @return 0 on success, or a negative error code on failure.
 */
static int cmsdk_gpio_request(struct udevice *dev, unsigned offset,
			      const char *label)
{
	return pinctrl_gpio_request(dev, offset);
}

static const struct udevice_id cmsdk_gpio_ids[] = {
	{.compatible = "arm,cmsdk-gpio"}, {}};

static const struct dm_gpio_ops cmsdk_gpio_ops = {
	.request = cmsdk_gpio_request,
	.get_value = cmsdk_gpio_get_value,
	.set_value = cmsdk_gpio_set_value,
	.get_function = cmsdk_gpio_get_function,
	.direction_input = cmsdk_gpio_direction_input,
	.direction_output = cmsdk_gpio_direction_output,
};

U_BOOT_DRIVER(gpio_cmsdk) = {
	.name = "gpio-cmsdk",
	.id = UCLASS_GPIO,
	.of_match = cmsdk_gpio_ids,
	.ops = &cmsdk_gpio_ops,
	.probe = cmsdk_gpio_probe,
	.priv_auto = sizeof(struct cmsdk_gpio),
};