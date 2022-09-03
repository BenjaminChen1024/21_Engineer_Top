/**
  ******************************************************************************
  * @file   : Service_Action.h
  * @brief  : Service_Action.cppͷ�ļ�
  ****************************************************************************** 
**/
#ifndef _SERVICE_ACTION_H
#define _SERVICE_ACTION_H
/* Includes ------------------------------------------------------------------*/
#include "System_Datapool.h"
/* Private defines ------------------------------------------------------------*/
#define Rotate_ActionGroup		ActionGroup[0]
#define Extend_ActionGroup		ActionGroup[1]
#define Lift_ActionGroup			ActionGroup[2]
#define Turn_ActionGroup			ActionGroup[3]

/* Private variables ---------------------------------------------------------*/

/* ���ж��������� --------------*/
enum ActionGroupTypedef
{
	None_Action,
	/* Rotate --------------*/
	Rotate_POST_Action,
	Rotate_Back_Start_Action,
	Rotate_Top_Action,
	Rotate_Exchange_Action,
	Rotate_Hor_Action,
	Rotate_Limit_Action,
	/* Extend --------------*/
	Extend_POST_Action,
	None_Extension_Action,
	Mini_Extension_Action,
	First_Stage_Extension_Action,
	Second_Stage_Extension_Action,
	/* Lift --------------*/
	None_Lift_Action,
	Lift_POST_Action,
	First_Stage_Lift_Action,
	Second_Stage_Lift_Action,
	Third_Stage_Lift_Action,
	Test_jl_Lift_Action,
	Take_BigBox_Lift_Action,
	Take_SmallBox_Lift_Action,
	Exchange_Box_Lift_Action,
	Meet_Box_Lift_Action,
	Vision_Lift_Action,
	/* Turn --------------*/
	Turn_to_QR_Action,
};

/* Private function declarations ---------------------------------------------*/
class Action_Classdef
{
	private:
		/* �����Լ���� --------------*/
		uint8_t Rotate_POST_Num;
		uint64_t POST_Num;
	public:
		/* ������ --------------*/
		ActionGroupTypedef ActionGroup[5];
		/* ��������ƺ��� --------------*/
		void Do_Action();				//������ִ�к�������
		void Action_POST();				//�����鿪���Լ캯������
		void Action_Init_All();				//������ȫ��ʼ����������
		void Action_Init_Part();				//��������ʼ����������
		void Action_Reset();				//�����鸴λ��������
		void Action_Protect_ALL();				//������ȫ������������
		void Action_Protect_Part();				//������뱣����������
		/* ���������麯�� --------------*/
		void	Do_Rotate_Action();				//��ת�����麯������
		void	Do_Extend_Action();				//��������麯������
		void	Do_Lift_Action();				//̧�������麯������
		void	Do_Turn_Action();				//��ת�����麯������
		void Do_Pinch_Action();				//��ȡ��������
		void Do_Rescue_Action();				//��Ԯ��������
		void Do_SuperRescue_Action();				//�汦��Ԯ��������
		void Do_ETC_Action();				//ˢ����������
};

#endif
