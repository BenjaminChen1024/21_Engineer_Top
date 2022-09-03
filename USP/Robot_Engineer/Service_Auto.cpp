/**
  ******************************************************************************
  * @file   : Service_Auto.cpp
  * @brief  : 服务自动组文件
  ******************************************************************************
  * @note
  *  - 
**/
/* Includes ------------------------------------------------------------------*/
#include "Service_Auto.h"
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -------------------------------------------------------*/

/*---------------------------------------------- 自动组任务 --------------------------------------------*/

/* 自动组任务执行函数 --------------*/
void Auto_Classdef::Auto_Task()
{
	Auto_RobBigBox();
	Auto_REBigBox();
	Auto_TakeSmallBox();
	Auto_TakeGroundBox();
	Auto_ExchangeBox();
	Auto_ExchangeAgain();
}
/* 自动组中断函数 --------------*/
void Auto_Classdef::Auto_Interrupt()
{
	if(Auto_RobBigBox_Status == Interrupt && Auto_REBigBox_Status == Interrupt && Auto_TakeSmallBox_Status == Interrupt && Auto_TakeGroundBox_Status == Interrupt && Auto_ExchangeBox_Status == Interrupt && Auto_ExchangeAgain_Status == Interrupt)
	{
		Auto_RobBigBox_Status = InterruptReturn;
		Auto_REBigBox_Status = InterruptReturn;
		Auto_TakeSmallBox_Status = InterruptReturn;
		Auto_TakeGroundBox_Status = InterruptReturn;
		Auto_ExchangeBox_Status = InterruptReturn;
		Auto_ExchangeAgain_Status = InterruptReturn;
	}
	else
	{
		Auto_RobBigBox_Status = Interrupt;
		Auto_REBigBox_Status = Interrupt;
		Auto_TakeSmallBox_Status = Interrupt;
		Auto_TakeGroundBox_Status = Interrupt;
		Auto_ExchangeBox_Status = Interrupt;
		Auto_ExchangeAgain_Status = Interrupt;
	}
}
/* 自动组复位函数 --------------*/
void Auto_Classdef::Auto_Reset()
{
	Auto_RobBigBox_Status = Waiting;
	Auto_REBigBox_Status = Waiting;
	Auto_TakeSmallBox_Status = Waiting;
	Auto_TakeGroundBox_Status = Waiting;
	Auto_ExchangeBox_Status = Waiting;
	Auto_ExchangeAgain_Status = Waiting;
}
/* 自动组开始函数 --------------*/
void Auto_Classdef::Auto_RobBigBox_Start()
{
	if(Auto_REBigBox_Status == Waiting)
	{
		Auto_RobBigBox_Status = StartAction;
	}
}
void Auto_Classdef::Auto_REBigBox_Start()
{
	if(Auto_REBigBox_Status == Waiting)
	{
		Auto_REBigBox_Status = StartAction;
	}
	else
	{
		Vision_DataPack.King = 3;
	}
}
void Auto_Classdef::Auto_TakeSmallBox_Start()
{
	if(Auto_REBigBox_Status == Waiting)
	{
		Auto_TakeSmallBox_Status = StartAction;
	}
}
void Auto_Classdef::Auto_TakeGroundBox_Start()
{
	if(Auto_REBigBox_Status == Waiting)
	{
		if(Auto_TakeGroundBox_Status == Waiting)
		{
			Auto_TakeGroundBox_Status = StartAction;
		}
		else
		{
			Vision_DataPack.King = 4;
		}
	}
}
void Auto_Classdef::Auto_ExchangeBox_Start()
{
	if(Auto_REBigBox_Status == Waiting)
	{
		Auto_ExchangeBox_Status = StartAction;
	}
}
void Auto_Classdef::Auto_ExchangeAgain_Start()
{
	if(Auto_REBigBox_Status == Waiting)
	{
		Auto_ExchangeAgain_Status = StartAction;
	}
}
/* 自动组半进入函数 --------------*/
void Auto_Classdef::Auto_ExchangeBox_Middle() {Auto_ExchangeBox_Status = RotateTop;}
/* 自动组状态判断函数 --------------*/
uint8_t Auto_Classdef::Auto_Status_Judge()
{
	if(Auto_RobBigBox_Status != Waiting){return 1;}
	else if(Auto_REBigBox_Status != Waiting){return 2;}
	else if(Auto_TakeSmallBox_Status != Waiting){return 3;}
	else if(Auto_TakeGroundBox_Status != Waiting){return 4;}
	else if(Auto_ExchangeBox_Status != Waiting){return 5;}
	else if(Auto_ExchangeAgain_Status != Waiting){return 5;}
	else{return 0;}
}
/* 自动组等待判断函数 --------------*/
bool Auto_Classdef::Auto_Waiting_Judge()
{
	return Auto_RobBigBox_Status == Waiting && Auto_REBigBox_Status == Waiting && Auto_TakeSmallBox_Status == Waiting && Auto_TakeGroundBox_Status == Waiting && Auto_ExchangeBox_Status == Waiting && Auto_ExchangeAgain_Status == Waiting;
}
/*---------------------------------------------- 自动抢大资源岛矿石 --------------------------------------------*/
void Auto_Classdef::Auto_RobBigBox()
{
	switch(Auto_RobBigBox_Status)
	{
		/* 动作等待 --------------*/
		case Waiting:
			RobBigBox_Interrupt_Action = Waiting;
			break;
		/* 动作中断 --------------*/
		case Interrupt:
			break;
		/* 中断回复 --------------*/
		case InterruptReturn:
			Auto_RobBigBox_Status = RobBigBox_Interrupt_Action;
			break;
		/* 动作开始 --------------*/
		case StartAction:
			Auto_RobBigBox_Status = VisionBoxLift;
			Auto_REBigBox_Status = Waiting;
			Auto_TakeSmallBox_Status = Waiting;
			Auto_TakeGroundBox_Status == Waiting;
			Auto_ExchangeBox_Status = Waiting;
			Auto_ExchangeAgain_Status = Waiting;
			break;
		/* 视觉抬升 --------------*/
		case VisionBoxLift:
			RobBigBox_Interrupt_Action = VisionBoxLift;
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Vision_BigBox_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Vision_BigBox_Judge() && Vision_DataPack.King == 1)
			{
				Auto_RobBigBox_Status = TakeBoxLift;
			}
			break;
		/* 取矿抬升 --------------*/
		case TakeBoxLift:
			RobBigBox_Interrupt_Action = TakeBoxLift;
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Take_BigBox_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Take_BigBox_Judge())
			{
				Auto_RobBigBox_Status = Extend;
			}
			break;
		/* 伸出 --------------*/
		case Extend:
			RobBigBox_Interrupt_Action = Extend;
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Second_Judge())
			{
				Auto_RobBigBox_Status = RotateTop1;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop1:
			RobBigBox_Interrupt_Action = RotateTop1;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge() && Vision_DataPack.King == 1)
			{
				Auto_RobBigBox_Status = Rotate;
			}
			break;
		/* 水平翻转 --------------*/
		case Rotate:
			RobBigBox_Interrupt_Action = Rotate;
			Engineer_Motor.Rotate_Motor.Rotate_Hor();
			if(Engineer_Motor.Rotate_Motor.Rotate_Hor_Judge())
			{
				Auto_RobBigBox_Status = PinchBox;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_RobBigBox_Status = RotateTop1;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox:
			RobBigBox_Interrupt_Action = PinchBox;
			Engineer_Relay.Pinch();
			Engineer_Motor.Turn_Motor.Turn_Death();
			if(Relay_Delay(500))
			{
				Auto_RobBigBox_Status = RotateTop2;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop2:
			RobBigBox_Interrupt_Action = RotateTop2;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
				Auto_RobBigBox_Status = IdentifyBox;
			}
			break;
		/* 识别矿石 --------------*/
		case IdentifyBox:
			RobBigBox_Interrupt_Action = IdentifyBox;
			switch(Vision_DataPack.King)
			{
				case 0:
					break;
				case 1:
					Auto_RobBigBox_Status = ExtendBack;
					break;
				case 2:
					Engineer_Relay.Loosen();
					Auto_RobBigBox_Status = PitchReset;
					break;
			}
			break;
			
		/*---------------------------------------------- 取矿失败 动作复位 --------------------------------------------*/
      
		/* 夹取复位 --------------*/
		case PitchReset:
			RobBigBox_Interrupt_Action = PitchReset;
			Engineer_Relay.Loosen();
			Auto_RobBigBox_Status = RotateReset;
			break;
		/* 旋转复位 --------------*/
		case RotateReset:
			RobBigBox_Interrupt_Action = RotateReset;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge() && Vision_DataPack.King ==1)
			{
				Auto_RobBigBox_Status = Rotate;
			}
			break;
			
		/*---------------------------------------------- 取矿成功 继续动作 --------------------------------------------*/

		/* 伸出收回 --------------*/
		case ExtendBack:
			RobBigBox_Interrupt_Action = ExtendBack;
			Engineer_Motor.Extend_Motor.Mini_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Mini_Judge())
			{
				switch(Engineer_Box.Box_Num)
				{
					case None_Box:
							Auto_RobBigBox_Status = StageLift1;
						break;
					case One_Box:
							Auto_RobBigBox_Status = StageLift1;
						break;
					default:
						Auto_RobBigBox_Status = Waiting;
						break;
				}
			}
			break;
		/* 阶级抬升 --------------*/
		case StageLift1:
			RobBigBox_Interrupt_Action = StageLift1;
			switch(Engineer_Box.Box_Num)
			{
				case None_Box:
						Auto_RobBigBox_Status = RotateBack;
					break;
				case One_Box:
					Engineer_Motor.Lift_Motor.Take_BigBox_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_Take_BigBox_Judge())
					{
						Auto_RobBigBox_Status = RotateBack;
					}
					break;
				default:
					break;
			}
			break;
		/* 翻转收回原点 --------------*/
		case RotateBack:
			RobBigBox_Interrupt_Action = RotateBack;
			Engineer_Motor.Turn_Motor.Turn_Life();
			Engineer_Motor.Rotate_Motor.Rotate_Back_Start();
			if(Engineer_Motor.Rotate_Motor.Rotate_Start_Judge())
			{
				Auto_RobBigBox_Status = StageLift2;
			}
			break;
		/* 阶级抬升 --------------*/
		case StageLift2:
			RobBigBox_Interrupt_Action = StageLift2;
			switch(Engineer_Box.Box_Num)
			{
				case None_Box:
					Engineer_Motor.Lift_Motor.First_Stage_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_First_Judge())
					{
						if(Relay_Delay(200))
						{
							Auto_RobBigBox_Status = LoosenBox;
						}
					}
					break;
				case One_Box:
						if(Relay_Delay(200))
						{
							Auto_RobBigBox_Status = LoosenBox;
						}
						break;
				default:
					break;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox:
			RobBigBox_Interrupt_Action = LoosenBox;
