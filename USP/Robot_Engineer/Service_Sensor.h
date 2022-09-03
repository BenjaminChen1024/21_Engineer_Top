/**
  ******************************************************************************
  * @file   : Service_Sensor.h
  * @brief  : Service_Sensor.cppÍ·ÎÄ¼þ
  ****************************************************************************** 
**/
#ifndef _SERVICE_SENSOR_H_
#define _SERVICE_SENSOR_H_
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* Private defines ------------------------------------------------------------*/
#define  PR_F1_Port       GPIOB
#define  PR_F1_Pin        GPIO_PIN_4
#define  PR_F2_Port       GPIOB
#define  PR_F2_Pin        GPIO_PIN_3
#define  PR_F3_Port       GPIOB
#define  PR_F3_Pin        GPIO_PIN_8
#define  PR_F4_Port       GPIOB
#define  PR_F4_Pin        GPIO_PIN_6
#define  PR_F5_Port       GPIOB
#define  PR_F5_Pin        GPIO_PIN_5
#define  PR_F6_Port       GPIOB
#define  PR_F6_Pin        GPIO_PIN_9
#define  PR_F7_Port       GPIOA
#define  PR_F7_Pin        GPIO_PIN_4
#define  PR_F8_Port       GPIOC
#define  PR_F8_Pin        GPIO_PIN_2

#define PR_F1_Status			PR_Status[0]
#define PR_F2_Status			PR_Status[1]
#define PR_F3_Status			PR_Status[2]
#define PR_F4_Status			PR_Status[3]
#define PR_F5_Status			PR_Status[4]
#define PR_F6_Status			PR_Status[5]
#define PR_F7_Status			PR_Status[6]
#define PR_F8_Status			PR_Status[7]


/* Private variables ---------------------------------------------------------*/

enum SensorStatusTypedef
{
	OFF,
	ON
};
/* Private function declarations ---------------------------------------------*/


class Sensor_Classdef
{
	private:
		SensorStatusTypedef PR_F1();
		SensorStatusTypedef PR_F2();
		SensorStatusTypedef PR_F3();
		SensorStatusTypedef PR_F4();
		SensorStatusTypedef PR_F5();
		SensorStatusTypedef PR_F6();
		SensorStatusTypedef PR_F7();
		SensorStatusTypedef PR_F8();
	public:
		void PR_Updata();
		void PR_RESET();
		uint8_t PR_Status[8];
};

#endif
