/**
 * \file            hosal_flash.c
 * \brief           Hosal Flash driver file
 */

/*
 * Copyright (c) 2024 Rafale Micro
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:         ives.lee 
 */
#include <stdint.h>
#include "stdio.h"

#include "mcu.h"
#include "hosal_status.h"
#include "hosal_flash.h"


int hosal_flash_enable_qe(void) {
    flash_enable_qe();
    return HOSAL_STATUS_SUCCESS;
}

int hosal_flash_init(void) {
    return HOSAL_STATUS_SUCCESS;
}

int hosal_flash_read(int ctl, uint32_t address, uint8_t* buf) {

    uint32_t  status = 0, buf_address;

    if (flash_check_busy()) {

        return HOSAL_STATUS_EBUSY;
    }

    switch (ctl) {
        case HOSAL_FLASH_READ_BYTE:
            buf[0] = flash_read_byte(address);
            return STATUS_SUCCESS;
        case HOSAL_FLASH_READ_PAGE:
            return flash_read_page_syncmode((uint32_t)buf, address);
        case HOSAL_FLASH_SECURITY_READ:
            return flash_read_sec_register((uint32_t)buf, address);   
        default:
            return -1;
    }
}

int hosal_flash_write(int ctl, uint32_t address, uint8_t* buf) {

    uint32_t  status = HOSAL_STATUS_SUCCESS;

    if (flash_check_busy()) {
        
        return HOSAL_STATUS_EBUSY;
    }

    switch (ctl) {
        case HOSAL_FLASH_WRITE_BYTE:
            flash_write_byte(address, buf[0]);
            return HOSAL_STATUS_SUCCESS;
        case HOSAL_FLASH_WRITE_PAGE:
            return flash_write_page((uint32_t)buf, address);
        case HOSAL_FLASH_SECURITY_WRITE:
            return flash_write_sec_register(address, (uint32_t)buf);
        default:
            return -1;
    }
}

int hosal_flash_erase(int ctl, uint32_t address) {
    

    if (flash_check_busy()) {

        return HOSAL_STATUS_EBUSY;
    }

    switch (ctl) {
        case HOSAL_FLASH_ERASE_PAGE: //Only Support 512k flash
            return flash_erase(FLASH_ERASE_PAGE, address);
        case HOSAL_FLASH_ERASE_SECTOR:
            return flash_erase(FLASH_ERASE_SECTOR, address);
        case HOSAL_FLASH_ERASE_32K_SECTOR:
            return flash_erase(FLASH_ERASE_32K, address);
        case HOSAL_FLASH_ERASE_64K_SECTOR:
            return flash_erase(FLASH_ERASE_64K, address);
        case HOSAL_FLASH_ERASE_CHIP:
            return HOSAL_STATUS_ERROR;
        default:
            return -1;
    }
}

int hosal_flash_ioctrl(int ctl, void *p_arg) {
    switch (ctl) {
        case HOSAL_FLASH_ENABLE_SUSPEND:
            flash_enable_suspend();
            return HOSAL_STATUS_SUCCESS;
        case HOSAL_FLASH_DISABLE_SUSPEND:
            flash_disable_suspend();
            return HOSAL_STATUS_SUCCESS;
        case HOSAL_FLASH_CACHE:
            flush_cache();
            return HOSAL_STATUS_SUCCESS;
        case HOSAL_FLASH_BUSY:
            return flash_check_busy();
        case HOSAL_FLASH_GET_INFO:
        *(uint32_t*)p_arg = flash_get_deviceinfo();

        return HOSAL_STATUS_SUCCESS;

        break;          
        default:
            return -1;
    }
}


int hosal_flash_read_id(uint32_t length, uint8_t* buf) {


    flash_get_unique_id((uint32_t)buf, length);    

    return HOSAL_STATUS_SUCCESS;
 
}