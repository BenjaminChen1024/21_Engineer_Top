/**
  ******************************************************************************
  * @file   : Service_Relay.cpp
  * @brief  : ����̵����ļ�
  ******************************************************************************
  * @note
  *  - 
**/

/* Includes ------------------------------------------------------------------*/
#include "Service_Relay.h"
/* Private variables ---------------------------------------------------------*/

/* �̵���״̬ --------------*/
float Relay_Time;
/* Private function prototypes -------------------------------------------------------*/

/**
* @brief  �̵�����ʼ������.
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
 * @brief  ��ʯ���Ӽ�ȡ����.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Pinch()  
{
    HAL_GPIO_WritePin(Relay_Pinch_Port, Relay_Pinch_Pin,GPIO_PIN_RESET);
    Pinch_Status = Relay_On;
}

/**
 * @brief  ��ʯ�����ɿ�����.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Loosen()  
{
    HAL_GPIO_WritePin(Relay_Pinch_Port, Relay_Pinch_Pin,GPIO_PIN_SET);
    Pinch_Status = Relay_Off;
}
/**
 * @brief  ��Ԯ�������.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Rescue() 
{
    HAL_GPIO_WritePin(Relay_Rescue_Port, Relay_Rescue_Pin,GPIO_PIN_RESET);
    Rescue_Status = Relay_On;
}

/**
 * @brief  ��Ԯ�ջغ���.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::Rescue_Back() 
{
    HAL_GPIO_WritePin(Relay_Rescue_Port, Relay_Rescue_Pin,GPIO_PIN_SET);
    Rescue_Status = Relay_Off;
}

/**
 * @brief  �汦��Ԯ�������.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::SuperRescue() 
{
    HAL_GPIO_WritePin(Relay_SuperRescue_Port, Relay_SuperRescue_Pin,GPIO_PIN_RESET);
    SuperRescue_Status = Relay_On;
}

/**
 * @brief  �汦��Ԯ�ջغ���.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::SuperRescue_Back() 
{
    HAL_GPIO_WritePin(Relay_SuperRescue_Port, Relay_SuperRescue_Pin,GPIO_PIN_SET);
    SuperRescue_Status = Relay_Off;
}

/**
 * @brief  ˢ���������.
 * @param  void.
 * @return void.
 */
void Relay_Classdef::ETC() 
{
    HAL_GPIO_WritePin(Relay_ETC_Port, Relay_ECT_Pin,GPIO_PIN_RESET);
    ETC_Status = Relay_On;
}

/**
 * @brief  ˢ���ջغ���.
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
