/**
  ******************************************************************************
  * @file   : Service_Communication.cpp
  * @brief  : 服务通信文件
  ******************************************************************************
  * @note
  *  - 
**/

/* Includes ------------------------------------------------------------------*/
#include "Service_Communication.h"
/* Private variables --------------、-------------------------------------------*/
/* 视觉数据包 --------------*/
Vision_DataPack_Typedef Vision_DataPack;
/* 按键数据包 --------------*/
Key_DataPack_Typedef	Key_DataPack;
/* 按键标志位 --------------*/
KeyFlag_Typedef KeyFlag;

/* Private function prototypes -------------------------------------------------------*/

/**
* @brief  板间通信数据发送函数.
* @param  void.
* @return void.
* @note  	None.
*/
void UIMsgSend()
{
	uint8_t UI_Tx_Data[8];
	UI_Tx_Data[0] = (uint8_t)(LeftLift_PosPID.Current / 630000 * 100);
	UI_Tx_Data[1] = (uint8_t)(RightLift_PosPID.Current / 630000 * 100);
	UI_Tx_Data[2] = Engineer_Box.Box_Num;
	UI_Tx_Data[3] = Engineer_Auto.Auto_Status_Judge();
	UI_Tx_Data[4] = Engineer_Relay.Rescue_Status;
	UI_Tx_Data[5] = Engineer_Relay.SuperRescue_Status;
	UI_Tx_Data[6] = Engineer_Relay.ETC_Status;
	UI_Tx_Data[7] = Engineer_Motor.Turn_Motor.Turn_QR;
	
	if(UI_TX_QueueHandle != NULL)
	{
		xQueueSend(UI_TX_QueueHandle,UI_Tx_Data,NULL);
	}
}

/**
* @brief  板件通信数据更新函数.
* @param  msg_rece	数据包.
* @param  StdID			数据包ID.
* @return void.
* @note  	数据包ID	|				0x1ff					|				0x200							|				0x201						|	
							0			|				_Z						|				_R								|				QR							|
							1			|				_X						|				_V								|				TakeBox					|
							2			|				_C						|				_E								|				ExtendBack			|
							3			|				_B						|				_Mouse_L					|												|
							4			|				_F						|													|												|
							5			|				_G						|													|												|
							6			|				_CTRL					|													|												|
							7			|				_SHIFT				|				DR16_Status				|												|

*/
void Update_USART_Board(uint8_t *msg_rece, uint8_t Status)
{
	if(Status)
	{
		Key_DataPack.Key_Z_IsPress = msg_rece[1];
		Key_DataPack.Key_X_IsPress = msg_rece[2];
		Key_DataPack.Key_C_IsPress = msg_rece[3];
		Key_DataPack.Key_B_IsPress = msg_rece[4];
		Key_DataPack.Key_F_IsPress = msg_rece[5];
		Key_DataPack.Key_G_IsPress = msg_rece[6];
		Key_DataPack.Key_CTRL_IsPress = msg_rece[7];
		Key_DataPack.Key_SHIFT_IsPress = msg_rece[8];

		Key_DataPack.Key_R_IsPress = msg_rece[9];
		Key_DataPack.Key_V_IsPress = msg_rece[10];
		Key_DataPack.Key_E_IsPress = msg_rece[11];
		Key_DataPack.Key_Mouse_L_IsPress = msg_rece[12];
		Key_DataPack.DR16_S2 = msg_rece[13];
		Key_DataPack.Key_Mouse_R_IsPress = msg_rece[14];
		Key_DataPack.Key_Q_IsPress = msg_rece[15];
		Key_DataPack.DR16_Status = msg_rece[16];

		Vision_DataPack.QR = msg_rece[17];
		Vision_DataPack.TakeBox = msg_rece[19];
		Vision_DataPack.ExtendBack = (float)((unsigned char)msg_rece[23] << 8 | (unsigned char)msg_rece[24]);
	}
	else
	{
		Key_DataPack.Key_Z_IsPress = 0;
		Key_DataPack.Key_X_IsPress = 0;
		Key_DataPack.Key_C_IsPress = 0;
		Key_DataPack.Key_B_IsPress = 0;
		Key_DataPack.Key_F_IsPress = 0;
		Key_DataPack.Key_G_IsPress = 0;
		Key_DataPack.Key_CTRL_IsPress = 0;
		Key_DataPack.Key_SHIFT_IsPress = 0;
		Key_DataPack.Key_R_IsPress = 0;
		Key_DataPack.Key_V_IsPress = 0;
		Key_DataPack.Key_E_IsPress = 0;
		Key_DataPack.Key_Q_IsPress = 0;
		Key_DataPack.Key_Mouse_L_IsPress = 0;
		Key_DataPack.Key_Mouse_R_IsPress = 0;
		Key_DataPack.DR16_Status = 0;
		Key_DataPack.DR16_S2 = 0;
		Vision_DataPack.QR = 0;
		Vision_DataPack.TakeBox = 0;
		Vision_DataPack.ExtendBack = 0;
	}
	
	Vision_DataPack.King = 0;
}

