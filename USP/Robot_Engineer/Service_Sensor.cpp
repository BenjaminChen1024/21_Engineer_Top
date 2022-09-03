/**
  ******************************************************************************
  * @file   : Service_Sensor.cpp
  * @brief  : ���񴫸����ļ�
  ******************************************************************************
  * @note
  *  - 
**/
/* Includes ------------------------------------------------------------------*/
#include "Service_Sensor.h"
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------*/

void Sensor_Classdef::PR_Updata()
{
	PR_F1_Status = PR_F1();
	PR_F2_Status = PR_F2();
	PR_F3_Status = PR_F3();
	PR_F4_Status = PR_F4();
	PR_F5_Status = PR_F5();
	PR_F6_Status = PR_F6();
	PR_F7_Status = PR_F7();
	PR_F8_Status = PR_F8();
}

void Sensor_Classdef::PR_RESET()
{
	PR_F1_Status = OFF;
	PR_F2_Status = OFF;
	PR_F3_Status = OFF;
	PR_F4_Status = OFF;
	PR_F5_Status = OFF;
	PR_F6_Status = OFF;
	PR_F7_Status = OFF;
	PR_F8_Status = OFF;

}

/**
* @brief  PR-F������1���������¹���ţ�.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F1()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F1_Port,PR_F1_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}

/**
* @brief  PR-F������2���������¹���ţ�.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F2()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F2_Port,PR_F2_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}

/**
* @brief  PR-F������3��������.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F3()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F3_Port,PR_F3_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}

/**
* @brief  PR-F������4��������.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F4()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F4_Port,PR_F4_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}

/**
* @brief  PR-F������5������ʶ�����ţ�.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F5()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F5_Port,PR_F5_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}

/**
* @brief  PR-F������6��������.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F6()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F6_Port,PR_F6_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}

/**
* @brief  PR-F������7��������.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F7()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F7_Port,PR_F7_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}

/**
* @brief  PR-F������8��������.
* @param  void.
* @return SensorStatusTypedef	������״̬.
* @note  	ON�����ڹ⡢OFF����δ�ڹ�.
*/
SensorStatusTypedef Sensor_Classdef::PR_F8()
{
	uint8_t Status = HAL_GPIO_ReadPin(PR_F8_Port,PR_F8_Pin);
	switch(Status)
	{
		case 0:
			return ON;
		case 1:
			return OFF;
		default:
			return OFF;
	}
}
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
