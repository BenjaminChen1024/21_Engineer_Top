/**
  ******************************************************************************
  * @file   : System_Datapool.h
  * @brief  : System_Datapool.cppͷ�ļ�
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

/* �����ջ��� --------------*/
#define Tiny_Stack_Size 64
#define Small_Stack_Size 128
#define Normal_Stack_Size 256
#define Large_Stack_Size 512
#define Huge_Stack_Size 1024
/* �������ȼ� --------------*/
#define PriorityVeryLow 1
#define PriorityLow 2
#define PriorityBelowNormal 3
#define PriorityNormal 4
#define PriorityAboveNormal 5
#define PriorityHigh 6
#define PriorityVeryHigh 7
/* ���ڽ��������С --------------*/
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
/* DR16�� --------------*/
extern DR16_Classdef Engineer_DR16;
extern Sensor_Classdef Engineer_Sensor;
extern Relay_Classdef Engineer_Relay;
extern Motor_Classdef Engineer_Motor;
extern Auto_Classdef Engineer_Auto;
extern Action_Classdef Engineer_Action;
extern Box_Classdef Engineer_Box;
/* ���ڽ������� --------------*/
extern uint8_t Uart1_Rx_Buff[USART1_RX_BUFFER_SIZE];
extern uint8_t Uart2_Rx_Buff[USART2_RX_BUFFER_SIZE];
extern uint8_t Uart3_Rx_Buff[USART3_RX_BUFFER_SIZE];
extern uint8_t Uart4_Rx_Buff[USART4_RX_BUFFER_SIZE];
extern uint8_t Uart6_Rx_Buff[USART6_RX_BUFFER_SIZE];
/* ��ʯ���� --------------*/
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

/* ��ʱ����� --------------*/
extern TIM_HandleTypeDef htim4;
/* ���ھ�� --------------*/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart6;
/* CAN��� --------------*/
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
/* ��Ϣ���о�� --------------*/
extern QueueHandle_t DR16_RX_QueueHandle;
extern QueueHandle_t Vision_RX_QueueHandle;
extern QueueHandle_t Key_RX_QueueHandle;
extern QueueHandle_t UI_TX_QueueHandle;

extern TaskHandle_t TopPOST_Handle;


/* Private class declarations ---------------------------------------------*/

class Box_Classdef
{
	private:
		uint8_t Box_Num_Flag = Engineer_Sensor.PR_F5_Status;				//��ʯ������־λ
		uint64_t	Box_Height;				//��ʯ�߶�
		void Box_Height_Judge();				//��ʯ�߶��жϺ�������
	
	public:
		BoxNumTypedef Box_Num;				//��ʯ����
		void Box_Set();				//��ʯ��־λ����������
		void Box_Reset();				//��ʯ��־λͬ��������
		uint8_t Box_Num_Judge();				//��ʯ�����жϺ�������


};


/* Private function prototypes -------------------------------------------------------*/

/* ��λģ�庯�� --------------*/
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