//			Engineer_Motor.Turn_Motor.Turn_Death();
			Engineer_Relay.Loosen();
			if(Relay_Delay(500))
			{
				switch(Engineer_Box.Box_Num)
				{
					case None_Box:
						Engineer_Box.Box_Num = One_Box;
						break;
					case One_Box:
						Engineer_Box.Box_Num = Two_Box;
						break;
					default:
						break;
				}
				Auto_RobBigBox_Status = Delay;
			}
			break;
		/* 延时 --------------*/
		case Delay:
			RobBigBox_Interrupt_Action = Delay;
			Engineer_Motor.Extend_Motor.None_Extension();
			if(Relay_Delay(500))
			{
				Auto_RobBigBox_Status = MeetBoxLift1;
			}
			break;
		/* 识矿抬升 --------------*/
		case MeetBoxLift1:
			RobBigBox_Interrupt_Action = MeetBoxLift1;
			Engineer_Motor.Extend_Motor.None_Extension();
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
					Auto_RobBigBox_Status = MeetBoxLift2;
					break;
				
				default:
					break;
			}
			break;
		/* 识矿抬升（由于取到矿石和取不到矿石会出现不同的情况，所以判断两次） --------------*/
		case MeetBoxLift2:
			RobBigBox_Interrupt_Action = MeetBoxLift2;
			Engineer_Motor.Extend_Motor.None_Extension();
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
					Auto_RobBigBox_Status = PinchProtect;
					break;
				
				default:
					break;
			}
			break;
		/* 矿石保护 --------------*/
		case PinchProtect:
			RobBigBox_Interrupt_Action = PinchProtect;
			if(Relay_Delay(300))
			{
				Engineer_Relay.Pinch();
				Auto_Reset();
			}
			break;
			
		default:
			Auto_Reset();
			break;
	}
}

