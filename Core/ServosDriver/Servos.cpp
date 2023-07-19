//
// Created by nblh on 2023/7/19.
//

#include "Servos.h"

void Servos::init() {

    if (GPIOA==static_cast<GPIO_TypeDef *>(&_GPIOX)){
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }else if (GPIOB==static_cast<GPIO_TypeDef *>(&_GPIOX)){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }else if(GPIOC==static_cast<GPIO_TypeDef *>(&_GPIOX)){
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }else if(GPIOD==static_cast<GPIO_TypeDef *>(&_GPIOX)){
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
    ServosGpioInitPinDef.Pin=_ServosGpioPin;
    ServosGpioInitPinDef.Speed=GPIO_SPEED_LOW;
    ServosGpioInitPinDef.Pull=GPIO_NOPULL;
    ServosGpioInitPinDef.Mode=GPIO_MODE_OUTPUT_OD;
    HAL_GPIO_Init(static_cast<GPIO_TypeDef *>(&_GPIOX),&ServosGpioInitPinDef);
}

Servos::Servos() {
}

void Servos::SetAngle(int _angle) {
    DelayTim=((2000*_angle)/180)+500;
    HAL_GPIO_WritePin(static_cast<GPIO_TypeDef *>(&_GPIOX), _ServosGpioPin, static_cast<GPIO_PinState>(SET));


}

uint16_t Servos::GetDelay() {
    return DelayTim;
}



