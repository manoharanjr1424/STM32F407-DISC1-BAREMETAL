/*
 * i2c_header.h
 *
 *  Created on: Mar 25, 2025
 *      Author: mjayakumar
 */

#ifndef I2C_H_
#define I2C_H_

#include "mcu.h"

typedef enum {
	I2C_SM_MODE = 0,
	I2C_FM_MODE
}i2c_mode_t;

typedef struct {
	i2c_register_t *I2C_Base;
	uint8_t I2C_Mode;
	uint8_t APB_PripheralFreq;
	uint8_t I2C_Freq;
	uint8_t I2C_CCRValue;
	uint8_t I2C_TRISEValue;
}i2c_handler_t;



void I2C_Init(i2c_handler_t i2cHandle);
uint8_t I2C_Write(i2c_register_t *Base, uint8_t Address,uint8_t Data, uint8_t len);
uint8_t I2C_WriteContinoues(i2c_register_t *Base, uint8_t Address,uint8_t Data, uint8_t len);
uint8_t I2C_Read(i2c_register_t *Base, uint8_t Address,uint8_t *Data);
uint8_t I2C_ReadContinoues(i2c_register_t *Base, uint8_t Address,uint8_t *Data);
uint8_t I2C_Start(i2c_register_t *Base);
uint8_t I2C_Stop(i2c_register_t *Base);


#endif /* I2C_H_ */
