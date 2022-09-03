/**
  ******************************************************************************
  * @file   : System_Tasks.cpp
  * @brief  : 创建任务.
  ******************************************************************************
  * @note
  *  - 
**/

/* Includes ------------------------------------------------------------------*/
#include "System_Tasks.h"
#include "System_Datapool.h"
/* TaskHandle_t --------------------------------------------------------------*/
TaskHandle_t TopPOST_Handle;
TaskHandle_t TopCom_Handle;
TaskHandle_t ActionCtrl_Handle;
TaskHandle_t BoardCom_Handle;
TaskHandle_t ModeSelection_Handle;
TaskHandle_t OfflineCtrl_Handle;
//TaskHandle_t DebugSent_Handle;
TaskHandle_t SystemReset_Handle;
/* Private function declarations ---------------------------------------------*/
void Top_POST(void *arg);
void Top_Com(void *arg);
void Action_Ctrl(void *arg);
void Board_Com(void *arg);
void Mode_Selection(void*arg);
void Offline_Ctrl(void*arg);
//void Debug_Sent(void*arg);
void System_Reset(void*arg);
/* Task Function prototypes --------------------------------------------------*/

/**
* @brief  任务初始化函数.
* @param  void.
* @return void.
* @note  	注意不要任务重名（不报错，时序会乱）.

*/
void System_Tasks_Init(void)
{
  vTaskSuspendAll();
	
	xTaskCreate(Top_POST,"Top_POST",Normal_Stack_Size,NULL,PriorityVeryHigh,&TopPOST_Handle);	
	xTaskCreate(Top_Com,"Top_Com",Normal_Stack_Size,NULL,PriorityAboveNormal,&TopCom_Handle);	
	xTaskCreate(Action_Ctrl,"Action_Ctrl",Normal_Stack_Size,NULL,PriorityAboveNormal,&ActionCtrl_Handle);
	xTaskCreate(Board_Com,"Board_Com",Normal_Stack_Size,NULL,PriorityHigh,&BoardCom_Handle);	
	xTaskCreate(Mode_Selection,"Mode_Selection",Normal_Stack_Size,NULL,PriorityAboveNormal,&ModeSelection_Handle);
	xTaskCreate(Offline_Ctrl,"Offline_Ctrl",Normal_Stack_Size,NULL,PriorityAboveNormal,&OfflineCtrl_Handle);
//	xTaskCreate(Debug_Sent,"Debug_Sent",Small_Stack_Size,NULL,PriorityNormal,&DebugSent_Handle);
	xTaskCreate(System_Reset,"System_Reset",Small_Stack_Size,NULL,PriorityAboveNormal,&SystemReset_Handle);
	
  if (!xTaskResumeAll())
    taskYIELD();
}

/**
* @brief  开机自检函数.
* @param  void.
* @return void.
* @note  	None.
*/
void Top_POST(void*arg)
{
  static TickType_t _xTicksToWait = pdMS_TO_TICKS(1);
	static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(1);
	for (;;)
  {
    if (xTaskNotifyWait(0x00000000, 0xFFFFFFFF, NULL, _xTicksToWait) == pdTRUE)
		{
			Engineer_Motor.Lift_Motor.Lift_POST_Reset();
    }
		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
	}
}

/**
* @brief  上层通信函数.
* @param  void.
* @return void.
* @note  	向上层设备进行通信（电机/传感器）.
*/
void Top_Com(void *arg)
{
  static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(1);
  for (;;)
  {
		Engineer_Sensor.PR_Updata();
		Engineer_Motor.Motor_Control();
		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
  }
}
/**
* @brief  动作控制函数.
* @param  void.
* @return void.
* @note  	None.
*/
void Action_Ctrl(void*arg)
{  
	static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(1);
  for (;;)
  {
		Engineer_Auto.Auto_Task();
		Engineer_Action.Do_Action();
		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
  }
}