/*---------------------------------------------- 自动'抢换'大资源岛矿石 --------------------------------------------*/
void Auto_Classdef::Auto_REBigBox()
{
	switch(Auto_REBigBox_Status)
	{
		/* 动作等待 --------------*/
		case Waiting:
			REBigBox_Interrupt_Action = Waiting;
			break;
		/* 动作中断 --------------*/
		case Interrupt:
			break;
		/* 中断回复 --------------*/
		case InterruptReturn:
			Auto_REBigBox_Status = REBigBox_Interrupt_Action;
			break;
		/* 动作开始 --------------*/
		case StartAction:
			Auto_RobBigBox_Status = Waiting;
			Auto_REBigBox_Status = VisionBoxLift;
			Auto_TakeSmallBox_Status = Waiting;
			Auto_TakeGroundBox_Status == Waiting;
			Auto_ExchangeBox_Status = Waiting;
			Auto_ExchangeAgain_Status = Waiting;
			break;
		/* 视觉抬升 --------------*/
		case VisionBoxLift:
			REBigBox_Interrupt_Action = VisionBoxLift;
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Vision_BigBox_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Vision_BigBox_Judge() && Vision_DataPack.King == 1)
			{
				Auto_REBigBox_Status = TakeBoxLift;
			}
			break;
		/* 取矿抬升 --------------*/
		case TakeBoxLift:
			REBigBox_Interrupt_Action = TakeBoxLift;
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Take_BigBox_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Take_BigBox_Judge())
			{
				Auto_REBigBox_Status = Extend1;
			}
			break;
		/* 伸出 --------------*/
		case Extend1:
			REBigBox_Interrupt_Action = Extend1;
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Second_Judge())
			{
				Auto_REBigBox_Status = RotateTop1;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop1:
			REBigBox_Interrupt_Action = RotateTop1;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge() && Vision_DataPack.King)
			{
				Auto_REBigBox_Status = Rotate;
			}
			break;
		/* 水平翻转 --------------*/
		case Rotate:
			REBigBox_Interrupt_Action = Rotate;
			Engineer_Motor.Rotate_Motor.Rotate_Hor();
			if(Engineer_Motor.Rotate_Motor.Rotate_Hor_Judge())
			{
				Auto_REBigBox_Status = PinchBox;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_REBigBox_Status = RotateTop1;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox:
			REBigBox_Interrupt_Action = PinchBox;
			Engineer_Relay.Pinch();
			Engineer_Motor.Turn_Motor.Turn_Death();
			if(Relay_Delay(500))
			{
				Auto_REBigBox_Status = RotateTop2;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop2:
			REBigBox_Interrupt_Action = RotateTop2;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
				Auto_REBigBox_Status = IdentifyBox;
			}
			break;
		/* 识别矿石 --------------*/
		case IdentifyBox:
			REBigBox_Interrupt_Action = IdentifyBox;
			switch(Vision_DataPack.King)
			{
				case 0:
					break;
				case 1:
					Auto_REBigBox_Status = RotateTopper;
					break;
				case 2:
					Engineer_Relay.Loosen();
					Auto_REBigBox_Status = PitchReset;
					break;
				case 3:
//					Auto_REBigBox_Status = ExchangeBoxLift;
					break;
			}
			break;
		/* 翻转收回 --------------*/
		case RotateTopper:
			REBigBox_Interrupt_Action = RotateTopper;
			Engineer_Motor.Extend_Motor.Mini_Extension();
			Engineer_Motor.Rotate_Motor.Rotate_Topper();
			if(Engineer_Motor.Rotate_Motor.Rotate_Topper_Judge() && Engineer_Motor.Extend_Motor.Extend_Mini_Judge())
			{
				Auto_REBigBox_Status = StageLift;
			}
			break;
		/* 阶级抬升 --------------*/
		case StageLift:
			REBigBox_Interrupt_Action = StageLift;
			switch(Engineer_Box.Box_Num)
			{
				case None_Box:
					Engineer_Motor.Lift_Motor.First_Stage_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_First_Judge())
					{
						if(Vision_DataPack.King == 3)
						{
							Auto_REBigBox_Status = ExchangeBoxLift;
						}
					}
					break;
				case One_Box:
					if(Vision_DataPack.King == 3)
					{
						Auto_REBigBox_Status = ExchangeBoxLift;
					}
					break;
				default:
						Auto_REBigBox_Status = Waiting;
					break;
			}
			break;
			
		/*---------------------------------------------- 取矿失败 动作复位 --------------------------------------------*/
      
		/* 夹取复位 --------------*/
		case PitchReset:
			REBigBox_Interrupt_Action = PitchReset;
			Engineer_Relay.Loosen();
			Auto_REBigBox_Status = RotateReset;
			break;
		/* 旋转复位 --------------*/
		case RotateReset:
			REBigBox_Interrupt_Action = RotateReset;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge() && Vision_DataPack.King ==1)
			{
				Auto_REBigBox_Status = Rotate;
			}
			break;
			
		/*---------------------------------------------- 取矿成功 继续动作 --------------------------------------------*/

	/* 兑换抬升 --------------*/
		case ExchangeBoxLift:
			REBigBox_Interrupt_Action = ExchangeBoxLift;
			Engineer_Motor.Lift_Motor.Exchange_Box_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Exchange_Box_Judge())
			{
				Auto_REBigBox_Status = RotateTop3;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop3:
			REBigBox_Interrupt_Action = RotateTop3;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			Engineer_Motor.Turn_Motor.Turn_Life();
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
//				if(Engineer_Motor.Turn_Motor.Turn_close_flag)
//				{
//					Auto_REBigBox_Status = TurnQR;
//				}
//				else
//				{
					Auto_REBigBox_Status = TurnHor;
//				}
			}
			break;
		/* 定位旋转 --------------*/
		case TurnQR:
			REBigBox_Interrupt_Action = TurnQR;
			Engineer_Motor.Turn_Motor.Turn_QR = 1;
			Engineer_Motor.Turn_Motor.Turn_Life();
			if(Engineer_Motor.Turn_Motor.Turn_to_QR(Vision_DataPack.QR))
			{
				Auto_REBigBox_Status = TurnHor;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_REBigBox_Status = TurnHor;
			}
			if(Vision_DataPack.King == 1)
			{
				Engineer_Motor.Turn_Motor.Turn_QR = 0;
				Auto_REBigBox_Status = TurnAdjust;
			}
			break;
		/* 水平旋转 --------------*/
		case TurnHor:
			REBigBox_Interrupt_Action = TurnHor;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			if(Vision_DataPack.King == 1)
			{
				Auto_REBigBox_Status = TurnAdjust;
			}
			break;
		/* 旋转调整 --------------*/
		case TurnAdjust:
			REBigBox_Interrupt_Action = TurnAdjust;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			Engineer_Motor.Turn_Motor.Turn_to_QR(1);
			if(Relay_Delay(80))
			{
				Auto_REBigBox_Status = RotateHor;
			}
			break;
		/* 水平翻转 --------------*/
		case RotateHor:
			REBigBox_Interrupt_Action = RotateHor;
			Engineer_Motor.Rotate_Motor.Rotate_Exchange();
			Engineer_Motor.Turn_Motor.Turn_Death();
			if(Engineer_Motor.Rotate_Motor.Rotate_Exchange_Judge() && Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_REBigBox_Status = LoosenBox1;
			}
			if(Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_REBigBox_Status = LoosenBox1;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox1:
			REBigBox_Interrupt_Action = LoosenBox1;
			Engineer_Relay.Loosen();
			if(Vision_DataPack.King == 1)
			{
				Auto_REBigBox_Status = ExtendBack1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack1:
			REBigBox_Interrupt_Action = ExtendBack1;
			Engineer_Motor.Extend_Motor.Negative_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Negative_Judge())
			{
				Auto_REBigBox_Status = PinchBox2;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox2:
			REBigBox_Interrupt_Action = PinchBox2;
			Engineer_Relay.Pinch();
			if(Relay_Delay(300))
			{
				Auto_REBigBox_Status = Extend2;
			}
			break;
		/* 兑换伸出 --------------*/
		case Extend2:
			REBigBox_Interrupt_Action = Extend2;
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Second_Judge() && Vision_DataPack.King == 1)
			{
				Auto_REBigBox_Status = ExtendBack2;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_REBigBox_Status = LoosenBox1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack2:
			REBigBox_Interrupt_Action = ExtendBack2;
			Engineer_Relay.Loosen();
			Engineer_Motor.Extend_Motor.None_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_None_Judge())
			{
				Auto_REBigBox_Status = RotateBack;
			}
			break;
		/* 翻转收回原点 --------------*/
		case RotateBack:
			REBigBox_Interrupt_Action = RotateBack;
			Engineer_Motor.Rotate_Motor.Rotate_Back_Start();
			if(Engineer_Motor.Rotate_Motor.Rotate_Start_Judge())
			{
				Auto_REBigBox_Status = LoosenBox2;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox2:
			REBigBox_Interrupt_Action = LoosenBox2;
			Engineer_Motor.Extend_Motor.None_Extension();
			Engineer_Relay.Loosen();
			Engineer_Box.Box_Reset();
			Auto_REBigBox_Status = Delay;
			break;
		/* 延时 --------------*/
		case Delay:
			REBigBox_Interrupt_Action = Delay;
			if(Relay_Delay(500))
			{
				Auto_REBigBox_Status = MeetBoxLift;
			}
			break;
		/* 识矿抬升 --------------*/
		case MeetBoxLift:
			REBigBox_Interrupt_Action = MeetBoxLift;
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
					Auto_Reset();
					break;
				
				default:
					break;
			}
			break;
			
		default:
			Auto_Reset();
			break;
	}
}


