/*
 * Flash_RW.h
 *
 *  Created on: Mar 23, 2020
 *      Author: MERT OCAL
 */

#ifndef SRC_FLASH_RW_H_
#define SRC_FLASH_RW_H_


#include "main.h"


void Flash_ErasePage( uint32_t page );

void Flash_EEPROM_Data_Write( uint8_t sector, uint32_t address, uint32_t index, uint16_t * writeBuffer );

void Flash_EEPROM_Data_Read( uint8_t sector, uint32_t address, uint32_t index, void *readBuffer );


#endif /* SRC_FLASH_RW_H_ */