/**
* @brief  保护按键控制函数.
* @param  void.
* @return void.
* @note  	进入保护状态时进行抬升电机独立手动调整.
*/
void Protect_Key_Control()
{
	/* 设置按键标志位 --------------*/
	Set_KeyFlag();
	
	if(KeyFlag_judge(_F) == ABC){}
	if(KeyFlag_judge(_F) == SHIFT_ABC){Engineer_Motor.Lift_Motor.Lift_Adjust(1,1);}
	if(KeyFlag_judge(_F) == CTRL_ABC){Engineer_Motor.Lift_Motor.Lift_Adjust(1,3);}
	if(KeyFlag_judge(_F) == CTRL_SHIRT_ABC){}
		
	if(KeyFlag_judge(_G) == ABC){}
	if(KeyFlag_judge(_G) == SHIFT_ABC){Engineer_Motor.Lift_Motor.Lift_Adjust(2,1);}
	if(KeyFlag_judge(_G) == CTRL_ABC){Engineer_Motor.Lift_Motor.Lift_Adjust(2,3);}
	if(KeyFlag_judge(_G) == CTRL_SHIRT_ABC){}
}

/**
* @brief  按键控制函数.
* @param  void.
* @return void.
* @note  	通过对应按键给予独立动作组与自动动作组指令.
*/
void Key_Control()
{
	/* 设置按键标志位 --------------*/
	Set_KeyFlag();
	
//	Engineer_Action.Action_POST();
	
	if(IsKeyPress(_CTRL) && IsKeyPress(_SHIFT)){Engineer_Action.Action_Protect_ALL();}
	
	if(KeyFlag._Z_KeyFlag && !IsKeyPress(_Z)){Engineer_Action.Lift_ActionGroup = Meet_Box_Lift_Action; KeyFlag._Z_KeyFlag = 0;}
	if(KeyFlag._Z_Shift_KeyFlag && !IsKeyPress(_Z)){Engineer_Action.Lift_ActionGroup = Take_BigBox_Lift_Action; KeyFlag._Z_Shift_KeyFlag = 0;}
	if(KeyFlag._Z_Ctrl_KeyFlag && !IsKeyPress(_Z)){Engineer_Action.Lift_ActionGroup = Test_jl_Lift_Action; KeyFlag._Z_Ctrl_KeyFlag = 0;}

	if(KeyFlag._X_KeyFlag && !IsKeyPress(_X)){Engineer_Action.Rotate_ActionGroup = Rotate_Back_Start_Action; KeyFlag._X_KeyFlag = 0;}
	if(KeyFlag._X_Shift_KeyFlag && !IsKeyPress(_X)){Engineer_Action.Rotate_ActionGroup = Rotate_Top_Action; KeyFlag._X_Shift_KeyFlag = 0;}
	if(KeyFlag._X_Ctrl_KeyFlag && !IsKeyPress(_X)){Engineer_Action.Rotate_ActionGroup = Rotate_Hor_Action; KeyFlag._X_Ctrl_KeyFlag = 0;}

	if(KeyFlag._C_KeyFlag && !IsKeyPress(_C)){Engineer_Action.Extend_ActionGroup = Mini_Extension_Action; KeyFlag._C_KeyFlag = 0;}
	if(KeyFlag._C_Shift_KeyFlag && !IsKeyPress(_C)){Engineer_Action.Extend_ActionGroup = Second_Stage_Extension_Action; KeyFlag._C_Shift_KeyFlag = 0;}
	if(KeyFlag._C_Ctrl_KeyFlag && !IsKeyPress(_C)){Engineer_Action.Extend_ActionGroup = First_Stage_Extension_Action; KeyFlag._C_Ctrl_KeyFlag = 0;}
		
	if(KeyFlag._V_KeyFlag && !IsKeyPress(_V)){KeyFlag._V_KeyFlag = 0;}
	if(KeyFlag._V_KeyFlag && KeyFlag._Mouse_L_KeyFlag){Engineer_Auto.Auto_REBigBox_Start();KeyFlag._V_KeyFlag = 0;}
	if(KeyFlag._V_KeyFlag && KeyFlag._Mouse_R_KeyFlag){Engineer_Auto.Auto_TakeGroundBox_Start();KeyFlag._V_KeyFlag = 0;}
	if(KeyFlag._V_Shift_KeyFlag && !IsKeyPress(_V)){Engineer_Auto.Auto_RobBigBox_Start(); KeyFlag._V_Shift_KeyFlag = 0;}
	if(KeyFlag._V_Ctrl_KeyFlag && !IsKeyPress(_V)){Engineer_Auto.Auto_TakeSmallBox_Start(); KeyFlag._V_Ctrl_KeyFlag = 0;}
	
	if(KeyFlag._B_KeyFlag && !IsKeyPress(_B)){Engineer_Auto.Auto_ExchangeBox_Start(); KeyFlag._B_KeyFlag = 0;}
	if(KeyFlag._B_Shift_KeyFlag && !IsKeyPress(_B)){Engineer_Auto.Auto_ExchangeBox_Middle();KeyFlag._B_Shift_KeyFlag = 0;}
	if(KeyFlag._B_Ctrl_KeyFlag && !IsKeyPress(_B)){ KeyFlag._B_Ctrl_KeyFlag = 0;}
	
	if(KeyFlag._F_KeyFlag && !IsKeyPress(_F)){Engineer_Motor.Turn_Motor.Turn_Life();Engineer_Action.Turn_ActionGroup = Turn_to_QR_Action; KeyFlag._F_KeyFlag = 0;}
	if(KeyFlag_judge(_F) == SHIFT_ABC){Engineer_Action.Turn_ActionGroup = None_Action;Engineer_Motor.Turn_Motor.Turn_QR = 0;Engineer_Motor.Turn_Motor.Turn_to_QR(3);}
	if(KeyFlag_judge(_F) == CTRL_ABC){Engineer_Action.Turn_ActionGroup = None_Action;Engineer_Motor.Turn_Motor.Turn_QR = 0;Engineer_Motor.Turn_Motor.Turn_to_QR(1);}
	
	if(KeyFlag._G_KeyFlag && !IsKeyPress(_G)){Engineer_Action.Do_ETC_Action();KeyFlag._G_KeyFlag = 0;}
	if(KeyFlag._G_Ctrl_KeyFlag && !IsKeyPress(_G)){Engineer_Relay.Relay_Open();KeyFlag._G_Ctrl_KeyFlag = 0;}

		
	if(KeyFlag._E_KeyFlag && !IsKeyPress(_E)){Engineer_Action.Do_Pinch_Action();KeyFlag._E_KeyFlag = 0;}
	if(KeyFlag._E_Shift_KeyFlag && !IsKeyPress(_E)){KeyFlag._E_Shift_KeyFlag = 0;}
	if(KeyFlag._E_Ctrl_KeyFlag && !IsKeyPress(_E)){Engineer_Relay.Relay_Reset();KeyFlag._E_Ctrl_KeyFlag = 0;}

	if(KeyFlag._R_KeyFlag && !IsKeyPress(_R)){KeyFlag._R_KeyFlag = 0;}
	if(KeyFlag._R_Shift_KeyFlag && !IsKeyPress(_R)){Engineer_Action.Do_SuperRescue_Action();KeyFlag._R_Shift_KeyFlag = 0;}
	if(KeyFlag._R_Ctrl_KeyFlag && !IsKeyPress(_R)){Engineer_Action.Do_Rescue_Action();KeyFlag._R_Ctrl_KeyFlag = 0;}
	if(IsKeyPress(_R) && IsKeyPress(_CTRL) && IsKeyPress(_SHIFT)){SystemReset_flag = 1;}
	
	if(KeyFlag._Q_KeyFlag && !IsKeyPress(_Q)){KeyFlag._Q_KeyFlag = 0;}
	if(KeyFlag._Q_Shift_KeyFlag && !IsKeyPress(_Q)){Engineer_Auto.Auto_ExchangeAgain_Start(); KeyFlag._Q_Shift_KeyFlag = 0;}
	if(KeyFlag._Q_Ctrl_KeyFlag && !IsKeyPress(_Q)){Engineer_Action.Lift_ActionGroup = Vision_Lift_Action; KeyFlag._Q_Ctrl_KeyFlag = 0;}

	
	if(KeyFlag._Mouse_L_KeyFlag && !IsKeyPress(_Mouse_L)){Vision_DataPack.King = 1;KeyFlag._Mouse_L_KeyFlag = 0;}
	if(KeyFlag._Mouse_L_Shift_KeyFlag && !IsKeyPress(_Mouse_L)){Engineer_Action.Action_Init_Part();KeyFlag._Mouse_L_Shift_KeyFlag = 0;}
	if(KeyFlag._Mouse_L_Ctrl_KeyFlag && !IsKeyPress(_Mouse_L)){Engineer_Auto.Auto_Reset();Engineer_Action.Action_Init_All();Engineer_Box.Box_Num = None_Box;KeyFlag._Mouse_L_Ctrl_KeyFlag = 0;}
	
	if(KeyFlag._Mouse_R_KeyFlag && !IsKeyPress(_Mouse_R)){Vision_DataPack.King = 2;KeyFlag._Mouse_R_KeyFlag = 0;}
}