/*---------------------------------------------- 自动取小资源岛矿石 --------------------------------------------*/

void Auto_Classdef::Auto_TakeSmallBox()
{
	switch(Auto_TakeSmallBox_Status)
	{
		/* 动作等待 --------------*/
		case Waiting:
			TakeSmallBox_Interrupt_Action = Waiting;
			break;
		/* 动作中断 --------------*/
		case Interrupt:
			
			break;
		/* 中断回复 --------------*/
		case InterruptReturn:
			Auto_TakeSmallBox_Status = TakeSmallBox_Interrupt_Action;
			break;
		/* 动作开始 --------------*/
		case StartAction:
			Auto_RobBigBox_Status = Waiting;
			Auto_REBigBox_Status = Waiting;
			Auto_TakeSmallBox_Status = TakeBoxLift;
			Auto_TakeGroundBox_Status == Waiting;
			Auto_ExchangeBox_Status = Waiting;
			Auto_ExchangeAgain_Status = Waiting;
			break;
		/* 视觉抬升 --------------*/
//		case VisionBoxLift:
//			Auto_TakeSmallBox_Status = VisionBoxLift;
//			Second_Stage_Lift();
//			if(Lift_Second_Judge() && Vision_DataPack.King)
//			{
//				Auto_TakeSmallBox_Status = TakeBoxLift;
//			}
//			break;
		/* 取矿抬升 --------------*/
		case TakeBoxLift:
			TakeSmallBox_Interrupt_Action = TakeBoxLift;
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Take_SmallBox_Lift();
			Engineer_Motor.Extend_Motor.Mini_Extension();
			if(Engineer_Motor.Lift_Motor.Lift_Take_SmallBox_Judge())
			{
				Auto_TakeSmallBox_Status = Rotate;
			}
			break;
		/* 水平翻转 --------------*/
		case Rotate:
			TakeSmallBox_Interrupt_Action = Rotate;
			Vision_DataPack.King == 0;
			Engineer_Motor.Rotate_Motor.Rotate_SmallBox();
			if(Engineer_Motor.Rotate_Motor.Rotate_SmallBox_Judge() && Vision_DataPack.King == 1)
			{
				Auto_TakeSmallBox_Status = PinchBox;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_TakeSmallBox_Status = PitchReset;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox:
			TakeSmallBox_Interrupt_Action = PinchBox;
			Engineer_Relay.Pinch();
			Engineer_Motor.Turn_Motor.Turn_Death();
			if(Relay_Delay(500))
			{
				Auto_TakeSmallBox_Status = RotateTop2;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop2:
			TakeSmallBox_Interrupt_Action = RotateTop2;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
				Auto_TakeSmallBox_Status = IdentifyBox;
			}
			break;
		/* 识别矿石 --------------*/
		case IdentifyBox:
			TakeSmallBox_Interrupt_Action = IdentifyBox;
			switch(Vision_DataPack.King)
			{
				case 0:
					break;
				case 1:
					Auto_TakeSmallBox_Status = ExtendBack;
					break;
				case 2:
					Auto_TakeSmallBox_Status = PitchReset;
				default:
					break;
			}
			break;
			
		/*---------------------------------------------- 取矿失败 动作复位 --------------------------------------------*/
      
		/* 夹取复位 --------------*/
		case PitchReset:
			TakeSmallBox_Interrupt_Action = PitchReset;
			Engineer_Relay.Loosen();
			Auto_TakeSmallBox_Status = RotateReset;
			break;
		/* 旋转复位 --------------*/
		case RotateReset:
			TakeSmallBox_Interrupt_Action = RotateReset;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge() && Vision_DataPack.King == 1)
			{
				Auto_TakeSmallBox_Status = Rotate;
			}
			break;
			
		/*---------------------------------------------- 取矿成功 继续动作 --------------------------------------------*/
		
		/* 伸出收回 --------------*/
		case ExtendBack:
			TakeSmallBox_Interrupt_Action = ExtendBack;
			Engineer_Motor.Extend_Motor.Mini_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Mini_Judge())
			{
				if(Engineer_Box.Box_Num == Three_Box || Engineer_Box.Box_Num == Two_Box)
				{
					Auto_TakeSmallBox_Status = Waiting;
				}
				else
				{
					Auto_TakeSmallBox_Status = RotateBack;
				}
			}
			break;
			
		/* 翻转收回原点 --------------*/
		case RotateBack:
			TakeSmallBox_Interrupt_Action = RotateBack;
			Engineer_Motor.Rotate_Motor.Rotate_Back_Start();
			Engineer_Motor.Turn_Motor.Turn_Life();
			if(Engineer_Motor.Rotate_Motor.Rotate_Start_Judge())
			{
				Auto_TakeSmallBox_Status = StageLift;
			}
			break;
		/* 阶级抬升 --------------*/
		case StageLift:
			TakeSmallBox_Interrupt_Action = StageLift;
			switch(Engineer_Box.Box_Num)
			{
				case None_Box:
					Engineer_Motor.Lift_Motor.First_Stage_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_First_Judge())
					{
						Auto_TakeSmallBox_Status = LoosenBox;
					}
					break;
				case One_Box:
					Engineer_Motor.Lift_Motor.Take_BigBox_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_Take_BigBox_Judge())
					{
						Auto_TakeSmallBox_Status = LoosenBox;
					}
					break;
				default:
						Auto_TakeSmallBox_Status = Waiting;
					break;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox:
			TakeSmallBox_Interrupt_Action = LoosenBox;
			Engineer_Box.Box_Reset();
			Engineer_Relay.Loosen();
			if(Relay_Delay(200))
			{
				switch(Engineer_Box.Box_Num)
				{
					case None_Box:
						Engineer_Box.Box_Num = One_Box;
						break;
					case One_Box:
						Engineer_Box.Box_Num = Two_Box;
						break;
					default:
						break;
				}
				Auto_TakeSmallBox_Status = Delay;
			}
			break;
			
		/* 延时 --------------*/
		case Delay:
			TakeSmallBox_Interrupt_Action = Delay;
			if(Relay_Delay(600))
			{
				Auto_TakeSmallBox_Status = MeetBoxLift1;
			}
			break;
			
		/* 识矿抬升 --------------*/
		case MeetBoxLift1:
			TakeSmallBox_Interrupt_Action = MeetBoxLift1;
			Engineer_Motor.Extend_Motor.None_Extension();
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
					Auto_TakeSmallBox_Status = MeetBoxLift2;
					break;
				
				default:
					break;
			}
			break;
		/* 识矿抬升（由于取到矿石和取不到矿石会出现不同的情况，所以判断两次） --------------*/
		case MeetBoxLift2:
			TakeSmallBox_Interrupt_Action = MeetBoxLift2;
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
					Auto_TakeSmallBox_Status = PinchProtect;
					break;
				
				default:
					break;
			}
			break;
		/* 矿石保护 --------------*/
		case PinchProtect:
			TakeSmallBox_Interrupt_Action = PinchProtect;
			if(Relay_Delay(300))
			{
				Engineer_Relay.Pinch();
				Auto_Reset();
			}
			break;
		default:
			Auto_Reset();
			break;
	}
}

