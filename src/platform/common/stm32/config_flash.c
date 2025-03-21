/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "platform.h"
#include "drivers/system.h"
#include "config/config_streamer.h"
#include "config/config_streamer_impl.h"

#if defined(CONFIG_IN_FLASH)

#if !defined(FLASH_PAGE_SIZE)
#error "Flash page size not defined for STM (or clone) target."
#endif

#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F765xx)
/*
Sector 0    0x08000000 - 0x08007FFF 32 Kbytes
Sector 1    0x08008000 - 0x0800FFFF 32 Kbytes
Sector 2    0x08010000 - 0x08017FFF 32 Kbytes
Sector 3    0x08018000 - 0x0801FFFF 32 Kbytes
Sector 4    0x08020000 - 0x0803FFFF 128 Kbytes
Sector 5    0x08040000 - 0x0807FFFF 256 Kbytes
Sector 6    0x08080000 - 0x080BFFFF 256 Kbytes
Sector 7    0x080C0000 - 0x080FFFFF 256 Kbytes

F7X5XI device with 2M flash
Sector 8    0x08100000 - 0x0813FFFF 256 Kbytes
Sector 9    0x08140000 - 0x0817FFFF 256 Kbytes
Sector 10   0x08180000 - 0x081BFFFF 256 Kbytes
Sector 11   0x081C0000 - 0x081FFFFF 256 Kbytes
*/

uint32_t getFLASHSectorForEEPROM(void)
{
    if ((uint32_t)&__config_start <= 0x08007FFF)
        return FLASH_SECTOR_0;
    if ((uint32_t)&__config_start <= 0x0800FFFF)
        return FLASH_SECTOR_1;
    if ((uint32_t)&__config_start <= 0x08017FFF)
        return FLASH_SECTOR_2;
    if ((uint32_t)&__config_start <= 0x0801FFFF)
        return FLASH_SECTOR_3;
    if ((uint32_t)&__config_start <= 0x0803FFFF)
        return FLASH_SECTOR_4;
    if ((uint32_t)&__config_start <= 0x0807FFFF)
        return FLASH_SECTOR_5;
    if ((uint32_t)&__config_start <= 0x080BFFFF)
        return FLASH_SECTOR_6;
    if ((uint32_t)&__config_start <= 0x080FFFFF)
        return FLASH_SECTOR_7;
#if defined(STM32F765xx)
    if ((uint32_t)&__config_start <= 0x0813FFFF)
        return FLASH_SECTOR_8;
    if ((uint32_t)&__config_start <= 0x0817FFFF)
        return FLASH_SECTOR_9;
    if ((uint32_t)&__config_start <= 0x081BFFFF)
        return FLASH_SECTOR_10;
    if ((uint32_t)&__config_start <= 0x081FFFFF)
        return FLASH_SECTOR_11;
#endif

    // Not good
    while (1) {
        failureMode(FAILURE_CONFIG_STORE_FAILURE);
    }
}

#elif defined(STM32F722xx)
/*
Sector 0    0x08000000 - 0x08003FFF 16 Kbytes
Sector 1    0x08004000 - 0x08007FFF 16 Kbytes
Sector 2    0x08008000 - 0x0800BFFF 16 Kbytes
Sector 3    0x0800C000 - 0x0800FFFF 16 Kbytes
Sector 4    0x08010000 - 0x0801FFFF 64 Kbytes
Sector 5    0x08020000 - 0x0803FFFF 128 Kbytes
Sector 6    0x08040000 - 0x0805FFFF 128 Kbytes
Sector 7    0x08060000 - 0x0807FFFF 128 Kbytes
*/

