/**
  ******************************************************************************
  * @file   : System_Datapool.h
  * @brief  : System_Datapool.cpp头文件
  ****************************************************************************** 
**/
#ifndef _SYSTEM_DATAPOOL_H_
#define _SYSTEM_DATAPOOL_H_
/* Includes ------------------------------------------------------------------*/
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include <SRML.h>
#include "UpperMonitor.h"
#include "Service_Relay.h"
#include "Service_Motor.h"
#include "Service_Sensor.h"
#include "Service_Communication.h"
#include "Service_Auto.h"
#include "Service_Action.h"
/* Private define ------------------------------------------------------------*/

/* 任务堆栈深度 --------------*/
#define Tiny_Stack_Size 64
#define Small_Stack_Size 128
#define Normal_Stack_Size 256
#define Large_Stack_Size 512
#define Huge_Stack_Size 1024
/* 任务优先级 --------------*/
#define PriorityVeryLow 1
#define PriorityLow 2
#define PriorityBelowNormal 3
#define PriorityNormal 4
#define PriorityAboveNormal 5
#define PriorityHigh 6
#define PriorityVeryHigh 7
/* 串口接收数组大小 --------------*/
#define USART1_RX_BUFFER_SIZE 64
#define USART2_RX_BUFFER_SIZE 64
#define USART3_RX_BUFFER_SIZE 64
#define USART4_RX_BUFFER_SIZE 64
#define USART6_RX_BUFFER_SIZE 64


/* Private variables ---------------------------------------------------------*/
class Motor_Classdef;
class Auto_Classdef;
class Action_Classdef;
class Box_Classdef;
/* DR16类 --------------*/
extern DR16_Classdef Engineer_DR16;
extern Sensor_Classdef Engineer_Sensor;
extern Relay_Classdef Engineer_Relay;
extern Motor_Classdef Engineer_Motor;
extern Auto_Classdef Engineer_Auto;
extern Action_Classdef Engineer_Action;
extern Box_Classdef Engineer_Box;
/* 串口接收数组 --------------*/
extern uint8_t Uart1_Rx_Buff[USART1_RX_BUFFER_SIZE];
extern uint8_t Uart2_Rx_Buff[USART2_RX_BUFFER_SIZE];
extern uint8_t Uart3_Rx_Buff[USART3_RX_BUFFER_SIZE];
extern uint8_t Uart4_Rx_Buff[USART4_RX_BUFFER_SIZE];
extern uint8_t Uart6_Rx_Buff[USART6_RX_BUFFER_SIZE];
/* 矿石数量 --------------*/
enum BoxNumTypedef
{
	None_Box,
	One_Box,
	Two_Box,
	Three_Box,
	Four_Box,
};

extern bool SystemReset_flag;
extern bool TopPOST_flag;

/* HAL Handlers --------------------------------------------------------------*/

/* 计时器句柄 --------------*/
extern TIM_HandleTypeDef htim4;
/* 串口句柄 --------------*/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart6;
/* CAN句柄 --------------*/
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
/* 消息队列句柄 --------------*/
extern QueueHandle_t DR16_RX_QueueHandle;
extern QueueHandle_t Vision_RX_QueueHandle;
extern QueueHandle_t Key_RX_QueueHandle;
extern QueueHandle_t UI_TX_QueueHandle;

extern TaskHandle_t TopPOST_Handle;


/* Private class declarations ---------------------------------------------*/

class Box_Classdef
{
	private:
		uint8_t Box_Num_Flag = Engineer_Sensor.PR_F5_Status;				//矿石数量标志位
		uint64_t	Box_Height;				//矿石高度
		void Box_Height_Judge();				//矿石高度判断函数（）
	
	public:
		BoxNumTypedef Box_Num;				//矿石数量
		void Box_Set();				//矿石标志位反向函数（）
		void Box_Reset();				//矿石标志位同向函数（）
		uint8_t Box_Num_Judge();				//矿石数量判断函数（）


};


/* Private function prototypes -------------------------------------------------------*/

/* 限位模板函数 --------------*/
template<typename Type>
Type myConstrain(Type input, Type min, Type max)
{
  if (input <= min)
    return min;
  else if (input >= max)
    return max;
  else
    return input;
}


#endif