/*---------------------------------------------- 自动取地面矿石 --------------------------------------------*/
void Auto_Classdef::Auto_TakeGroundBox()
{
	switch(Auto_TakeGroundBox_Status)
	{
		/* 动作等待 --------------*/
		case Waiting:
			TakeGroundBox_Interrupt_Action = Waiting;
			break;
		/* 动作中断 --------------*/
		case Interrupt:
			break;
		/* 中断回复 --------------*/
		case InterruptReturn:
			Auto_TakeGroundBox_Status = TakeGroundBox_Interrupt_Action;
			break;
		/* 动作开始 --------------*/
		case StartAction:
			Auto_RobBigBox_Status = Waiting;
			Auto_REBigBox_Status = Waiting;
			Auto_TakeSmallBox_Status = Waiting;
			Auto_TakeGroundBox_Status = TakeBoxLift;
			Auto_ExchangeBox_Status = Waiting;
			Auto_ExchangeAgain_Status = Waiting;
			break;
		/* 取矿抬升 --------------*/
		case TakeBoxLift:
			TakeGroundBox_Interrupt_Action = TakeBoxLift;
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Negative_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Negative_Judge())
			{
				Auto_TakeGroundBox_Status = Extend;
			}
			break;
		/* 伸出 --------------*/
		case Extend:
			TakeGroundBox_Interrupt_Action = Extend;
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Second_Judge())
			{
				Auto_TakeGroundBox_Status = Rotate;
			}
			break;
		/* 极限翻转 --------------*/
		case Rotate:
			TakeGroundBox_Interrupt_Action = Rotate;
			Engineer_Motor.Rotate_Motor.Rotate_Limit();
			if(Engineer_Motor.Rotate_Motor.Rotate_Limit_Judge())
			{
				Auto_TakeGroundBox_Status = IdentifyBox;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_TakeGroundBox_Status = PitchReset;
			}
			break;
		/* 识别矿石 --------------*/
		case IdentifyBox:
			TakeGroundBox_Interrupt_Action = IdentifyBox;
