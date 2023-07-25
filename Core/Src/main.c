/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "rtthread.h"
#include "i2c.h"
#include "ssd1306.h"
#include "mpu6050.h"
#include "Servos.h"

#define SerovsGPIOX GPIOA
#define SerovsGPIOPin GPIO_PIN_6

extern uint16_t ServoisPWMPeriod;
extern uint16_t ServoisPluse;
extern bool isTriger;

/**
  * @brief  The application entry point.
  * @retval int
  */
uint16_t pwm_set = 0;
uint16_t pwm_max = 1700;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance==TIM1){//10us
        static int pwm_val=0;
        static uint16_t Count=0;
        pwm_val++;
        if(pwm_val<pwm_set){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,(RESET));
            HAL_GPIO_WritePin(SerovsGPIOX,SerovsGPIOPin,SET);
        }
        if(pwm_val>pwm_set){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (SET));
            HAL_GPIO_WritePin(SerovsGPIOX,SerovsGPIOPin,RESET);
        }
        if(pwm_val == pwm_max) pwm_val = 0;

//        if(Count%ServoisPWMPeriod<ServoisPluse)  HAL_GPIO_WritePin(SerovsGPIOX, SerovsGPIOPin,SET);
//        if(Count%ServoisPWMPeriod>ServoisPluse) HAL_GPIO_WritePin(SerovsGPIOX, SerovsGPIOPin,RESET);


//        if (Count%40000){
//            static int d3elayms=0;
//            if (d3elayms%50==0)
//            Servos1.SetAngle(Count%180);
//            d3elayms++;
//        }

        Count++;
    }
}
void mpu6050(void *UserData){




    float temp= MPU_Get_Temperature();
    short accX,accY,accZ;
    MPU_Get_Accelerometer(&accX,&accY,&accZ);
    short gX,gY,gZ;
    MPU_Get_Gyroscope(&gX,&gY,&gZ);
    rt_kprintf("temp:%d accX:%i accY:%i accZ:%i gX:%i gY:%i gZ:%i\n",temp,accX,accY,accZ,gX,gY,gZ);
    rt_thread_mdelay(10);


//    if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//    {
//        temp=MPU_Get_Temperature();								//得到温度值
//        MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
//        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
//        printf("三轴角度：%f-%f-%f\r\n",pitch,roll,yaw);
//        printf("三轴加速度：%d-%d-%d\r\n",aacx,aacy,aacz);
//        printf("三轴角角度：%d-%d-%d\r\n",gyrox,gyroy,gyroz);
//    }
   // rt_thread_mdelay(100);

}

int main(void)
{
    uint8_t dir = 1;
   // Servos1.InitGpiodef(SerovsGPIOX, SerovsGPIOPin);
    MX_GPIO_Init();
    initServosGpioPinDef(SerovsGPIOX,SerovsGPIOPin);
    SetServosPWM(1700,50);
    initI2C();
    initDMA();
    MX_TIM1_Init();
    MX_TIM2_Init();
   //ssd1306_Init();
   // MPU_Init();

//    rt_thread_t MPU6050Thread= rt_thread_create("MPU6050",mpu6050,NULL,256,10,5);
//    rt_thread_startup(MPU6050Thread);

  while (1)
  {

      if(dir)
      {
          rt_thread_mdelay(100);
          pwm_set++;
          if(pwm_set ==(pwm_max*0.120)) dir = 0;
      }
      if(!dir)
      {
          rt_thread_mdelay(100);
          pwm_set--;
          if(pwm_set == 0) dir = 1;
      }




      //mpu6050(NULL);
     // rt_thread_mdelay(1000);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

