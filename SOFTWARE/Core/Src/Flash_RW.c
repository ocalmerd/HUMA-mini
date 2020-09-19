/*
 * Flash_RW.c
 *
 *  Created on: Mar 23, 2020
 *      Author: MERT OCAL
 */

#include "Flash_RW.h"


void    FLASH_PageErase(uint32_t PageAddress);
HAL_StatusTypeDef  HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);


uint32_t PageError;


void Flash_ErasePage( uint32_t pageaddress )
{
	HAL_FLASH_Unlock();

//	HAL_FLASHEx_Erase( (FLASH_EraseInitTypeDef *) FLASH_TYPEERASE_MASSERASE, (uint32_t *) PageError);
	FLASH_PageErase( pageaddress );

	HAL_FLASH_Lock();
}

HAL_StatusTypeDef Flash_EEPROM_Data_Write( uint8_t page, uint32_t address, uint32_t index, void *writeBuffer )
{
	uint32_t flashAddress = address + (index*2);

    HAL_StatusTypeDef status = HAL_FLASH_Unlock();

    /* Fill EraseInit structure*/
    FLASH_EraseInitTypeDef EraseInitStruct;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = address;
    EraseInitStruct.NbPages = page;
    uint32_t error;


    if (status != HAL_OK)
        return status;

    // perform the erase first
    HAL_FLASHEx_Erase(&EraseInitStruct, &error);

    if (error) { return -1; }

	//Write to Flash
	for( uint32_t i = 0; i < 1; i++ )
	{
		status = HAL_FLASH_Program( FLASH_TYPEPROGRAM_HALFWORD, flashAddress, ( (uint16_t *)writeBuffer)[i] );
		if (status != HAL_OK)
			return status;


	    HAL_FLASH_Unlock();

	    return status;
	}

	//Lock the Flash space
	HAL_FLASH_Lock();

	return status;
}

void Flash_EEPROM_Data_Read( uint8_t page, uint32_t address, uint32_t index, void *readBuffer )
{
	uint32_t flashAddress = address + (index*2);

		*((uint16_t *)readBuffer) = *(uint32_t *)flashAddress;
}