uint32_t getFLASHSectorForEEPROM(void)
{
    if ((uint32_t)&__config_start <= 0x08003FFF)
        return FLASH_SECTOR_0;
    if ((uint32_t)&__config_start <= 0x08007FFF)
        return FLASH_SECTOR_1;
    if ((uint32_t)&__config_start <= 0x0800BFFF)
        return FLASH_SECTOR_2;
    if ((uint32_t)&__config_start <= 0x0800FFFF)
        return FLASH_SECTOR_3;
    if ((uint32_t)&__config_start <= 0x0801FFFF)
        return FLASH_SECTOR_4;
    if ((uint32_t)&__config_start <= 0x0803FFFF)
        return FLASH_SECTOR_5;
    if ((uint32_t)&__config_start <= 0x0805FFFF)
        return FLASH_SECTOR_6;
    if ((uint32_t)&__config_start <= 0x0807FFFF)
        return FLASH_SECTOR_7;

    // Not good
    while (1) {
        failureMode(FAILURE_CONFIG_STORE_FAILURE);
    }
}

#elif defined(STM32F4)
/*
Sector 0    0x08000000 - 0x08003FFF 16 Kbytes
Sector 1    0x08004000 - 0x08007FFF 16 Kbytes
Sector 2    0x08008000 - 0x0800BFFF 16 Kbytes
Sector 3    0x0800C000 - 0x0800FFFF 16 Kbytes
Sector 4    0x08010000 - 0x0801FFFF 64 Kbytes
Sector 5    0x08020000 - 0x0803FFFF 128 Kbytes
Sector 6    0x08040000 - 0x0805FFFF 128 Kbytes
Sector 7    0x08060000 - 0x0807FFFF 128 Kbytes
Sector 8    0x08080000 - 0x0809FFFF 128 Kbytes
Sector 9    0x080A0000 - 0x080BFFFF 128 Kbytes
Sector 10   0x080C0000 - 0x080DFFFF 128 Kbytes
Sector 11   0x080E0000 - 0x080FFFFF 128 Kbytes
*/

uint32_t getFLASHSectorForEEPROM(void)
{
    if ((uint32_t)&__config_start <= 0x08003FFF)
        return FLASH_Sector_0;
    if ((uint32_t)&__config_start <= 0x08007FFF)
        return FLASH_Sector_1;
    if ((uint32_t)&__config_start <= 0x0800BFFF)
        return FLASH_Sector_2;
    if ((uint32_t)&__config_start <= 0x0800FFFF)
        return FLASH_Sector_3;
    if ((uint32_t)&__config_start <= 0x0801FFFF)
        return FLASH_Sector_4;
    if ((uint32_t)&__config_start <= 0x0803FFFF)
        return FLASH_Sector_5;
    if ((uint32_t)&__config_start <= 0x0805FFFF)
        return FLASH_Sector_6;
    if ((uint32_t)&__config_start <= 0x0807FFFF)
        return FLASH_Sector_7;
    if ((uint32_t)&__config_start <= 0x0809FFFF)
        return FLASH_Sector_8;
    if ((uint32_t)&__config_start <= 0x080DFFFF)
        return FLASH_Sector_9;
    if ((uint32_t)&__config_start <= 0x080BFFFF)
        return FLASH_Sector_10;
    if ((uint32_t)&__config_start <= 0x080FFFFF)
        return FLASH_Sector_11;

    // Not good
    while (1) {
        failureMode(FAILURE_CONFIG_STORE_FAILURE);
    }
}

#elif defined(STM32H743xx) || defined(STM32G4) || defined(STM32H7A3xx) || defined(STM32H7A3xxQ) || defined(STM32H723xx) || defined(STM32H725xx)
/*
MCUs with uniform array of equal size sectors, handled in two banks having contiguous address.
(Devices with non-contiguous flash layout is not currently useful anyways.)

H743
2 bank * 8 sector/bank * 128K/sector (2MB)
Bank 1 0x08000000 - 0x080FFFFF 128KB * 8
Bank 2 0x08100000 - 0x081FFFFF 128KB * 8

H743
1 bank * 8 sector/bank * 128K/sector (1MB)
Bank 1 0x08000000 - 0x080FFFFF 128KB * 8

H7A3
2 bank * 128 sector/bank * 8KB/sector (2MB)
Bank 1 0x08000000 - 0x080FFFFF 8KB * 128
Bank 2 0x08100000 - 0x081FFFFF 8KB * 128

G473/474 in dual bank mode
2 bank * 128 sector/bank * 2KB/sector (512KB)
Bank 1 0x08000000 - 0x0803FFFF 2KB * 128
Bank 2 0x08040000 - 0x0807FFFF 2KB * 128

Note that FLASH_BANK_SIZE constant used in the following code changes depending on
bank operation mode. The code assumes dual bank operation, in which case the
FLASH_BANK_SIZE constant is set to one half of the available flash size in HAL.
*/

