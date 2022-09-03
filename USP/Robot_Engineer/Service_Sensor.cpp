/**
  ******************************************************************************
  * @file   : Service_Sensor.cpp
  * @brief  : 服务传感器文件
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
* @brief  PR-F传感器1函数（左下光电门）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
* @brief  PR-F传感器2函数（右下光电门）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
* @brief  PR-F传感器3函数（）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
* @brief  PR-F传感器4函数（）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
* @brief  PR-F传感器5函数（识矿光电门）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
* @brief  PR-F传感器6函数（）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
* @brief  PR-F传感器7函数（）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
* @brief  PR-F传感器8函数（）.
* @param  void.
* @return SensorStatusTypedef	传感器状态.
* @note  	ON代表遮光、OFF代表未遮光.
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
