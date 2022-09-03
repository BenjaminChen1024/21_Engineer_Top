/**
  ******************************************************************************
  * @file   : Service_Action.cpp
  * @brief  : 服务动作组文件
  ******************************************************************************
  * @note
  *  - 
**/
/* Includes ------------------------------------------------------------------*/
#include "Service_Action.h"
/* Private function prototypes -------------------------------------------------------*/

/*---------------------------------------------- Universal Action Function --------------------------------------------*/

/* 动作组执行函数 --------------*/
void Action_Classdef::Do_Action()
{
	Do_Rotate_Action();
	Do_Extend_Action();
	Do_Lift_Action();
	Do_Turn_Action();
}
/* 动作组开机自检函数 --------------*/
void Action_Classdef::Action_POST()
{
	if(POST_Num < 8000)
	{
		if( POST_Num < 1000)
		{
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			Engineer_Motor.Turn_Motor.Turn_Death();
			Rotate_ActionGroup = Rotate_POST_Action;
			Extend_ActionGroup = Extend_POST_Action;
			Engineer_Relay.Relay_Init();
		}
		if(POST_Num == 1000)
		{
			Extend_ActionGroup = None_Extension_Action;
			Rotate_ActionGroup = Rotate_Back_Start_Action;
		}
		Lift_ActionGroup = Lift_POST_Action;
		POST_Num++;
	}
	else if(POST_Num == 8000)
	{
		Action_Reset();
		POST_Num++;
	}
}
/* 动作组全初始化函数 --------------*/
void Action_Classdef::Action_Init_All()
{
	Engineer_Motor.Turn_Motor.Turn_QR = 0;
	Action_Reset();
	Engineer_Auto.Auto_Reset();
	Engineer_Motor.Turn_Motor.Turn_Death();
	Rotate_ActionGroup = Rotate_Back_Start_Action;
	Extend_ActionGroup = None_Extension_Action;
	Lift_ActionGroup = None_Lift_Action;
	Engineer_Relay.Relay_Init();
}
/* 动作组半初始化函数 --------------*/
void Action_Classdef::Action_Init_Part()
{
	if(Engineer_Auto.Auto_Waiting_Judge())
	{
		Engineer_Motor.Turn_Motor.Turn_QR = 0;
		Action_Reset();
		Engineer_Relay.Relay_Reset();
		Engineer_Motor.Turn_Motor.Turn_Death();
		Rotate_ActionGroup = Rotate_Back_Start_Action;
		Extend_ActionGroup = None_Extension_Action;
	}
}
/* 动作组复位函数 --------------*/
void Action_Classdef::Action_Reset()
{
	Rotate_ActionGroup = None_Action;
	Extend_ActionGroup = None_Action;
	Lift_ActionGroup = None_Action;
	Turn_ActionGroup = None_Action;
}
/* 动作组全保护函数 --------------*/
void Action_Classdef::Action_Protect_ALL()
{
	Engineer_Motor.Turn_Motor.Turn_QR = 0;
	Action_Reset();
	Engineer_Auto.Auto_Reset();
	Engineer_Motor.Lift_Motor.Lift_Stop();
	Engineer_Motor.Turn_Motor.Turn_Stop();
	Engineer_Motor.Rotate_Motor.Rotate_Stop();
	Engineer_Motor.Extend_Motor.Extend_Stop();
}
/* 动作组半保护函数 --------------*/
void Action_Classdef::Action_Protect_Part()
{
	Action_Reset();
	Engineer_Auto.Auto_Reset();
	Engineer_Motor.Lift_Motor.Lift_Stop();
	Engineer_Motor.Turn_Motor.Turn_Stop();
}

/*---------------------------------------------- Rotate Action Function --------------------------------------------*/
void Action_Classdef::Do_Rotate_Action()
{
	switch(Rotate_ActionGroup)
	{
		case None_Action:
			break;
		case Rotate_POST_Action:
			if(Engineer_Motor.Rotate_Motor.Rotate_POST() == Rotate_POST_OK)
			{
				Rotate_POST_Num++;
			}
			if(Rotate_POST_Num == 10)
			{
				Rotate_POST_Num = 0;
				Rotate_ActionGroup = None_Action;
			}
			break;
		case Rotate_Back_Start_Action:
			Engineer_Motor.Rotate_Motor.Rotate_Back_Start();
			if(Engineer_Motor.Rotate_Motor.Rotate_Start_Judge())
			{
				Rotate_ActionGroup = None_Action;
			}
			break;
		case Rotate_Top_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
				Rotate_ActionGroup = None_Action;
			}
			break;
		case Rotate_Exchange_Action:
			Engineer_Motor.Rotate_Motor.Rotate_Exchange();
			if(Engineer_Motor.Rotate_Motor.Rotate_Exchange_Judge())
			{
				Rotate_ActionGroup = None_Action;
			}
			break;
		case Rotate_Hor_Action:
			if(Engineer_Motor.Extend_Motor.Extend_None_Judge() || Engineer_Motor.Extend_Motor.Extend_Mini_Judge())
			{
				Rotate_ActionGroup = None_Action;
			}
			else
			{
				Engineer_Relay.Loosen();
				Engineer_Motor.Rotate_Motor.Rotate_Hor();
				if(Engineer_Motor.Rotate_Motor.Rotate_Hor_Judge())
				{
					Rotate_ActionGroup = None_Action;
				}
			}
			break;
		case Rotate_Limit_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			Engineer_Motor.Rotate_Motor.Rotate_Limit();
			if(Engineer_Motor.Rotate_Motor.Rotate_Limit_Judge())
			{
				Rotate_ActionGroup = None_Action;
			}
			break;
		default:
			break;
	}
}

