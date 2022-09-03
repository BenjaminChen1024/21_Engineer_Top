/**
  ******************************************************************************
  * @file   : Service_Auto.h
  * @brief  : Service_Auto.cpp头文件
  ****************************************************************************** 
**/
#ifndef _SERVICE_AUTO_H
#define _SERVICE_AUTO_H
/* Includes ------------------------------------------------------------------*/
#include "System_Datapool.h"

/* Private defines ------------------------------------------------------------*/

/* 上层自动状态仪 --------------*/
#define Auto_TakeSmallBox_Status				Auto_Status[0]
#define Auto_RobBigBox_Status						Auto_Status[1]
#define Auto_ExchangeBox_Status					Auto_Status[2]
#define Auto_REBigBox_Status						Auto_Status[3]
#define Auto_TakeGroundBox_Status				Auto_Status[4]
#define Auto_ExchangeAgain_Status					Auto_Status[5]
/* 上层中断状态仪 --------------*/
#define TakeSmallBox_Interrupt_Action				Interrupt_Action[0]
#define RobBigBox_Interrupt_Action					Interrupt_Action[1]
#define ExchangeBox_Interrupt_Action				Interrupt_Action[2]
#define REBigBox_Interrupt_Action						Interrupt_Action[3]
#define TakeGroundBox_Interrupt_Action			Interrupt_Action[4]
#define ExchangeAgain_Interrupt_Action			Interrupt_Action[5]

/* Private variables ---------------------------------------------------------*/

/* 上层所有状态 --------------*/
enum TopStatusTypedef
{
	Waiting,
	Interrupt,
	InterruptReturn,
	Delay,
	StartAction,
	StageLift,StageLift1,StageLift2,
	TakeBoxLift,
	ExchangeBoxLift,
	VisionBoxLift,
	MeetBoxLift,MeetBoxLift1,MeetBoxLift2,
	Rotate,
	RotateTop,RotateTop1,RotateTop2,RotateTop3,
	RotateTopper,
	RotateHor,
	RotateBack,
	Extend,Extend1,Extend2,
	ExtendBack,ExtendBack1,ExtendBack2,
	IdentifyBox,
	TurnHor,
	TurnQR,
	TurnAdjust,
	PinchBox,PinchBox1,PinchBox2,
	PinchProtect,
	LoosenBox,LoosenBox1,LoosenBox2,
	RotateReset,
	PitchReset,
};

/* Private Class declarations ---------------------------------------------*/
class Auto_Classdef
{
	private:
		/* 上层自动状态仪 --------------*/
		TopStatusTypedef Auto_Status[6];
		/* 上层中断状态仪 --------------*/
		TopStatusTypedef Interrupt_Action[6];
	
		void Auto_RobBigBox();				//自动抢大矿函数（）
		void Auto_REBigBox();				//自动抢大矿函数（）
		void Auto_TakeSmallBox();				//自动取小矿函数（）
		void Auto_TakeGroundBox();				//自动取地面函数（）
		void Auto_ExchangeBox();				//自动兑换函数（）
		void Auto_ExchangeAgain();				//再次兑换函数（）
	
	public:
		void Auto_Task();				//自动组任务执行函数（）
		void Auto_Interrupt();				//自动组中断函数（）
		void Auto_Reset();				//自动组复位函数（）
		/* 自动组开始函数 --------------*/
		void Auto_RobBigBox_Start();
		void Auto_REBigBox_Start();
		void Auto_TakeSmallBox_Start();
		void Auto_TakeGroundBox_Start();
		void Auto_ExchangeBox_Start();
		void Auto_ExchangeAgain_Start();

		/* 自动组半进入函数 --------------*/
	  void Auto_ExchangeBox_Middle();
		/* 自动组判断函数 --------------*/
		uint8_t Auto_Status_Judge();				//自动组状态判断函数（）
		bool Auto_Waiting_Judge();				//自动组等待判断函数（）
};
#endif
