//
// Created by nblh on 2023/7/19.
//

#include "Servos.h"

GPIO_InitTypeDef ServosGpioInitPinDef;
uint16_t ServoisPWMPeriod=0;
uint16_t ServoisPluse=0;
bool isTriger=false;



void initServosGpioPinDef(GPIO_TypeDef *GPIOX, uint16_t GPIO_PIN) {
    if (GPIOX==GPIOA){
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }else if(GPIOX==GPIOB){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }else if(GPIOX==GPIOC){
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }else if(GPIOX==GPIOD){
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOX, GPIO_PIN, GPIO_PIN_RESET);

    /*Configure GPIO pin : PC13 */
    ServosGpioInitPinDef.Pin = GPIO_PIN;
    ServosGpioInitPinDef.Mode = GPIO_MODE_OUTPUT_PP;
    ServosGpioInitPinDef.Pull = GPIO_NOPULL;
    ServosGpioInitPinDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOX, &ServosGpioInitPinDef);
}

void SetServosPWM(uint16_t Period, uint16_t Pluse) {
    ServoisPWMPeriod=Period;//20ms的周期
    //per Count= ServoisPWMPeriod/20
    ServoisPluse=ServoisPWMPeriod+(ServoisPWMPeriod*Pluse*0.01);
}