/*---------------------------------------------- Extend Action Function --------------------------------------------*/
void Action_Classdef::Do_Extend_Action()
{
	switch(Extend_ActionGroup)
	{
		case None_Action:
			break;
		case Extend_POST_Action:
			if(Engineer_Motor.Extend_Motor.Extend_POST() == Extend_POST_OK)
			{
				Extend_ActionGroup = None_Action;
			}
			break;
		case None_Extension_Action:
			Engineer_Motor.Extend_Motor.None_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_None_Judge())
			{
				Extend_ActionGroup = None_Action;
			}
			break;
		case Mini_Extension_Action:
			Engineer_Motor.Extend_Motor.Mini_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Mini_Judge())
			{
				Extend_ActionGroup = None_Action;
			}
			break;
		case First_Stage_Extension_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Extend_Motor.First_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_First_Judge())
			{
				Extend_ActionGroup = None_Action;
			}
			break;
		case Second_Stage_Extension_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Second_Judge())
			{
				Extend_ActionGroup = None_Action;
			}
			break;
		default:
			break;
	}
}

/*---------------------------------------------- Lift Action Function --------------------------------------------*/

void Action_Classdef::Do_Lift_Action()
{
	switch(Lift_ActionGroup)
	{
		case None_Action:
			break;
		case Lift_POST_Action:
			if(Engineer_Motor.Lift_Motor.Lift_POST() == Lift_POST_OK)
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case None_Lift_Action:
			Engineer_Motor.Lift_Motor.None_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_None_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case First_Stage_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.First_Stage_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_First_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case Second_Stage_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Second_Stage_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Second_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case Third_Stage_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Third_Stage_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Third_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case Test_jl_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Test_jl_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Test_jl_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case Take_BigBox_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Take_BigBox_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Take_BigBox_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case Take_SmallBox_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Take_SmallBox_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Take_SmallBox_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case Exchange_Box_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Exchange_Box_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Exchange_Box_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		case Meet_Box_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Auto.Auto_Reset();
			switch(Engineer_Box.Box_Num_Judge())
			{
				case 0:
					Engineer_Motor.Lift_Motor.None_Lift();
					break;
				
				case 1:
					Engineer_Motor.Lift_Motor.Third_Stage_Lift();
					break;
				
				case 2:
					Engineer_Motor.Lift_Motor.Lift_Stop();
					Lift_ActionGroup = None_Action;
					break;
				
				default:
					break;
			}

			break;
		case Vision_Lift_Action:
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Vision_BigBox_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Vision_BigBox_Judge())
			{
				Lift_ActionGroup = None_Action;
			}
			break;
		default:
			break;
	}
}

/*---------------------------------------------- Turn Action Function --------------------------------------------*/
void Action_Classdef::Do_Turn_Action()
{
	switch(Turn_ActionGroup)
	{
		case None_Action:
			break;
		case Turn_to_QR_Action:
			Engineer_Motor.Turn_Motor.Turn_QR = 1;
			if(Engineer_Motor.Turn_Motor.Turn_to_QR(Vision_DataPack.QR))
			{
				Engineer_Motor.Turn_Motor.Turn_QR = 0;
				if(Relay_Delay(200))
				{
					Turn_ActionGroup = None_Action;
				}
			}
			break;
		default:
			break;
	}
}

/*---------------------------------------------- Relay Action Function --------------------------------------------*/

/* 夹取函数 --------------*/
void Action_Classdef::Do_Pinch_Action()
{
	switch(Engineer_Relay.Pinch_Status)
	{
		case Relay_Off:
			Engineer_Relay.Pinch();
			break;
		case Relay_On:
			Engineer_Relay.Loosen();
			break;
		default:
			break;
	}
}
/* 救援函数 --------------*/
void Action_Classdef::Do_Rescue_Action()
{
	switch(Engineer_Relay.Rescue_Status)
	{
		case Relay_Off:
			Engineer_Relay.Rescue();
			break;
		case Relay_On:
			Engineer_Relay.Rescue_Back();
			break;
		default:
			break;
	}
}
/* 舵宝救援函数 --------------*/
void Action_Classdef::Do_SuperRescue_Action()
{
	switch(Engineer_Relay.SuperRescue_Status)
	{
		case Relay_Off:
			Engineer_Relay.SuperRescue();
			break;
		case Relay_On:
			Engineer_Relay.SuperRescue_Back();
			break;
		default:
			break;
	}
}
/* 刷卡函数 --------------*/
void Action_Classdef::Do_ETC_Action()
{
	switch(Engineer_Relay.ETC_Status)
	{
		case Relay_Off:
			Engineer_Relay.ETC();
			break;
		case Relay_On:
			Engineer_Relay.ETC_Back();
			break;
		default:
			break;
	}
}