/**
* @brief  设置按键标志位函数.
* @param  void.
* @return void.
* @note  	根据按键判断设置对应标志位.
*/
void Set_KeyFlag()
{
	
	if(KeyFlag_judge(_Z) == ABC){KeyFlag._Z_KeyFlag = 1;}
	if(KeyFlag_judge(_Z) == SHIFT_ABC){KeyFlag._Z_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_Z) == CTRL_ABC){KeyFlag._Z_Ctrl_KeyFlag = 1;}

	if(KeyFlag_judge(_X) == ABC){KeyFlag._X_KeyFlag = 1;}
	if(KeyFlag_judge(_X) == SHIFT_ABC){KeyFlag._X_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_X) == CTRL_ABC){KeyFlag._X_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_C) == ABC){KeyFlag._C_KeyFlag = 1;}
	if(KeyFlag_judge(_C) == SHIFT_ABC){KeyFlag._C_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_C) == CTRL_ABC){KeyFlag._C_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_V) == ABC){KeyFlag._V_KeyFlag = 1;}
	if(KeyFlag_judge(_V) == SHIFT_ABC){KeyFlag._V_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_V) == CTRL_ABC){KeyFlag._V_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_B) == ABC){KeyFlag._B_KeyFlag = 1;}
	if(KeyFlag_judge(_B) == SHIFT_ABC){KeyFlag._B_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_B) == CTRL_ABC){KeyFlag._B_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_F) == ABC){KeyFlag._F_KeyFlag = 1;}
	if(KeyFlag_judge(_F) == SHIFT_ABC){KeyFlag._F_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_F) == CTRL_ABC){KeyFlag._F_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_G) == ABC){KeyFlag._G_KeyFlag = 1;}
	if(KeyFlag_judge(_G) == SHIFT_ABC){KeyFlag._G_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_G) == CTRL_ABC){KeyFlag._G_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_E) == ABC){KeyFlag._E_KeyFlag = 1;}
	if(KeyFlag_judge(_E) == SHIFT_ABC){KeyFlag._E_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_E) == CTRL_ABC){KeyFlag._E_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_R) == ABC){KeyFlag._R_KeyFlag = 1;}
	if(KeyFlag_judge(_R) == SHIFT_ABC){KeyFlag._R_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_R) == CTRL_ABC){KeyFlag._R_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_Q) == ABC){KeyFlag._Q_KeyFlag = 1;}
	if(KeyFlag_judge(_Q) == SHIFT_ABC){KeyFlag._Q_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_Q) == CTRL_ABC){KeyFlag._Q_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_Mouse_L) == ABC){KeyFlag._Mouse_L_KeyFlag = 1;}
	if(KeyFlag_judge(_Mouse_L) == SHIFT_ABC){KeyFlag._Mouse_L_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_Mouse_L) == CTRL_ABC){KeyFlag._Mouse_L_Ctrl_KeyFlag = 1;}
	
	if(KeyFlag_judge(_Mouse_R) == ABC){KeyFlag._Mouse_R_KeyFlag = 1;}
	if(KeyFlag_judge(_Mouse_R) == SHIFT_ABC){KeyFlag._Mouse_R_Shift_KeyFlag = 1;}
	if(KeyFlag_judge(_Mouse_R) == CTRL_ABC){KeyFlag._Mouse_R_Ctrl_KeyFlag = 1;}
}


