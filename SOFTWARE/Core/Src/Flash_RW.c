/*
 * Flash_RW.c
 *
 *  Created on: Mar 23, 2020
 *      Author: MERT OCAL
 */

#include "Flash_RW.h"

uint32_t PageError;

void Flash_EraseSector( uint8_t sector )
{
	HAL_FLASH_Unlock();

	HAL_FLASHEx_Erase( (FLASH_EraseInitTypeDef *) FLASH_TYPEERASE_MASSERASE, (uint32_t *) PageError);

	HAL_FLASH_Lock();
}

void Flash_EEPROM_Data_Write( uint8_t sector, uint32_t address, uint32_t index, void *writeBuffer )
{
	uint32_t flashAddress = address + index;

	//Unlock Flash
	HAL_FLASH_Unlock();

	//Write to Flash
	for( uint32_t i = 0; i < 1; i++ )
	{
		HAL_FLASH_Program( FLASH_TYPEPROGRAM_HALFWORD, flashAddress , ( (uint8_t *)writeBuffer )[i] );
		flashAddress++;
	}

	//Lock the Flash space
	HAL_FLASH_Lock();
}

void Flash_EEPROM_Data_Read( uint8_t sector, uint32_t address, uint32_t index, void *readBuffer )
{
	uint32_t flashAddress = address + index;

	for( uint32_t i = 0; i < 1; i++ )
	{
		*((uint8_t *)readBuffer + i) = *(uint8_t *)flashAddress;
		flashAddress++;
	}
}