#if defined(STM32H743xx) || defined(STM32H723xx) || defined(STM32H725xx)
#define FLASH_PAGE_PER_BANK 8
#elif defined(STM32H7A3xx) || defined(STM32H7A3xxQ)
#define FLASH_PAGE_PER_BANK 128
#elif defined(STM32G4)
#define FLASH_PAGE_PER_BANK 128
// These are not defined in CMSIS like H7
#define FLASH_BANK1_BASE FLASH_BASE
#define FLASH_BANK2_BASE (FLASH_BANK1_BASE + FLASH_BANK_SIZE)
#endif

void getFLASHSectorForEEPROM(uint32_t address, uint32_t *bank, uint32_t *sector)
{
#if defined(FLASH_BANK2_BASE)
    if (address >= FLASH_BANK1_BASE && address < FLASH_BANK2_BASE) {
        *bank = FLASH_BANK_1;
    } else if (address >= FLASH_BANK2_BASE && address < FLASH_BANK2_BASE + FLASH_BANK_SIZE) {
        *bank = FLASH_BANK_2;
        address -= FLASH_BANK_SIZE;
    }
#else
    if (address >= FLASH_BANK1_BASE && address < FLASH_BANK1_BASE + FLASH_BANK_SIZE) {
        *bank = FLASH_BANK_1;
    }
#endif
    else {
        // Not good
        while (1) {
            failureMode(FAILURE_CONFIG_STORE_FAILURE);
        }
    }

    address -= FLASH_BANK1_BASE;
    *sector = address / FLASH_PAGE_SIZE;
}
#elif defined(STM32H750xx)
/*
The memory map supports 2 banks of 8 128k sectors like the H743xx, but there is only one 128K sector so we save some code
space by using a smaller function.

Bank 1
Sector 0    0x08000000 - 0x0801FFFF 128 Kbytes

*/

void getFLASHSectorForEEPROM(uint32_t *bank, uint32_t *sector)
{

    uint32_t start = (uint32_t)&__config_start;

    if (start == FLASH_BANK1_BASE) {
        *sector = FLASH_SECTOR_0;
        *bank = FLASH_BANK_1;
    } else {
        // Not good
        while (1) {
            failureMode(FAILURE_CONFIG_STORE_FAILURE);
        }
    }
}
#elif defined(APM32F4)
/*
Sector 0    0x08000000 - 0x08003FFF 16 Kbytes
Sector 1    0x08004000 - 0x08007FFF 16 Kbytes
Sector 2    0x08008000 - 0x0800BFFF 16 Kbytes
Sector 3    0x0800C000 - 0x0800FFFF 16 Kbytes
Sector 4    0x08010000 - 0x0801FFFF 64 Kbytes
Sector 5    0x08020000 - 0x0803FFFF 128 Kbytes
Sector 6    0x08040000 - 0x0805FFFF 128 Kbytes
Sector 7    0x08060000 - 0x0807FFFF 128 Kbytes
Sector 8    0x08080000 - 0x0809FFFF 128 Kbytes
Sector 9    0x080A0000 - 0x080BFFFF 128 Kbytes
Sector 10   0x080C0000 - 0x080DFFFF 128 Kbytes
Sector 11   0x080E0000 - 0x080FFFFF 128 Kbytes
*/