/**
* @brief  按键标志位判断函数.
* @param  void.
* @return void.
* @note  	判断_/_SHIFT/_CTRL是否按下返回按键信息.
*/
KeyTypedef KeyFlag_judge(int key)
{
	if(IsKeyPress(key)&&IsKeyPress(_SHIFT)&&!IsKeyPress(_CTRL))
	{
		return SHIFT_ABC;
	}
	else if(IsKeyPress(key)&&!IsKeyPress(_SHIFT)&&IsKeyPress(_CTRL))
	{
		return CTRL_ABC;
	}
	else if(IsKeyPress(key)&&!IsKeyPress(_SHIFT)&&!IsKeyPress(_CTRL))
	{
		return ABC;
	}
	else
	{
		return None;
	}
}

/**
* @brief  单独按键判断函数.
* @param  _key	按键字符.
* @return void.
* @note  	通过板件通信判断按键是否按下.
*/
uint8_t IsKeyPress(int _key)
{
	switch(_key)
	{
		case _Z:
			return Key_DataPack.Key_Z_IsPress;
		case _X:
			return Key_DataPack.Key_X_IsPress;
		case _C:
			return Key_DataPack.Key_C_IsPress;
		case _V:
			return Key_DataPack.Key_V_IsPress;
		case _B:
			return Key_DataPack.Key_B_IsPress;
		case _F:
			return Key_DataPack.Key_F_IsPress;		
		case _G:
			return Key_DataPack.Key_G_IsPress;
		case _E:
			return Key_DataPack.Key_E_IsPress;
		case _R:
			return Key_DataPack.Key_R_IsPress;
		case _Q:
			return Key_DataPack.Key_Q_IsPress;
		case _CTRL:
			return Key_DataPack.Key_CTRL_IsPress;
		case _SHIFT:
			return Key_DataPack.Key_SHIFT_IsPress;
		case _Mouse_L:
			return Key_DataPack.Key_Mouse_L_IsPress;
		case _Mouse_R:
			return Key_DataPack.Key_Mouse_R_IsPress;
		default:
			return 100;
	}
}
