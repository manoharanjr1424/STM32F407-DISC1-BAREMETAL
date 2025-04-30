#include "flash.h"

uint8_t Flash_Init(flashHandler_t *data) {

	if(Flash_Unlock() == FLASH_UNLOCK_FAILED) {
		return FLASH_UNLOCK_FAILED;
	}

	FLASH->FLASH_ACR &= ~(0x0007);
	FLASH->FLASH_ACR |= data->LATENCY;

	FLASH->FLASH_CR &= ~(3 << 8);
	FLASH->FLASH_CR |= (data->PARALLELISM << 8);

	FLASH->FLASH_ACR &= ~(1 << 10);
	FLASH->FLASH_ACR &= ~(1 << 9);
	FLASH->FLASH_ACR &= ~(1 << 8);
	FLASH->FLASH_ACR |= (1 << 10);
	FLASH->FLASH_ACR |= (1 << 9);
	FLASH->FLASH_ACR |= (1 << 8);

	return FLASH_OP_SUCCESS;
}


uint8_t Write_to_Flash(uint32_t StartPageAddress, uint32_t *Data, uint16_t numofPages) {

	uint32_t Parallelism = 0;
	uint32_t addressIncrementOffset = 0;
	uint32_t loop = 0;


	FLASH->FLASH_CR |= (1 << 0);

	while(Check_Flash_Busy()); //  # Checking Weather Any Flash Operation are Going
	Parallelism = ((FLASH->FLASH_CR >> 8) & 3);
	switch(Parallelism) {
	case 0:
		addressIncrementOffset = 1;
		break;
	case 1:
		addressIncrementOffset = 2;
		break;
	case 2:
		addressIncrementOffset = 4;
		break;
	case 3:
		addressIncrementOffset = 8;
		break;
	}

	for(loop = 0; loop < numofPages; loop++) {

		*((uint32_t *)StartPageAddress) = (volatile uint32_t)Data[loop];
		printf("Writing at Address [%x]\n",StartPageAddress);
		while(Check_Flash_Busy());
		FLASH->FLASH_SR |= (1 << 0);
		StartPageAddress = (StartPageAddress + addressIncrementOffset);
	}

	FLASH->FLASH_CR &= ~(1 << 0);
	Flash_Lock();
	return FLASH_OP_SUCCESS;
}


uint8_t Read_from_Flash(uint32_t StartPageAddress, uint32_t *Data, uint16_t numofPages) {

		uint32_t Parallelism = 0;
		uint32_t addressIncrementOffset = 0;
		uint32_t loop = 0;

		while(Check_Flash_Busy()); //  # Checking Weather Any Flash Operation are Going

		Parallelism = ((FLASH->FLASH_CR >> 8) & 3);
		switch(Parallelism) {
		case 0:
			addressIncrementOffset = 1;
			break;
		case 1:
			addressIncrementOffset = 2;
			break;
		case 2:
			addressIncrementOffset = 4;
			break;
		case 3:
			addressIncrementOffset = 8;
			break;
		}

		for(loop = 0; loop < numofPages; loop++) {

			(*Data)  = *((uint32_t *)StartPageAddress);
			while(Check_Flash_Busy());
			StartPageAddress = (StartPageAddress + addressIncrementOffset);
			Data++;
		}

		return FLASH_OP_SUCCESS;
}

uint8_t Flash_Erase_Sector(uint32_t FlashSector) {

	while(Check_Flash_Busy());
	FLASH->FLASH_CR &= ~(0xF << 3);
	FLASH->FLASH_CR |=(FlashSector << 3);
	FLASH->FLASH_CR |=(1 << 1);
	FLASH->FLASH_CR |= (1 << 16);
	while(Check_Flash_Busy());
	FLASH->FLASH_SR |= (1 << 0);          // Clear EOP
	FLASH->FLASH_CR &= ~(1 << 1);
	return FLASH_OP_SUCCESS;
}


uint8_t Check_Flash_Busy(void) {
	return (FLASH->FLASH_SR & (1 << 16));
}

uint8_t Flash_Unlock(void) {

	if(! (FLASH->FLASH_CR & (1 << 31)) ) {
		return FLASH_UNLOCKED;
	}

	FLASH->FLASH_KEYR = 0x45670123;
	FLASH->FLASH_KEYR = 0xCDEF89AB;
	FLASH->FLASH_CR |= (1 << 0);

	if( FLASH->FLASH_CR & (1 << 31) ) {
		return FLASH_UNLOCK_FAILED;
	} else {
		return FLASH_UNLOCKED;
	}

}


uint8_t Flash_Lock(void) {
	if( FLASH->FLASH_CR & (1 << 31) ) {
		return FLASH_LOCKED;
	}

	FLASH->FLASH_CR |= (1 << 31);

	if( FLASH->FLASH_CR & (1 << 31) ) {
		return FLASH_LOCKED;
	} else {
		return FLASH_LOCK_FAILED;
	}
}



