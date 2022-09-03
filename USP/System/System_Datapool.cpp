/**
  ******************************************************************************
  * @file   : System_Datapool.cpp
  * @brief  : 包含所有用户资源（变量、函数）
  ******************************************************************************
  * @note
  *  - 
**/
/* Includes ------------------------------------------------------------------*/
#include "System_Datapool.h"
#include "System_Config.h"
/* Private variables ---------------------------------------------------------*/

/* DR16类 --------------*/
DR16_Classdef Engineer_DR16;
Sensor_Classdef Engineer_Sensor;
Relay_Classdef Engineer_Relay;
Motor_Classdef Engineer_Motor;
Auto_Classdef Engineer_Auto;
Action_Classdef Engineer_Action;
Box_Classdef Engineer_Box;
/* 串口接收数组 --------------*/
uint8_t Uart1_Rx_Buff[USART1_RX_BUFFER_SIZE];
uint8_t Uart2_Rx_Buff[USART2_RX_BUFFER_SIZE];
uint8_t Uart3_Rx_Buff[USART3_RX_BUFFER_SIZE];
uint8_t Uart4_Rx_Buff[USART4_RX_BUFFER_SIZE];
uint8_t Uart6_Rx_Buff[USART6_RX_BUFFER_SIZE];
/* HAL Handlers --------------------------------------------------------------*/
QueueHandle_t DR16_RX_QueueHandle;
QueueHandle_t Vision_RX_QueueHandle;
QueueHandle_t Key_RX_QueueHandle;
QueueHandle_t UI_TX_QueueHandle;

bool SystemReset_flag;
bool TopPOST_flag;

/* Private function prototypes -------------------------------------------------------*/

/* 矿石标志位反向函数 --------------*/
void Box_Classdef::Box_Set()
{
	Box_Num_Flag = !Engineer_Sensor.PR_F5_Status;
}
/* 矿石标志位通向函数 --------------*/
void Box_Classdef::Box_Reset()
{
	Box_Num_Flag = Engineer_Sensor.PR_F5_Status;
}
/* 矿石数量判断函数 --------------*/
uint8_t Box_Classdef::Box_Num_Judge()
{
	if(Box_Num_Flag != Engineer_Sensor.PR_F5_Status)
	{
		Box_Height = LeftLift_PosPID.Current;
		Box_Height_Judge();
		Box_Num_Flag = Engineer_Sensor.PR_F5_Status;
		return 2;
	}
	else
	{
		if(Box_Num_Flag == 0)
		{
			if(Engineer_Motor.Lift_Motor.Lift_None_Judge())
			{
				Box_Height = LeftLift_PosPID.Current;
				Box_Height_Judge();
				Box_Num_Flag = Engineer_Sensor.PR_F5_Status;
				return 2;
			}
			return 0;
		}
		else
		{
			if(Engineer_Motor.Lift_Motor.Lift_Third_Judge())
			{
				Box_Height = LeftLift_PosPID.Current;
				Box_Height_Judge();
				Box_Num_Flag = Engineer_Sensor.PR_F5_Status;
				return 2;
			}
			return 1;
		}
	}
}
/* 矿石高度判断函数 --------------*/
void Box_Classdef::Box_Height_Judge()
{	
	if(Box_Height <= 186000)
	{
		Box_Num = None_Box;
	}
	if(Box_Height > 186000 && Box_Height < 186000 + 400000)
	{
		Box_Num = One_Box;
	}
	if(Box_Height >= 186000 + 400000)
	{
		Box_Num = Two_Box;
	}
}

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
