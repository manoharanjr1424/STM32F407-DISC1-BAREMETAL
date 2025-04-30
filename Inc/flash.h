/*
 * flash.h
 *
 *  Created on: Apr 15, 2025
 *      Author: mjayakumar
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "mcu.h"


typedef struct {
	volatile uint32_t FLASH_ACR;
	volatile uint32_t FLASH_KEYR;
	volatile uint32_t FLASH_OPTKEYR;
	volatile uint32_t FLASH_SR;
	volatile uint32_t FLASH_CR;
	volatile uint32_t FLASH_OPTCR;
}flashInterfaceReg_t;

typedef struct {
	volatile uint8_t LATENCY;
	volatile uint8_t PARALLELISM;
}flashHandler_t;

typedef enum {
    ZERO_WAIT_STATE = 0,
    ONE_WAIT_STATE,
    TWO_WAIT_STATE,
    THREE_WAIT_STATE,
    FOUR_WAIT_STATE,
    FIVE_WAIT_STATE,
    SIX_WAIT_STATE,
    SEVEN_WAIT_STATE,
    EIGHT_WAIT_STATE,
    NINE_WAIT_STATE,
    TEN_WAIT_STATE,
    ELEVEN_WAIT_STATE,
    TWELVE_WAIT_STATE,
    THIRTEEN_WAIT_STATE,
    FOURTEEN_WAIT_STATE,
    FIFTEEN_WAIT_STATE
}flashWaitState_t;


typedef enum {
	program_x8 = 0,
	program_x16,
	program_x32,
	program_x64
}flashParallelism_t;

typedef enum {
	SECTOR_0 = 0000,
	SECTOR_1,
	SECTOR_2,
	SECTOR_3,
	SECTOR_4,
	SECTOR_5,
	SECTOR_6,
	SECTOR_7,
	SECTOR_8,
	SECTOR_9,
	SECTOR_10,
	SECTOR_11
}flashSector_t;


typedef enum {
	FLASH_OP_SUCCESS = 0,
	FLASH_OP_FAILED,
	FLASH_UNLOCKED,
	FLASH_LOCKED,
	FLASH_UNLOCK_FAILED,
	FLASH_LOCK_FAILED,
	FLASH_WRITE_FAILED,
	FLASH_WRITE_SUCCESS,
	FLASH_READ_FAILED,
	FLASH_READ_SUCCESS,
	FLASH_SECTOR_ERASE_SUCCESS,
	FLASH_SECTOR_ERASE_FAILED,
	FLASH_MASS_ERASE_SUCCESS,
	FLASH_MASS_ERASE_FAILED,
	FLASH_BANK_ERASE_SUCCESS,
	FLASH_BANK_ERASE_FIALED
}flashReturnSatate;


#define FlASH_SECTOR_0_ADDR			0x08000000UL
#define FlASH_SECTOR_1_ADDR			0x08004000UL
#define FlASH_SECTOR_2_ADDR			0x08008000UL
#define FlASH_SECTOR_3_ADDR			0x0800C000UL
#define FlASH_SECTOR_4_ADDR			0x08010000UL
#define FlASH_SECTOR_5_ADDR			0x08020000UL
#define FlASH_SECTOR_6_ADDR			0x08040000UL
#define FlASH_SECTOR_7_ADDR			0x08060000UL
#define FlASH_SECTOR_8_ADDR			0x08080000UL
#define FlASH_SECTOR_9_ADDR			0x080A0000UL
#define FlASH_SECTOR_10_ADDR		0x080C0000UL
#define FlASH_SECTOR_11_ADDR		0x080E0000UL


#define FLASH ((flashInterfaceReg_t *)0x40023C00UL)


uint8_t Flash_Erase_Sector(uint32_t FlashSector);
uint8_t Write_to_Flash(uint32_t StartPageAddress, uint32_t *Data, uint16_t numofPages);
uint8_t Read_from_Flash(uint32_t StartPageAddress, uint32_t *Data, uint16_t numofPages);
uint8_t Flash_Init(flashHandler_t *);
uint8_t Check_Flash_Busy(void);
uint8_t Flash_Unlock(void);
uint8_t Flash_Lock(void);




#endif /* FLASH_H_ */
