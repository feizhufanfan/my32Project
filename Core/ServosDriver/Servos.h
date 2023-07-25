//
// Created by nblh on 2023/7/19.
//

#ifndef TIM_DEMO_SERVOS_H
#define TIM_DEMO_SERVOS_H


#if __cplusplus
extern "C"{
#endif

#include <stdbool.h>
#include "rtthread.h"
#include "stm32f1xx_hal.h"




#if __cplusplus
};
#endif



extern GPIO_InitTypeDef ServosGpioInitPinDef;

void initServosGpioPinDef(GPIO_TypeDef *GPIOX, uint16_t GPIO_PIN);
void SetServosPWM(uint16_t Period, uint16_t Pluse);

#endif //TIM_DEMO_SERVOS_H
