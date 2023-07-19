//
// Created by du-pc on 2023/7/18.
//

#ifndef TIM_DEMO_SQLITE_H
#define TIM_DEMO_SQLITE_H

//#include <iostream>
#include <vector>
#include <string>
#if __cplusplus
extern "C"{
#endif

#include "rtthread.h"
#include "stm32f1xx_hal.h"

#if __cplusplus
};
#endif



class SQlite{
public:
    /**
     *
     * @param FlashStartAddress Flash存储器开始地址
     * @param FlashSize Flash大小 单位KB  常见STM32F103C8T6 64KB 、STM32F103C6T6 32KB
     * @param DataOffset 用于存储数据的偏移 单位KB
     */
    SQlite(uint32_t FlashStartAddress=0x08000000,uint16_t FlashSize=32,uint16_t DataOffset=0):_address_base(FlashStartAddress),_flashSize(FlashSize),_dataOffset(DataOffset){};

    uint16_t* ReadValue(std::string ValueName,uint16_t valueNum=1);
    bool WriteValue(std::string ValueName,uint16_t *pData,uint16_t ValueNum=1);

private:
    uint16_t* Read(std::string ValueName,uint16_t valueNum=1);
    bool Write(std::string ValueName,uint16_t *pData,uint16_t ValueNum=1);
    uint16_t FlashReadHalfWord(uint16_t address);
    bool WriteHalfWord(uint16_t address,uint16_t value);

private:
    uint32_t _address_base{0};
    uint16_t _flashSize{0};
    uint16_t _dataOffset{0};
    std::vector<std::pair<std::string,uint16_t>> ValueMap;

};
#endif //TIM_DEMO_SQLITE_H
