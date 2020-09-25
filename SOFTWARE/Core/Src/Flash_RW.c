/*
 * Flash_RW.c
 *
 *  Created on: Mar 23, 2020
 *      Author: MERT OCAL
 */

#include "Flash_RW.h"


void    FLASH_PageErase(uint32_t PageAddress);

uint32_t PageError;


void Flash_ErasePage( uint32_t pageaddress )
{
	HAL_FLASH_Unlock();

//	HAL_FLASHEx_Erase( (FLASH_EraseInitTypeDef *) FLASH_TYPEERASE_MASSERASE, (uint32_t *) PageError);
	FLASH_PageErase( pageaddress );

	HAL_FLASH_Lock();
}

void Flash_EEPROM_Data_Write( uint8_t page, uint32_t address, uint32_t index, uint16_t * writeBuffer )
{
	uint32_t flashAddress = address + (index*2);

	//Unlock Flash
	HAL_FLASH_Unlock();

	//Write to Flash
	for( uint32_t i = 0; i < 1; i++ )
	{
		HAL_FLASH_Program( FLASH_TYPEPROGRAM_HALFWORD, flashAddress, (writeBuffer)[i] );
	}

	//Lock the Flash space
	HAL_FLASH_Lock();
}

void Flash_EEPROM_Data_Read( uint8_t page, uint32_t address, uint32_t index, void *readBuffer )
{
	uint32_t flashAddress = address + (index*2);

		*((uint8_t *)readBuffer) = *(uint32_t *)flashAddress;
}
