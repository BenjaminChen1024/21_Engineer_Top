/**
  ******************************************************************************
  * @file   : System_Datapool.h
  * @brief  : System_Datapool.cpp头文件
  ****************************************************************************** 
**/
#ifndef _SERVICE_COMMUNICATION_H_
#define _SERVICE_COMMUNICATION_H_
/* Includes ------------------------------------------------------------------*/
#include "System_Datapool.h"
/* Private variables ---------------------------------------------------------*/

/* 视觉数据包 --------------*/
#pragma pack(1)
struct Vision_DataPack_Typedef 
{
	uint8_t QR;
	uint8_t TakeBox;
	short ExtendBack;
	uint8_t King;
};
#pragma pack()
/* UI数据包 --------------*/
#pragma pack(1)
struct UI_DataPack_Typedef
{
	uint8_t LeftLift_PosPIDCurrent;
	uint8_t RightLift_PosPIDCurrent;
	uint8_t Engineer_BoxBox_Num;
	uint8_t Engineer_AutoAuto_Status_Judge;
	uint8_t Engineer_RelayRescue_Status;
	uint8_t Engineer_RelaySuperRescue_Status;
	uint8_t Engineer_RelayETC_Status;
	uint8_t Engineer_MotorTurn_MotorTurn_QR;
};
#pragma pack()
/* 按键数据包 --------------*/
#pragma pack(1)
struct Key_DataPack_Typedef
{
	uint8_t DR16_Status;
	uint8_t DR16_S2;
	uint8_t Key_Z_IsPress;
	uint8_t Key_X_IsPress;
	uint8_t Key_C_IsPress;
	uint8_t Key_V_IsPress;
	uint8_t Key_B_IsPress;
	uint8_t Key_F_IsPress;
	uint8_t Key_G_IsPress;
	uint8_t Key_E_IsPress;
	uint8_t Key_R_IsPress;
	uint8_t Key_Q_IsPress;
	uint8_t Key_CTRL_IsPress;
	uint8_t Key_SHIFT_IsPress;
	uint8_t	Key_Mouse_L_IsPress;
	uint8_t Key_Mouse_R_IsPress;
};
#pragma pack()

/* 按键类型 --------------*/
enum KeyTypedef
{
	None,
	ABC,
	SHIFT_ABC,
	CTRL_ABC,
	CTRL_SHIRT_ABC
};
/* 按键标志位 --------------*/
struct KeyFlag_Typedef
{
	bool _Z_KeyFlag;
	bool _Z_Shift_KeyFlag;
	bool _Z_Ctrl_KeyFlag;
	bool _X_KeyFlag;
	bool _X_Shift_KeyFlag;
	bool _X_Ctrl_KeyFlag;
	bool _C_KeyFlag;
	bool _C_Shift_KeyFlag;
	bool _C_Ctrl_KeyFlag;
	bool _V_KeyFlag;
	bool _V_Shift_KeyFlag;
	bool _V_Ctrl_KeyFlag;
	bool _B_KeyFlag;
	bool _B_Shift_KeyFlag;
	bool _B_Ctrl_KeyFlag;
	bool _F_KeyFlag;
	bool _F_Shift_KeyFlag;
	bool _F_Ctrl_KeyFlag;
	bool _G_KeyFlag;
	bool _G_Shift_KeyFlag;
	bool _G_Ctrl_KeyFlag;
	bool _E_KeyFlag;
	bool _E_Shift_KeyFlag;
	bool _E_Ctrl_KeyFlag;
	bool _R_KeyFlag;
	bool _R_Shift_KeyFlag;
	bool _R_Ctrl_KeyFlag;
	bool _Q_KeyFlag;
	bool _Q_Shift_KeyFlag;
	bool _Q_Ctrl_KeyFlag;
	bool _Mouse_L_KeyFlag;
	bool _Mouse_L_Shift_KeyFlag;
	bool _Mouse_L_Ctrl_KeyFlag;
	bool _Mouse_R_KeyFlag;
	bool _Mouse_R_Shift_KeyFlag;
	bool _Mouse_R_Ctrl_KeyFlag;
};
/* 数据包 --------------*/
extern Key_DataPack_Typedef	Key_DataPack;
extern Vision_DataPack_Typedef Vision_DataPack;
/* Private function declarations ---------------------------------------------*/
void UIMsgSend();
void Update_USART_Board(uint8_t *,uint8_t);
void Protect_Key_Control();
void Key_Control();
void Set_KeyFlag();
KeyTypedef KeyFlag_judge(int key);
uint8_t IsKeyPress(int _key);

#endif