uint32_t getFLASHSectorForEEPROM(void)
{
    if ((uint32_t)&__config_start <= 0x08003FFF)
        return FLASH_SECTOR_0;
    if ((uint32_t)&__config_start <= 0x08007FFF)
        return FLASH_SECTOR_1;
    if ((uint32_t)&__config_start <= 0x0800BFFF)
        return FLASH_SECTOR_2;
    if ((uint32_t)&__config_start <= 0x0800FFFF)
        return FLASH_SECTOR_3;
    if ((uint32_t)&__config_start <= 0x0801FFFF)
        return FLASH_SECTOR_4;
    if ((uint32_t)&__config_start <= 0x0803FFFF)
        return FLASH_SECTOR_5;
    if ((uint32_t)&__config_start <= 0x0805FFFF)
        return FLASH_SECTOR_6;
    if ((uint32_t)&__config_start <= 0x0807FFFF)
        return FLASH_SECTOR_7;
    if ((uint32_t)&__config_start <= 0x0809FFFF)
        return FLASH_SECTOR_8;
    if ((uint32_t)&__config_start <= 0x080DFFFF)
        return FLASH_SECTOR_9;
    if ((uint32_t)&__config_start <= 0x080BFFFF)
        return FLASH_SECTOR_10;
    if ((uint32_t)&__config_start <= 0x080FFFFF)
        return FLASH_SECTOR_11;

    // Not good
    while (1) {
        failureMode(FAILURE_CONFIG_STORE_FAILURE);
    }
}
#endif

void configUnlock(void)
{
#if defined(STM32F7) || defined(STM32H7) || defined(STM32G4)
    HAL_FLASH_Unlock();
#elif defined(APM32F4)
    DAL_FLASH_Unlock();
#elif defined(AT32F4)
    flash_unlock();
#else
    FLASH_Unlock();
#endif
}

void configLock(void)
{
#if defined(STM32F7) || defined(STM32H7) || defined(STM32G4)
        HAL_FLASH_Lock();
#elif defined(AT32F4)
        flash_lock();
#elif defined(APM32F4)
        DAL_FLASH_Lock();
#else
        FLASH_Lock();
#endif
}

void configClearFlags(void)
{
#if defined(STM32F4)
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
#elif defined(STM32F7)
    // NOP
#elif defined(STM32H7)
    // NOP
#elif defined(STM32G4)
    // NOP
#elif defined(AT32F4)
    flash_flag_clear(FLASH_ODF_FLAG | FLASH_PRGMERR_FLAG | FLASH_EPPERR_FLAG);
#elif defined(APM32F4)
    __DAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
#elif defined(UNIT_TEST) || defined(SIMULATOR_BUILD)
    // NOP
#else
# error "Unsupported CPU"
#endif
}

configStreamerResult_e configWriteWord(uintptr_t address, config_streamer_buffer_type_t *buffer)
{
#if defined(STM32H7)
    if (address % FLASH_PAGE_SIZE == 0) {
        FLASH_EraseInitTypeDef EraseInitStruct = {
            .TypeErase     = FLASH_TYPEERASE_SECTORS,
#if !(defined(STM32H7A3xx) || defined(STM32H7A3xxQ))
            .VoltageRange  = FLASH_VOLTAGE_RANGE_3, // 2.7-3.6V
#endif
            .NbSectors     = 1
        };
        getFLASHSectorForEEPROM(address, &EraseInitStruct.Banks, &EraseInitStruct.Sector);
        uint32_t SECTORError;
        const HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
        if (status != HAL_OK) {
            return CONFIG_RESULT_FAILURE;
        }
    }

    // For H7
    // HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress);
    STATIC_ASSERT(CONFIG_STREAMER_BUFFER_SIZE == sizeof(uint32_t) * FLASH_NB_32BITWORD_IN_FLASHWORD,  "CONFIG_STREAMER_BUFFER_SIZE does not match written size");
    const HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, address, (uint32_t)buffer);
    if (status != HAL_OK) {
        return CONFIG_RESULT_ADDRESS_INVALID;
    }
