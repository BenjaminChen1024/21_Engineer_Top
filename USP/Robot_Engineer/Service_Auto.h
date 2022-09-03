/**
  ******************************************************************************
  * @file   : Service_Auto.h
  * @brief  : Service_Auto.cppͷ�ļ�
  ****************************************************************************** 
**/
#ifndef _SERVICE_AUTO_H
#define _SERVICE_AUTO_H
/* Includes ------------------------------------------------------------------*/
#include "System_Datapool.h"

/* Private defines ------------------------------------------------------------*/

/* �ϲ��Զ�״̬�� --------------*/
#define Auto_TakeSmallBox_Status				Auto_Status[0]
#define Auto_RobBigBox_Status						Auto_Status[1]
#define Auto_ExchangeBox_Status					Auto_Status[2]
#define Auto_REBigBox_Status						Auto_Status[3]
#define Auto_TakeGroundBox_Status				Auto_Status[4]
#define Auto_ExchangeAgain_Status					Auto_Status[5]
/* �ϲ��ж�״̬�� --------------*/
#define TakeSmallBox_Interrupt_Action				Interrupt_Action[0]
#define RobBigBox_Interrupt_Action					Interrupt_Action[1]
#define ExchangeBox_Interrupt_Action				Interrupt_Action[2]
#define REBigBox_Interrupt_Action						Interrupt_Action[3]
#define TakeGroundBox_Interrupt_Action			Interrupt_Action[4]
#define ExchangeAgain_Interrupt_Action			Interrupt_Action[5]

/* Private variables ---------------------------------------------------------*/

/* �ϲ�����״̬ --------------*/
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
		/* �ϲ��Զ�״̬�� --------------*/
		TopStatusTypedef Auto_Status[6];
		/* �ϲ��ж�״̬�� --------------*/
		TopStatusTypedef Interrupt_Action[6];
	
		void Auto_RobBigBox();				//�Զ������������
		void Auto_REBigBox();				//�Զ������������
		void Auto_TakeSmallBox();				//�Զ�ȡС��������
		void Auto_TakeGroundBox();				//�Զ�ȡ���溯������
		void Auto_ExchangeBox();				//�Զ��һ���������
		void Auto_ExchangeAgain();				//�ٴζһ���������
	
	public:
		void Auto_Task();				//�Զ�������ִ�к�������
		void Auto_Interrupt();				//�Զ����жϺ�������
		void Auto_Reset();				//�Զ��鸴λ��������
		/* �Զ��鿪ʼ���� --------------*/
		void Auto_RobBigBox_Start();
		void Auto_REBigBox_Start();
		void Auto_TakeSmallBox_Start();
		void Auto_TakeGroundBox_Start();
		void Auto_ExchangeBox_Start();
		void Auto_ExchangeAgain_Start();

		/* �Զ������뺯�� --------------*/
	  void Auto_ExchangeBox_Middle();
		/* �Զ����жϺ��� --------------*/
		uint8_t Auto_Status_Judge();				//�Զ���״̬�жϺ�������
		bool Auto_Waiting_Judge();				//�Զ���ȴ��жϺ�������
};
#endif
