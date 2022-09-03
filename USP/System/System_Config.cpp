/**
  ******************************************************************************
  * @file   System_Config.cpp
  * @brief  创建初始化配置、通信回调函数
  ******************************************************************************
  * @note
  *  - 
**/
/* Includes ------------------------------------------------------------------*/
#include "System_Config.h"
#include "System_Datapool.h"
/* Private function declarations ---------------------------------------------*/
uint32_t User_UART1_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen);
uint32_t User_UART2_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen);
uint32_t User_UART3_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen);
uint32_t User_UART4_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen);
uint32_t User_UART6_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen);



void User_CAN1_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage);
void User_CAN2_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage);

uint8_t temp_msg[26];


/* Private Function prototypes -------------------------------------------------------*/

/**
* @brief  系统资源初始化函数.
* @param  void.
* @return void.
* @note  	None.
*/
void System_Resource_Init(void)
{
	/* 计时器初始化 --------------*/
	Timer_Init(&htim4,USE_HAL_DELAY);
	/* 串口初始化 --------------*/
  Uart_Init(&huart1, Uart1_Rx_Buff, USART1_RX_BUFFER_SIZE, User_UART1_RxCpltCallback);
  Uart_Init(&huart2, Uart2_Rx_Buff, USART2_RX_BUFFER_SIZE, User_UART2_RxCpltCallback);
  Uart_Init(&huart3, Uart3_Rx_Buff, USART3_RX_BUFFER_SIZE, User_UART3_RxCpltCallback);
  Uart_Init(&huart4, Uart4_Rx_Buff, USART4_RX_BUFFER_SIZE, User_UART4_RxCpltCallback);
  Uart_Init(&huart6, Uart6_Rx_Buff, USART6_RX_BUFFER_SIZE, User_UART6_RxCpltCallback);

	/* CAN初始化 --------------*/
  CAN_Init(&hcan1, User_CAN1_RxCpltCallback);
  CAN_Init(&hcan2, User_CAN2_RxCpltCallback);
	/* CAN过滤器初始化 --------------*/
	
	CAN_Filter_Mask_Config(&hcan1,CanFilter_0|CanFifo_0|Can_STDID|Can_DataType,0x100,0x3ff);
	CAN_Filter_Mask_Config(&hcan1,CanFilter_1|CanFifo_0|Can_STDID|Can_DataType,0x101,0x3ff);
	CAN_Filter_Mask_Config(&hcan1,CanFilter_2|CanFifo_0|Can_STDID|Can_DataType,0x102,0x3ff);

	
//	CAN_Filter_Mask_Config(&hcan1,CanFilter_0|CanFifo_0|Can_STDID|Can_DataType,LeftExtendMotor_ID,0x3ff);
//	CAN_Filter_Mask_Config(&hcan1,CanFilter_1|CanFifo_0|Can_STDID|Can_DataType,RightExtendMotor_ID,0x3ff);
//	CAN_Filter_Mask_Config(&hcan1,CanFilter_2|CanFifo_0|Can_STDID|Can_DataType,LeftRotateMotor_ID,0x3ff);
//	CAN_Filter_Mask_Config(&hcan1,CanFilter_3|CanFifo_0|Can_STDID|Can_DataType,RightRotateMotor_ID,0x3ff);
//	CAN_Filter_Mask_Config(&hcan1,CanFilter_4|CanFifo_0|Can_STDID|Can_DataType,TurnMotor_ID,0x3ff);
//	CAN_Filter_Mask_Config(&hcan1,CanFilter_5|CanFifo_0|Can_STDID|Can_DataType,LeftLiftMotor_ID,0x3ff);
//	CAN_Filter_Mask_Config(&hcan1,CanFilter_6|CanFifo_0|Can_STDID|Can_DataType,RightLiftMotor_ID,0x3ff);

	CAN_Filter_Mask_Config(&hcan2,CanFilter_15|CanFifo_0|Can_STDID|Can_DataType,LeftExtendMotor_ID,0x3ff);
	CAN_Filter_Mask_Config(&hcan2,CanFilter_16|CanFifo_0|Can_STDID|Can_DataType,RightExtendMotor_ID,0x3ff);
	CAN_Filter_Mask_Config(&hcan2,CanFilter_17|CanFifo_0|Can_STDID|Can_DataType,LeftRotateMotor_ID,0x3ff);
	CAN_Filter_Mask_Config(&hcan2,CanFilter_18|CanFifo_0|Can_STDID|Can_DataType,RightRotateMotor_ID,0x3ff);
	CAN_Filter_Mask_Config(&hcan2,CanFilter_19|CanFifo_0|Can_STDID|Can_DataType,TurnMotor_ID,0x3ff);
	CAN_Filter_Mask_Config(&hcan2,CanFilter_20|CanFifo_0|Can_STDID|Can_DataType,LeftLiftMotor_ID,0x3ff);
	CAN_Filter_Mask_Config(&hcan2,CanFilter_21|CanFifo_0|Can_STDID|Can_DataType,RightLiftMotor_ID,0x3ff);	
	/* 创建消息队列 --------------*/
  DR16_RX_QueueHandle = xQueueCreate(4, sizeof(DR16_DataPack_Typedef));
  Vision_RX_QueueHandle = xQueueCreate(4, sizeof(Vision_DataPack_Typedef));
  Key_RX_QueueHandle = xQueueCreate(4, sizeof(Key_DataPack_Typedef));
  UI_TX_QueueHandle = xQueueCreate(2, 8 * sizeof(uint8_t));
	/* 电机PID初始化 --------------*/
	Engineer_Motor.MotorPIDInit();
	/* 继电器初始化 --------------*/
	Engineer_Relay.Relay_Init();
}

/*---------------------------------------------- User RxCpltCallback Function --------------------------------------------*/
uint32_t User_UART1_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen)
{
	return 0xFFFFFFFF;
}

uint32_t User_UART2_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen)
{
	return 0xFFFFFFFF;

}

uint32_t User_UART3_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen)
{
	return 0xFFFFFFFF;
}

uint32_t User_UART4_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen)
{
	/* 接收视觉数据 --------------*/
  if (Vision_RX_QueueHandle != NULL)
	{
    return xQueueSendFromISR(Vision_RX_QueueHandle, Recv_Data, NULL);
	}
  else
	{
		return 0xFFFFFFFF ;
	}
}

uint32_t User_UART6_RxCpltCallback(uint8_t *Recv_Data, uint16_t ReceiveLen)
{

	if(Recv_Data[0] == 25 && Recv_Data[25] == 30)
	{
		Update_USART_Board(Recv_Data,1);
		return 0xFFFFFFFF;
	}
	Update_USART_Board(Recv_Data,0);
	return 0xFFFFFFFF;
}

void User_CAN1_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage)
{

}

void User_CAN2_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage)
{
	/* 接收电机数据 --------------*/
	if(((CAN_RxMessage->header.StdId)&0x200) == 0x200)
	{
		uint32_t Motor_ID = CAN_RxMessage->header.StdId;
		Engineer_Motor.Update_Motor(CAN_RxMessage->data, Motor_ID);
	}
}
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
