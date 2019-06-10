#ifndef _IIC_IO_H
#define _IIC_IO_H
#include "sys.h"
#define I2C_GPIO_SDA_PORT GPIOB
#define I2C_GPIO_SDA_PIN GPIO_PIN_11
#define I2C_GPIO_SCL_PORT GPIOB
#define I2C_GPIO_SCL_PIN GPIO_PIN_10
#if 0
#define SDA_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}
#define SDA_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;}
#define IIC_SCL   PAout(8)
#define IIC_SDA   PCout(9)
#define READ_SDA  PCout(9)
#else
//IO方向设置
#define SDA_IN()                         \
	{                                    \
		I2C_GPIO_SDA_PORT->MODER &= ~(3 << (11 * 2)); \
		I2C_GPIO_SDA_PORT->MODER |= 0 << 11 * 2;      \
	} //PH5输入模式
#define SDA_OUT()                        \
	{                                    \
		I2C_GPIO_SDA_PORT->MODER &= ~(3 << (11 * 2)); \
		I2C_GPIO_SDA_PORT->MODER |= 1 << 11 * 2;      \
	} //PH5输出模式
//IO操作
#define IIC_SCL(n) ((n) ? HAL_GPIO_WritePin(I2C_GPIO_SCL_PORT, I2C_GPIO_SCL_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(I2C_GPIO_SCL_PORT, I2C_GPIO_SCL_PIN, GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n) ((n) ? HAL_GPIO_WritePin(I2C_GPIO_SDA_PORT, I2C_GPIO_SDA_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(I2C_GPIO_SDA_PORT, I2C_GPIO_SDA_PIN, GPIO_PIN_RESET)) //SDA
#define READ_SDA HAL_GPIO_ReadPin(I2C_GPIO_SDA_PORT, I2C_GPIO_SDA_PIN)																			   //输入SDA
#endif
#define i2c_delay(us) delay_us_poll_systick(us)
enum {
	I2C_MASTER_READ_WTTH_ACK = 0,
	I2C_MASTER_READ_WITH_NACK
};

extern void delay_us_poll_systick(uint32_t us);

void i2c_gpio_init(void);
HAL_StatusTypeDef i2c_master_receive(uint16_t dev_addr,uint8_t *pdata, uint16_t size);
HAL_StatusTypeDef i2c_master_transmit(uint16_t dev_addr,uint8_t *pdata, uint16_t size);
HAL_StatusTypeDef i2c_master_read_mem(uint16_t dev_addr,uint16_t mem_addr,uint8_t *pdata, uint16_t size);

#endif