uint8_t test_TX[8];
uint64_t test_Num;
/**
* @brief  板间通信函数.
* @param  void.
* @return void.
* @note  	与底层主控板进行通信.
*/
void Board_Com(void *arg)
{
  static TickType_t _xTicksToWait = pdMS_TO_TICKS(5);
  static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(5);
	uint8_t UI_Tx_Data[8];
  for (;;)
  {
		UIMsgSend();
    if (xQueueReceive(UI_TX_QueueHandle, UI_Tx_Data, _xTicksToWait) == pdTRUE)
		{
			if(test_Num <= 3000)
			{
				if(CANx_SendData(&hcan1,0x100,UI_Tx_Data,sizeof(UI_Tx_Data)) != CAN_SUCCESS)
				{
					test_Num++;
					Engineer_Motor.Turn_Motor.Turn_close_flag = 0;
				}
				else
				{
					Engineer_Motor.Turn_Motor.Turn_close_flag = 1;
					test_Num = 0;
				}
			}
			else
			{
				if(test_Num <= 5000)
				{
					Engineer_Motor.Turn_Motor.Turn_close_flag = 0;
					test_Num++;
				}
				else
				{
					test_Num = 0;
				}
			}
			memcpy(test_TX,UI_Tx_Data,sizeof(UI_Tx_Data));
		}
		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
  }
}

/**
* @brief  模式切换函数.
* @param  void.
* @return void.
* @note  	根据DR16开关切换不同模式.
*/
void Mode_Selection(void*arg)
{
	static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(1);
  for (;;)
  {		
		
    if (Key_DataPack.DR16_Status == 0)
		{
			xTaskNotify(OfflineCtrl_Handle, (uint32_t)NULL, eNoAction);
		}
    else
    {
			if(Key_DataPack.DR16_S2 == 1)
			{
				Protect_Key_Control();
			}
			else
			{
//				if(Engineer_Motor.Lift_Motor.Life_Balance_Protect())
//				{
					Key_Control();
//				}
//				else
//				{
//					Engineer_Action.Action_Protect_Part();
//				}
			}
		}
		
		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
	}
}


uint8_t flag;
/**
* @brief  掉线保护函数.
* @param  void.
* @return void.
* @note  	暂时没用，先保留接口.
*/
void Offline_Ctrl(void*arg)
{
  static TickType_t _xTicksToWait = pdMS_TO_TICKS(1);
	static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(1);
	
  for (;;)
  {
    if (xTaskNotifyWait(0x00000000, 0xFFFFFFFF, NULL, _xTicksToWait) == pdTRUE)
		{
			Engineer_Action.Action_Protect_ALL();
    }
		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
  }
}

/**
* @brief  上位机发送函数.
* @param  void.
* @return void.
* @note  	None.
*/
//void Debug_Sent(void*arg)
//{
//	static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
//  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(10);
//	for (;;)
//  {
//		Sent_Contorl(&huart1);
//		Sent_Contorl(&huart3);
//		Sent_Contorl(&huart6);
////		UIMsgSend(&huart1);
////		UIMsgSend(&huart6);
////		UIMsgSend(&huart6);
//		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
//	}
//}

/**
* @brief  系统复位函数.
* @param  void.
* @return void.
* @note  	None.
*/
void System_Reset(void*arg)
{
	static TickType_t _xPreviousWakeTime = xTaskGetTickCount();
  static TickType_t _xTimeIncrement = pdMS_TO_TICKS(1);
	static uint32_t delay_time;
	for (;;)
  {
		if(SystemReset_flag == 1)
		{
			Engineer_Action.Action_Protect_ALL();
			delay_time++;
			if(delay_time == 1000)
			{
				__set_FAULTMASK(1);
				HAL_NVIC_SystemReset();
				delay_time = 0;
				SystemReset_flag = 0;
			}
		}
		vTaskDelayUntil(&_xPreviousWakeTime, _xTimeIncrement);
	}
}

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