//			Engineer_Motor.Turn_Motor.Turn_Death();
			switch(Vision_DataPack.King)
			{
				case 0:
					break;
				case 1:
					Auto_TakeGroundBox_Status = PinchBox;
					break;
				case 2:
					Engineer_Relay.Loosen();
					Auto_TakeGroundBox_Status = PitchReset;
					break;
				default:
					break;
			}
			break;
			
		/*---------------------------------------------- 取矿失败 动作复位 --------------------------------------------*/
      
		/* 夹取复位 --------------*/
		case PitchReset:
			TakeGroundBox_Interrupt_Action = PitchReset;
			Engineer_Relay.Loosen();
			Auto_TakeGroundBox_Status = RotateReset;
			break;
		/* 旋转复位 --------------*/
		case RotateReset:
			TakeGroundBox_Interrupt_Action = RotateReset;
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge() && Vision_DataPack.King ==1)
			{
				Auto_TakeGroundBox_Status = Rotate;
			}
			break;
			
		/*---------------------------------------------- 取矿成功 继续动作 --------------------------------------------*/
		
		/* 矿石夹取 --------------*/
		case PinchBox:
			TakeGroundBox_Interrupt_Action = PinchBox;
			Engineer_Relay.Pinch();
			if(Relay_Delay(300))
			{
				Auto_TakeGroundBox_Status = StageLift1;
			}
			break;
		/* 阶级抬升 --------------*/
		case StageLift1:
			TakeGroundBox_Interrupt_Action = StageLift1;
			switch(Engineer_Box.Box_Num)
			{
				case None_Box:
					Engineer_Motor.Lift_Motor.First_Stage_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_First_Judge())
					{
						Auto_TakeGroundBox_Status = RotateTopper;
					}
					break;
				case One_Box:
					Engineer_Motor.Lift_Motor.Take_BigBox_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_Take_BigBox_Judge())
					{
						Auto_TakeGroundBox_Status = RotateTopper;
					}
					break;
				default:
					Auto_TakeGroundBox_Status = Waiting;
					break;
			}
			break;
		/* 翻转收回 --------------*/
		case RotateTopper:
			TakeGroundBox_Interrupt_Action = RotateTopper;
			Engineer_Motor.Extend_Motor.Mini_Extension();
			Engineer_Motor.Rotate_Motor.Rotate_Topper();
			if(Engineer_Motor.Rotate_Motor.Rotate_Topper_Judge() && Engineer_Motor.Extend_Motor.Extend_Mini_Judge())
			{
				if(Vision_DataPack.King == 4)
				{
					Auto_TakeGroundBox_Status = ExchangeBoxLift;
				}
			}
			break;
	/* 兑换抬升 --------------*/
		case ExchangeBoxLift:
			TakeGroundBox_Interrupt_Action = ExchangeBoxLift;
			Engineer_Motor.Lift_Motor.Exchange_Box_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Exchange_Box_Judge())
			{
				Auto_TakeGroundBox_Status = RotateTop3;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop3:
			TakeGroundBox_Interrupt_Action = RotateTop3;
			Engineer_Motor.Turn_Motor.Turn_Life();
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
//				if(Engineer_Motor.Turn_Motor.Turn_close_flag)
//				{
//					Auto_TakeGroundBox_Status = TurnQR;
//				}
//				else
//				{
					Auto_TakeGroundBox_Status = TurnHor;
//				}
			}
			break;
		/* 定位旋转 --------------*/
		case TurnQR:
			TakeGroundBox_Interrupt_Action = TurnQR;
			Engineer_Motor.Turn_Motor.Turn_QR = 1;
			if(Engineer_Motor.Turn_Motor.Turn_to_QR(Vision_DataPack.QR))
			{
				Auto_TakeGroundBox_Status = TurnHor;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_TakeGroundBox_Status = TurnHor;
			}
			if(Vision_DataPack.King == 1)
			{
				Engineer_Motor.Turn_Motor.Turn_QR = 0;
				Auto_TakeGroundBox_Status = TurnAdjust;
			}
			break;
		/* 水平旋转 --------------*/
		case TurnHor:
			TakeGroundBox_Interrupt_Action = TurnHor;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			if(Vision_DataPack.King == 1)
			{
				Auto_TakeGroundBox_Status = TurnAdjust;
			}
			break;
		/* 旋转调整 --------------*/
		case TurnAdjust:
			TakeGroundBox_Interrupt_Action = TurnAdjust;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			Engineer_Motor.Turn_Motor.Turn_to_QR(1);
			if(Relay_Delay(80))
			{
				Auto_TakeGroundBox_Status = RotateHor;
			}
			break;
		/* 水平翻转 --------------*/
		case RotateHor:
			TakeGroundBox_Interrupt_Action = RotateHor;
			Engineer_Motor.Rotate_Motor.Rotate_Exchange();
			Engineer_Motor.Turn_Motor.Turn_Death();
			if(Engineer_Motor.Rotate_Motor.Rotate_Exchange_Judge() && Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_TakeGroundBox_Status = LoosenBox1;
			}
			if(Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_TakeGroundBox_Status = LoosenBox1;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox1:
			TakeGroundBox_Interrupt_Action = LoosenBox1;
			Engineer_Relay.Loosen();
			if(Vision_DataPack.King == 1)
			{
				Auto_TakeGroundBox_Status = ExtendBack1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack1:
			TakeGroundBox_Interrupt_Action = ExtendBack1;
			Engineer_Motor.Extend_Motor.Negative_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Negative_Judge())
			{
				Auto_TakeGroundBox_Status = PinchBox2;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox2:
			TakeGroundBox_Interrupt_Action = PinchBox2;
			Engineer_Relay.Pinch();
			if(Relay_Delay(300))
			{
				Auto_TakeGroundBox_Status = Extend2;
			}
			break;
		/* 兑换伸出 --------------*/
		case Extend2:
			TakeGroundBox_Interrupt_Action = Extend2;
			Engineer_Motor.Extend_Motor.Second_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Second_Judge() && Vision_DataPack.King == 1)
			{
				Auto_TakeGroundBox_Status = ExtendBack2;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_TakeGroundBox_Status = LoosenBox1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack2:
			TakeGroundBox_Interrupt_Action = ExtendBack2;
			Engineer_Relay.Loosen();
			Engineer_Motor.Extend_Motor.None_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_None_Judge())
			{
				Auto_TakeGroundBox_Status = RotateBack;
			}
			break;
		/* 翻转收回原点 --------------*/
		case RotateBack:
			TakeGroundBox_Interrupt_Action = RotateBack;
			Engineer_Motor.Rotate_Motor.Rotate_Back_Start();
			if(Engineer_Motor.Rotate_Motor.Rotate_Start_Judge())
			{
				Auto_TakeGroundBox_Status = LoosenBox2;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox2:
			TakeGroundBox_Interrupt_Action = LoosenBox2;
			Engineer_Motor.Extend_Motor.None_Extension();
			Engineer_Relay.Loosen();
			Engineer_Box.Box_Reset();
			Auto_TakeGroundBox_Status = Delay;
			break;
		/* 延时 --------------*/
		case Delay:
			TakeGroundBox_Interrupt_Action = Delay;
			if(Relay_Delay(500))
			{
				Auto_TakeGroundBox_Status = MeetBoxLift;
			}
			break;
		/* 识矿抬升 --------------*/
		case MeetBoxLift:
			TakeGroundBox_Interrupt_Action = MeetBoxLift;
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
					Auto_Reset();
					break;
				
				default:
					break;
			}
			break;
			
		default:
			Auto_Reset();
			break;
	}
}

/*---------------------------------------------- 自动兑换矿石 --------------------------------------------*/

