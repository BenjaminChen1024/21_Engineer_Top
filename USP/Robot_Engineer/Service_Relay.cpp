/**
  ******************************************************************************
  * @file   : Service_Relay.cpp
  * @brief  : 服务继电器文件
  ******************************************************************************
  * @note
  *  - 
**/

/* Includes ------------------------------------------------------------------*/
#include "Service_Relay.h"
/* Private variables ---------------------------------------------------------*/

/* 继电器状态 --------------*/
float Relay_Time;
/* Private function prototypes -------------------------------------------------------*/

/**
* @brief  继电器初始化函数.
* @param  void.
* @return void.
* @note  	None.
*/
void Relay_Classdef::Relay_Init()
{
	HAL_GPIO_WritePin(Relay_Pinch_Port, Relay_Pinch_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Relay_Rescue_Port, Relay_Rescue_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Relay_SuperRescue_Port, Relay_SuperRescue_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Relay_ETC_Port, Relay_ECT_Pin, GPIO_PIN_SET);
	Pinch_Status = Relay_Off;
  Rescue_Status = Relay_Off;
  SuperRescue_Status = Relay_Off;
  Rescue_Status = Relay_Off;
}

void Relay_Classdef::Relay_Open()
{
	HAL_GPIO_WritePin(Relay_Pinch_Port, Relay_Pinch_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Relay_Rescue_Port, Relay_Rescue_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Relay_SuperRescue_Port, Relay_SuperRescue_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Relay_ETC_Port, Relay_ECT_Pin, GPIO_PIN_RESET);
	Pinch_Status = Relay_On;
  Rescue_Status = Relay_On;
  SuperRescue_Status = Relay_On;
  Rescue_Status = Relay_On;
}

void Relay_Classdef::Relay_Reset()
{
  HAL_GPIO_WritePin(Relay_Rescue_Port, Relay_Rescue_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Relay_SuperRescue_Port, Relay_SuperRescue_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Relay_ETC_Port, Relay_ECT_Pin, GPIO_PIN_SET);
  Rescue_Status = Relay_Off;
  SuperRescue_Status = Relay_Off;
  Rescue_Status = Relay_Off;
}

/**
 * @brief  矿石夹子夹取函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Pinch()  
{
    HAL_GPIO_WritePin(Relay_Pinch_Port, Relay_Pinch_Pin,GPIO_PIN_RESET);
    Pinch_Status = Relay_On;
}

/**
 * @brief  矿石夹子松开函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Loosen()  
{
    HAL_GPIO_WritePin(Relay_Pinch_Port, Relay_Pinch_Pin,GPIO_PIN_SET);
    Pinch_Status = Relay_Off;
}
/**
 * @brief  救援伸出函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Rescue() 
{
    HAL_GPIO_WritePin(Relay_Rescue_Port, Relay_Rescue_Pin,GPIO_PIN_RESET);
    Rescue_Status = Relay_On;
}

/**
 * @brief  救援收回函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Rescue_Back() 
{
    HAL_GPIO_WritePin(Relay_Rescue_Port, Relay_Rescue_Pin,GPIO_PIN_SET);
    Rescue_Status = Relay_Off;
}

/**
 * @brief  舵宝救援伸出函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::SuperRescue() 
{
    HAL_GPIO_WritePin(Relay_SuperRescue_Port, Relay_SuperRescue_Pin,GPIO_PIN_RESET);
    SuperRescue_Status = Relay_On;
}

/**
 * @brief  舵宝救援收回函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::SuperRescue_Back() 
{
    HAL_GPIO_WritePin(Relay_SuperRescue_Port, Relay_SuperRescue_Pin,GPIO_PIN_SET);
    SuperRescue_Status = Relay_Off;
}

/**
 * @brief  刷卡伸出函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::ETC() 
{
    HAL_GPIO_WritePin(Relay_ETC_Port, Relay_ECT_Pin,GPIO_PIN_RESET);
    ETC_Status = Relay_On;
}

/**
 * @brief  刷卡收回函数.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::ETC_Back() 
{
    HAL_GPIO_WritePin(Relay_ETC_Port, Relay_ECT_Pin,GPIO_PIN_SET);
    ETC_Status = Relay_Off;
}


uint8_t Relay_Delay(float Time)
{
	Relay_Time ++;
	if(Relay_Time >= Time)
	{
		Relay_Time =0;
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void Relay_Delay_Clear()
{
		Relay_Time =0;
}

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
