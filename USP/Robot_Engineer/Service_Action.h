/**
  ******************************************************************************
  * @file   : Service_Action.h
  * @brief  : Service_Action.cpp头文件
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

/* 所有动作组类型 --------------*/
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
		/* 开机自检次数 --------------*/
		uint8_t Rotate_POST_Num;
		uint64_t POST_Num;
	public:
		/* 动作组 --------------*/
		ActionGroupTypedef ActionGroup[5];
		/* 动作组控制函数 --------------*/
		void Do_Action();				//动作组执行函数（）
		void Action_POST();				//动作组开机自检函数（）
		void Action_Init_All();				//动作组全初始化函数（）
		void Action_Init_Part();				//动作组半初始化函数（）
		void Action_Reset();				//动作组复位函数（）
		void Action_Protect_ALL();				//动作组全保护函数（）
		void Action_Protect_Part();				//动作组半保护函数（）
		/* 独立动作组函数 --------------*/
		void	Do_Rotate_Action();				//翻转动作组函数（）
		void	Do_Extend_Action();				//伸出动作组函数（）
		void	Do_Lift_Action();				//抬升动作组函数（）
		void	Do_Turn_Action();				//旋转动作组函数（）
		void Do_Pinch_Action();				//夹取函数（）
		void Do_Rescue_Action();				//救援函数（）
		void Do_SuperRescue_Action();				//舵宝救援函数（）
		void Do_ETC_Action();				//刷卡函数（）
};

#endif