void Auto_Classdef::Auto_ExchangeBox()
{
	switch(Auto_ExchangeBox_Status)
	{
		/* 动作等待 --------------*/
		case Waiting:
			ExchangeBox_Interrupt_Action = Waiting;
			break;
		/* 动作中断 --------------*/
		case Interrupt:
			break;
		/* 中断回复 --------------*/
		case InterruptReturn:
			Auto_ExchangeBox_Status = ExchangeBox_Interrupt_Action;
			break;
		/* 动作开始 --------------*/
		case StartAction:
			Auto_RobBigBox_Status = Waiting;
			Auto_REBigBox_Status = Waiting;
			Auto_TakeSmallBox_Status = Waiting;
			Auto_TakeGroundBox_Status = Waiting;
			Auto_ExchangeBox_Status = MeetBoxLift1;
			Auto_ExchangeAgain_Status = Waiting;
			break;
		/* 视觉抬升 --------------*/
//		case VisionBoxLift:
//			Auto_ExchangeBox_Status = VisionBoxLift;
//			Second_Stage_Lift();
//			if(Lift_Second_Judge() && Vision_DataPack.King)
//			{
//				Auto_ExchangeBox_Status = StageLift1;
//			}
//			break;
		/* 识矿抬升 --------------*/
		case MeetBoxLift1:
			ExchangeBox_Interrupt_Action = MeetBoxLift1;
			Engineer_Relay.Loosen();
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
					Auto_ExchangeBox_Status = StageLift1;
					break;
				
				default:
					break;
			}
			break;
		/* 阶级抬升 --------------*/
		case StageLift1:
			ExchangeBox_Interrupt_Action = StageLift1;
			Engineer_Relay.Loosen();
			switch(Engineer_Box.Box_Num)
			{
				case One_Box:
					Engineer_Motor.Lift_Motor.None_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_None_Judge())
					{
						Auto_ExchangeBox_Status = PinchBox1;
					}
					break;
				case Two_Box:
					Engineer_Motor.Lift_Motor.Second_Stage_Lift();
					if(Engineer_Motor.Lift_Motor.Lift_Second_Judge())
					{
						Auto_ExchangeBox_Status = PinchBox1;
					}
					break;
				default:
					Auto_ExchangeBox_Status = Waiting;
					break;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox1:
			ExchangeBox_Interrupt_Action = PinchBox1;
			Engineer_Relay.Pinch();
			if(Relay_Delay(300))
			{
				Auto_ExchangeBox_Status = ExchangeBoxLift;
			}
			break;
		/* 兑换抬升 --------------*/
		case ExchangeBoxLift:
			ExchangeBox_Interrupt_Action = ExchangeBoxLift;
			Engineer_Motor.Lift_Motor.Exchange_Box_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Exchange_Box_Judge())
			{
				Auto_ExchangeBox_Status = RotateTop;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop:
			ExchangeBox_Interrupt_Action = RotateTop;
			Engineer_Motor.Extend_Motor.Third_Stage_Extension();
			Engineer_Motor.Turn_Motor.Turn_Life();
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
				Vision_DataPack.King = 0;
//				if(Engineer_Motor.Turn_Motor.Turn_close_flag)
//				{
//					Auto_ExchangeBox_Status = TurnQR;
//				}
//				else
//				{
					Auto_ExchangeBox_Status = TurnHor;
//				}
			}
			break;
		/* 定位旋转 --------------*/
		case TurnQR:
			ExchangeBox_Interrupt_Action = TurnQR;
			Engineer_Motor.Turn_Motor.Turn_QR = 1;
			Engineer_Motor.Turn_Motor.Turn_Life();
			if(Engineer_Motor.Turn_Motor.Turn_to_QR(Vision_DataPack.QR))
			{
				Auto_ExchangeBox_Status = TurnHor;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_ExchangeBox_Status = TurnHor;
			}
			if(Vision_DataPack.King == 1)
			{
				Engineer_Motor.Turn_Motor.Turn_QR = 0;
				Auto_ExchangeBox_Status = TurnAdjust;
			}
			break;
		/* 水平旋转 --------------*/
		case TurnHor:
			ExchangeBox_Interrupt_Action = TurnHor;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			if(Vision_DataPack.King == 1)
			{
				Auto_ExchangeBox_Status = TurnAdjust;
			}
			break;
		/* 旋转调整 --------------*/
		case TurnAdjust:
			ExchangeBox_Interrupt_Action = TurnAdjust;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			Engineer_Motor.Turn_Motor.Turn_to_QR(1);
			if(Relay_Delay(80))
			{
				Auto_ExchangeBox_Status = RotateHor;
			}
			break;
		/* 水平翻转 --------------*/
		case RotateHor:
			ExchangeBox_Interrupt_Action = RotateHor;
			Engineer_Motor.Rotate_Motor.Rotate_Exchange();
			Engineer_Motor.Turn_Motor.Turn_Death();
			if(Engineer_Motor.Rotate_Motor.Rotate_Exchange_Judge() && Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_ExchangeBox_Status = LoosenBox1;
			}
			if(Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_ExchangeBox_Status = LoosenBox1;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox1:
			ExchangeBox_Interrupt_Action = LoosenBox1;
			Engineer_Relay.Loosen();
			if(Vision_DataPack.King == 1)
			{
				Auto_ExchangeBox_Status = ExtendBack1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack1:
			ExchangeBox_Interrupt_Action = ExtendBack1;
			Engineer_Motor.Extend_Motor.Negative_Extension();
			Engineer_Motor.Rotate_Motor.Rotate_Push();
			if(Engineer_Motor.Extend_Motor.Extend_Negative_Judge())
			{
				Auto_ExchangeBox_Status = PinchBox2;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox2:
			ExchangeBox_Interrupt_Action = PinchBox2;
			Engineer_Relay.Pinch();
			if(Relay_Delay(300))
			{
				Auto_ExchangeBox_Status = Extend;
			}
			break;
		/* 兑换伸出 --------------*/
		case Extend:
			ExchangeBox_Interrupt_Action = Extend;
			Engineer_Motor.Extend_Motor.Third_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Third_Judge() && Vision_DataPack.King == 1)
			{
				Auto_ExchangeBox_Status = ExtendBack2;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_ExchangeBox_Status = LoosenBox1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack2:
			ExchangeBox_Interrupt_Action = ExtendBack2;
			Engineer_Relay.Loosen();
			Engineer_Motor.Extend_Motor.None_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_None_Judge())
			{
				Auto_ExchangeBox_Status = RotateBack;
			}
			break;
		/* 翻转收回原点 --------------*/
		case RotateBack:
			ExchangeBox_Interrupt_Action = RotateBack;
			Engineer_Motor.Rotate_Motor.Rotate_Back_Start();
			if(Engineer_Motor.Rotate_Motor.Rotate_Start_Judge())
			{
				Auto_ExchangeBox_Status = LoosenBox2;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox2:
			ExchangeBox_Interrupt_Action = LoosenBox2;
			Engineer_Motor.Extend_Motor.None_Extension();
			Engineer_Relay.Loosen();
			Engineer_Box.Box_Reset();
			switch(Engineer_Box.Box_Num)
			{
				case None_Box:
					break;
				case One_Box:
					Engineer_Box.Box_Num = None_Box;
					break;
				case Two_Box:
					Engineer_Box.Box_Num = One_Box;
					break;
				default:
					break;
			}
			Auto_ExchangeBox_Status = Delay;
			break;
		/* 延时 --------------*/
		case Delay:
			ExchangeBox_Interrupt_Action = Delay;
			if(Relay_Delay(500))
			{
				Auto_ExchangeBox_Status = MeetBoxLift;
			}
			break;
		/* 识矿抬升 --------------*/
		case MeetBoxLift:
			ExchangeBox_Interrupt_Action = MeetBoxLift;
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
					Auto_Reset();
					break;
				
				default:
					break;
			}
			break;
			
		default:
			Auto_Reset();
			break;
	}
}

/*---------------------------------------------- 再次兑换矿石 --------------------------------------------*/

