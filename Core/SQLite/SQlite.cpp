//
// Created by du-pc on 2023/7/18.
//

#include "SQlite.h"


uint16_t SQlite::FlashReadHalfWord(uint16_t address) {
    return *(uint16_t *)address;
}

bool SQlite::WriteHalfWord(uint16_t address, uint16_t value) {
    if (address<_address_base||address>(_address_base+_flashSize*1024)){
        rt_kprintf("地址不合法01");
        return false;
    }
    HAL_StatusTypeDef ret= HAL_FLASH_Program(FLASH_PROC_PROGRAMHALFWORD,address,value);

    if(ret!=HAL_OK){
        rt_kprintf("数据写入失败02");
        return false;
    }
    return true;
}

uint16_t *SQlite::ReadValue(std::string ValueName, uint16_t valueNum) {
    return nullptr;
}

bool SQlite::WriteValue(std::string ValueName, uint16_t *pData, uint16_t ValueNum) {
    return false;
}