#elif defined(STM32F7)
    if (address % FLASH_PAGE_SIZE == 0) {
        FLASH_EraseInitTypeDef EraseInitStruct = {
            .TypeErase     = FLASH_TYPEERASE_SECTORS,
            .VoltageRange  = FLASH_VOLTAGE_RANGE_3, // 2.7-3.6V
            .NbSectors     = 1
        };
        EraseInitStruct.Sector = getFLASHSectorForEEPROM();
        uint32_t SECTORError;
        const HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
        if (status != HAL_OK) {
            return CONFIG_RESULT_FAILURE;
        }
    }

    STATIC_ASSERT(CONFIG_STREAMER_BUFFER_SIZE == sizeof(uint32_t),  "CONFIG_STREAMER_BUFFER_SIZE does not match written size");
    // For F7
    // HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
    const HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *buffer);
    if (status != HAL_OK) {
        return CONFIG_RESULT_INCOMPLETE;
    }
#elif defined(STM32G4)
    if (address % FLASH_PAGE_SIZE == 0) {

        FLASH_EraseInitTypeDef EraseInitStruct = {
            .TypeErase     = FLASH_TYPEERASE_PAGES,
            .NbPages       = 1
        };
        getFLASHSectorForEEPROM(address, &EraseInitStruct.Banks, &EraseInitStruct.Page);
        uint32_t SECTORError;
        const HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
        if (status != HAL_OK) {
            return CONFIG_RESULT_FAILURE;
        }
    }

    STATIC_ASSERT(CONFIG_STREAMER_BUFFER_SIZE == sizeof(uint64_t),  "CONFIG_STREAMER_BUFFER_SIZE does not match written size");
    const HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, *buffer);
    if (status != HAL_OK) {
        return CONFIG_RESULT_ADDRESS_INVALID;
    }
#elif defined(AT32F4)
    if (address % FLASH_PAGE_SIZE == 0) {
        const flash_status_type status = flash_sector_erase(address);
        if (status != FLASH_OPERATE_DONE) {
            return CONFIG_RESULT_FAILURE;
        }
    }

    STATIC_ASSERT(CONFIG_STREAMER_BUFFER_SIZE == sizeof(uint32_t),  "CONFIG_STREAMER_BUFFER_SIZE does not match written size");
    const flash_status_type status = flash_word_program(address, *buffer);
    if (status != FLASH_OPERATE_DONE) {
        return CONFIG_RESULT_ADDRESS_INVALID;
    }
#elif defined(APM32F4)
    if (address % FLASH_PAGE_SIZE == 0) {
        FLASH_EraseInitTypeDef EraseInitStruct = {
            .TypeErase     = FLASH_TYPEERASE_SECTORS,
            .VoltageRange  = FLASH_VOLTAGE_RANGE_3, // 2.7-3.6V
            .NbSectors     = 1
        };
        EraseInitStruct.Sector = getFLASHSectorForEEPROM();
        uint32_t SECTORError;
        const DAL_StatusTypeDef status = DAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
        if (status != DAL_OK) {
            return CONFIG_RESULT_FAILURE;
        }
    }

    STATIC_ASSERT(CONFIG_STREAMER_BUFFER_SIZE == sizeof(uint32_t),  "CONFIG_STREAMER_BUFFER_SIZE does not match written size");
    const DAL_StatusTypeDef status = DAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *buffer);
    if (status != DAL_OK) {
        return CONFIG_RESULT_ADDRESS_INVALID;
    }
#elif defined(STM32F4)
    if (address % FLASH_PAGE_SIZE == 0) {
        const FLASH_Status status = FLASH_EraseSector(getFLASHSectorForEEPROM(), VoltageRange_3); //0x08080000 to 0x080A0000
        if (status != FLASH_COMPLETE) {
            return CONFIG_RESULT_FAILURE;
        }
    }

    STATIC_ASSERT(CONFIG_STREAMER_BUFFER_SIZE == sizeof(uint32_t),  "CONFIG_STREAMER_BUFFER_SIZE does not match written size");
    const FLASH_Status status = FLASH_ProgramWord(address, *buffer);
    if (status != FLASH_COMPLETE) {
        return CONFIG_RESULT_ADDRESS_INVALID;
    }
#else
#error "MCU not catered for in configWriteWord for config_streamer"
#endif
    return CONFIG_RESULT_SUCCESS;
}

#endif // CONFIG_IN_FLASH