void Auto_Classdef::Auto_ExchangeAgain()
{
	switch(Auto_ExchangeAgain_Status)
	{
		/* 动作等待 --------------*/
		case Waiting:
			ExchangeAgain_Interrupt_Action = Waiting;
			break;
		/* 动作中断 --------------*/
		case Interrupt:
			break;
		/* 中断回复 --------------*/
		case InterruptReturn:
			Auto_ExchangeAgain_Status = ExchangeAgain_Interrupt_Action;
			break;
		/* 动作开始 --------------*/
		case StartAction:
			Auto_RobBigBox_Status = Waiting;
			Auto_REBigBox_Status = Waiting;
			Auto_TakeSmallBox_Status = Waiting;
			Auto_TakeGroundBox_Status = Waiting;
			Auto_ExchangeBox_Status = Waiting;
			Auto_ExchangeAgain_Status = ExchangeBoxLift;
			break;
		/* 兑换抬升 --------------*/
		case ExchangeBoxLift:
			ExchangeAgain_Interrupt_Action = ExchangeBoxLift;
			Engineer_Relay.Loosen();
			Engineer_Motor.Lift_Motor.Exchange_Box_Lift();
			if(Engineer_Motor.Lift_Motor.Lift_Exchange_Box_Judge())
			{
				Auto_ExchangeAgain_Status = Extend1;
			}
			break;
		/* 伸出 --------------*/
		case Extend1:
			ExchangeAgain_Interrupt_Action = Extend1;
			Engineer_Motor.Extend_Motor.Third_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Third_Judge())
			{
				Auto_ExchangeAgain_Status = RotateTop1;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop1:
			ExchangeAgain_Interrupt_Action = RotateTop1;
			Engineer_Relay.Loosen();
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge() && Vision_DataPack.King == 1)
			{
				Auto_ExchangeAgain_Status = Rotate;
			}
			break;
		/* 水平翻转 --------------*/
		case Rotate:
			ExchangeAgain_Interrupt_Action = Rotate;
			Engineer_Motor.Rotate_Motor.Rotate_ExchangeAgain();
			if(Engineer_Motor.Rotate_Motor.Rotate_ExchangeAgain_Judge())
			{
				Auto_ExchangeAgain_Status = PinchBox;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_ExchangeAgain_Status = RotateTop1;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox:
			ExchangeAgain_Interrupt_Action = PinchBox;
			Engineer_Relay.Pinch();
			if(Relay_Delay(500))
			{
				Auto_ExchangeAgain_Status = RotateTop2;
			}
			break;
		/* 识别翻转 --------------*/
		case RotateTop2:
			ExchangeAgain_Interrupt_Action = RotateTop2;
			Engineer_Motor.Turn_Motor.Turn_Life();
			Engineer_Motor.Rotate_Motor.Rotate_Top();
			if(Engineer_Motor.Rotate_Motor.Rotate_Top_Judge())
			{
				Vision_DataPack.King = 0;
				Auto_ExchangeAgain_Status = TurnHor;
			}
			break;
		/* 水平旋转 --------------*/
		case TurnHor:
			ExchangeAgain_Interrupt_Action = TurnHor;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			if(Vision_DataPack.King == 2)
			{
				Auto_ExchangeAgain_Status = RotateTop1;
			}
			if(Vision_DataPack.King == 1)
			{
				Auto_ExchangeAgain_Status = TurnAdjust;
			}
			break;
		/* 旋转调整 --------------*/
		case TurnAdjust:
			ExchangeAgain_Interrupt_Action = TurnAdjust;
			Engineer_Motor.Turn_Motor.Turn_QR = 0;
			Engineer_Motor.Turn_Motor.Turn_to_QR(1);
			if(Relay_Delay(80))
			{
				Auto_ExchangeAgain_Status = RotateHor;
			}
			break;
		/* 水平翻转 --------------*/
		case RotateHor:
			ExchangeAgain_Interrupt_Action = RotateHor;
			Engineer_Motor.Rotate_Motor.Rotate_Exchange();
			Engineer_Motor.Turn_Motor.Turn_Death();
			if(Engineer_Motor.Rotate_Motor.Rotate_Exchange_Judge() && Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_ExchangeAgain_Status = LoosenBox1;
			}
			if(Vision_DataPack.King == 1)
			{
				Vision_DataPack.King = 0;
				Auto_ExchangeAgain_Status = LoosenBox1;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox1:
			ExchangeAgain_Interrupt_Action = LoosenBox1;
			Engineer_Relay.Loosen();
			if(Vision_DataPack.King == 1)
			{
				Auto_ExchangeAgain_Status = ExtendBack1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack1:
			ExchangeAgain_Interrupt_Action = ExtendBack1;
			Engineer_Motor.Extend_Motor.Negative_Extension();
			Engineer_Motor.Rotate_Motor.Rotate_Push();
			if(Engineer_Motor.Extend_Motor.Extend_Negative_Judge())
			{
				Auto_ExchangeAgain_Status = PinchBox2;
			}
			break;
		/* 矿石夹取 --------------*/
		case PinchBox2:
			ExchangeAgain_Interrupt_Action = PinchBox2;
			Engineer_Relay.Pinch();
			if(Relay_Delay(300))
			{
				Auto_ExchangeAgain_Status = Extend2;
			}
			break;
		/* 兑换伸出 --------------*/
		case Extend2:
			ExchangeAgain_Interrupt_Action = Extend2;
			Engineer_Motor.Extend_Motor.Third_Stage_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_Third_Judge() && Vision_DataPack.King == 1)
			{
				Auto_ExchangeAgain_Status = ExtendBack2;
			}
			if(Vision_DataPack.King == 2)
			{
				Auto_ExchangeAgain_Status = LoosenBox1;
			}
			break;
		/* 伸出收回 --------------*/
		case ExtendBack2:
			ExchangeAgain_Interrupt_Action = ExtendBack2;
			Engineer_Relay.Loosen();
			Engineer_Motor.Extend_Motor.None_Extension();
			if(Engineer_Motor.Extend_Motor.Extend_None_Judge())
			{
				Auto_ExchangeAgain_Status = RotateBack;
			}
			break;
		/* 翻转收回原点 --------------*/
		case RotateBack:
			ExchangeAgain_Interrupt_Action = RotateBack;
			Engineer_Motor.Rotate_Motor.Rotate_Back_Start();
			if(Engineer_Motor.Rotate_Motor.Rotate_Start_Judge())
			{
				Auto_ExchangeAgain_Status = LoosenBox2;
			}
			break;
		/* 矿石松开 --------------*/
		case LoosenBox2:
			ExchangeAgain_Interrupt_Action = LoosenBox2;
			Engineer_Motor.Extend_Motor.None_Extension();
			Engineer_Relay.Loosen();
			Engineer_Box.Box_Reset();
			Auto_ExchangeAgain_Status = Delay;
			break;
		/* 延时 --------------*/
		case Delay:
			ExchangeAgain_Interrupt_Action = Delay;
			if(Relay_Delay(500))
			{
				Auto_ExchangeAgain_Status = MeetBoxLift;
			}
			break;
		/* 识矿抬升 --------------*/
		case MeetBoxLift:
			ExchangeAgain_Interrupt_Action = MeetBoxLift;
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
					Auto_Reset();
					break;
				
				default:
					break;
			}
			break;
			
		default:
			Auto_Reset();
			break;
	}
}
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
