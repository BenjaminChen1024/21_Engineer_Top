/**
  ******************************************************************************
  * @file   : Service_Relay.h
  * @brief  : Service_Relay.cppͷ�ļ�
  ****************************************************************************** 
**/
#ifndef _SERVICE_RELAY_H_
#define _SERVICE_RELAY_H_

#ifdef __cplusplus

	extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* Private defines ------------------------------------------------------------*/

/* ��ʯ����GPIO --------------*/
#define  Relay_Pinch_Port      			GPIOC
#define  Relay_Pinch_Pin      		  GPIO_PIN_5
/* ��ͨ��ԮGPIO --------------*/
#define  Relay_Rescue_Port  		    GPIOB
#define  Relay_Rescue_Pin    		 	  GPIO_PIN_0
/* �汦��ԮGPIO --------------*/
#define  Relay_SuperRescue_Port     GPIOB
#define  Relay_SuperRescue_Pin      GPIO_PIN_1
/* ˢ��GPIO --------------*/
#define  Relay_ETC_Port   				  GPIOC
#define  Relay_ECT_Pin    	 			  GPIO_PIN_4
		
/* Private variables ---------------------------------------------------------*/
/* �̵�������״̬ --------------*/
enum RelaySetStatusTypeDef
{
	Relay_Off,
	Relay_On,
};
/* �̵���״̬ --------------*/

/* Private function declarations ---------------------------------------------*/

class Relay_Classdef
{
	public:
    RelaySetStatusTypeDef Pinch_Status;
    RelaySetStatusTypeDef Rescue_Status;
    RelaySetStatusTypeDef SuperRescue_Status;
	  RelaySetStatusTypeDef ETC_Status;
	
		void Relay_Init();
		void Relay_Open();
		void Relay_Reset();
		void Pinch();
		void Loosen();
		void Rescue();
		void Rescue_Back();
		void SuperRescue();
		void SuperRescue_Back();
		void ETC();
		void ETC_Back();
};

uint8_t Relay_Delay(float);

#ifdef __cplusplus
}
#endif

#endif
