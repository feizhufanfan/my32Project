//
// Created by nblh on 2023/7/19.
//

#ifndef TIM_DEMO_SERVOS_H
#define TIM_DEMO_SERVOS_H

#include <functional>
#if __cplusplus
extern "C"{
#endif
#include "rtthread.h"
#include "stm32f1xx_hal.h"


#define GPIOA_RCC_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();
#define GPIOB_RCC_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE();
#define GPIOC_RCC_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE();
#define GPIOD_RCC_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE();

#if __cplusplus
};
#endif

class Servos {
public:
    Servos();

    void InitGpiodef(GPIO_TypeDef* GPIOx,uint16_t GPIO_PIN){
        _GPIOX=*GPIOx;
        _ServosGpioPin=GPIO_PIN;
        init();
    };

    void SetAngle(int _angle);

    uint16_t GetDelay();

    bool GetisTro(){
        return isTro;
    }
    void SetisTro(bool flags){
        isTro=flags;
    }

private:
    void init();

private:
    GPIO_TypeDef _GPIOX;
    uint16_t _ServosGpioPin;
    GPIO_InitTypeDef ServosGpioInitPinDef;
    int DelayTim=0;
    bool isTro{false};
};


#endif //TIM_DEMO_SERVOS_H
