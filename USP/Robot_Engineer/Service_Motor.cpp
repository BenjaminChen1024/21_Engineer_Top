/**
  ******************************************************************************
  * @file   : Service_Motor.cpp
  * @brief  : �������ļ�
  ******************************************************************************
  * @note
  *  - 
**/

/* Includes ------------------------------------------------------------------*/
#include "Service_Motor.h"
#include "Motor.h"
/* Private variables ---------------------------------------------------------*/

/* ����� --------------*/
Motor_C610 LeftExtendMotor(1),RightExtendMotor(2);
Motor_C620 LeftRotateMotor(3),RightRotateMotor(4);
Motor_C620 LeftLiftMotor(5),RightLiftMotor(6);
Motor_C610 TurnMotor(7);
//Motor_C620 TurnMotor(7);
/* ���PID���� --------------*/
myPID MotorPID[20];

/* HAL Handlers --------------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
/* Private function prototypes -------------------------------------------------------*/

/*---------------------------------------------- Universal Motor Function --------------------------------------------*/

/**
* @brief  ������ݷ��ͺ���.
* @param  hcan	���ݷ���CAN��.
* @param  Motor_Msg	���������������.
* @param  StdID	���ID.
* @return void.
* @note  	None.
*/
void Motor_Classdef::MotorMsgSend(CAN_HandleTypeDef *hcan,int16_t Motor_Msg[],int StdID)
{
	uint32_t mailbox;
	uint8_t Tx_Data[8];
	CAN_TxHeaderTypeDef CAN_TxHeader;	
	CAN_TxHeader.IDE=CAN_ID_STD;
	CAN_TxHeader.StdId=StdID;
	CAN_TxHeader.RTR=CAN_RTR_DATA;
	CAN_TxHeader.DLC=8;
	Tx_Data[0]=Motor_Msg[0] >> 8;
	Tx_Data[1]=Motor_Msg[0];
	Tx_Data[2]=Motor_Msg[1] >> 8;
	Tx_Data[3]=Motor_Msg[1];
	Tx_Data[4]=Motor_Msg[2] >> 8;
	Tx_Data[5]=Motor_Msg[2];
	Tx_Data[6]=Motor_Msg[3] >> 8;
	Tx_Data[7]=Motor_Msg[3];
	HAL_CAN_AddTxMessage(hcan,&CAN_TxHeader,(uint8_t *)Tx_Data,&mailbox);	
}

/**
* @brief  ����������ݸ��º���.
* @param  msg_rece	���ݰ�.
* @param  Motor_ID	���ID.
* @return void.
* @note  	None.
*/
void Motor_Classdef::Update_Motor(uint8_t *msg_rece,uint32_t Motor_ID)
{
	switch(Motor_ID)
	{
		case LeftExtendMotor_ID:
			LeftExtendMotor.update(msg_rece);
			LeftExtend_PosPID.Current=LeftExtendMotor.total_encoder + Extend_Motor.LeftExtend_ZeroOffset;
			LeftExtend_SpdPID.Current=LeftExtendMotor.getSpeed();
			Extend_Motor.LeftExtend_Torque = LeftExtendMotor.getTorque();
			break;
		case RightExtendMotor_ID:
			RightExtendMotor.update(msg_rece);
			RightExtend_PosPID.Current=RightExtendMotor.total_encoder + Extend_Motor.RightExtend_ZeroOffset;
			RightExtend_SpdPID.Current=RightExtendMotor.getSpeed();
			Extend_Motor.RightExtend_Torque = RightExtendMotor.getTorque();
			break;
		case LeftRotateMotor_ID:
			LeftRotateMotor.update(msg_rece);
			LeftRotate_PosPID.Current=LeftRotateMotor.total_encoder + Rotate_Motor.LeftRotato_ZeroOffset;
			LeftRotate_SpdPID.Current=LeftRotateMotor.getSpeed();
			Rotate_Motor.LeftRotate_Torque = LeftRotateMotor.getGivenCurrent();
			Rotate_Motor.LeftRotate_rpm = (short)((unsigned char)msg_rece[2]<<8|(unsigned char)msg_rece[3]);	
			break;
		case RightRotateMotor_ID:
			RightRotateMotor.update(msg_rece);
			RightRotate_PosPID.Current=RightRotateMotor.total_encoder + Rotate_Motor.RightRotato_ZeroOffset;
			RightRotate_SpdPID.Current=RightRotateMotor.getSpeed();
			Rotate_Motor.RightRotate_Torque = RightRotateMotor.getGivenCurrent();
			Rotate_Motor.RightRotate_rpm = (short)((unsigned char)msg_rece[2]<<8|(unsigned char)msg_rece[3]);	
			break;			
		case LeftLiftMotor_ID:
			LeftLiftMotor.update(msg_rece);
			LeftLift_PosPID.Current=LeftLiftMotor.total_encoder + Lift_Motor.LeftLift_ZeroOffset;
			LeftLift_SpdPID.Current=LeftLiftMotor.getSpeed();
			Lift_Motor.LeftLift_Torque = LeftLiftMotor.getGivenCurrent();
			break;
		case RightLiftMotor_ID:
			RightLiftMotor.update(msg_rece);
			RightLift_PosPID.Current=RightLiftMotor.total_encoder + Lift_Motor.RightLift_ZeroOffset;
			RightLift_SpdPID.Current=RightLiftMotor.getSpeed();
			Lift_Motor.RightLift_Torque = RightLiftMotor.getGivenCurrent();
			break;
		case TurnMotor_ID:
			TurnMotor.update(msg_rece);
			Turn_PosPID.Current=TurnMotor.total_encoder;
			Turn_SpdPID.Current=TurnMotor.getSpeed();
			Turn_Motor.Turn_Torque = TurnMotor.getTorque();
//			Turn_Torque = TurnMotor.getGivenCurrent();
			break;
		default:
			break;
	}
}

/**
* @brief  ���PID��ʼ��.
* @param  void.
* @return void.
* @note  	����λ�û��ٶȻ�PID.
*/
void Motor_Classdef::MotorPIDInit()
{
	/* PID��ʱ����ʼ�� --------------*/
	myPIDTimer::getMicroTick_regist(Get_SystemTimer);
	/* Rotate Motor PID Config */
	LeftRotate_PosPID.SetPIDParam(0.3f,0.0f,0.0f,1000.0f,10000.0f);
	RightRotate_PosPID.SetPIDParam(0.3f,0.0f,0.0f,1000.0f,10000.0f);
	LeftRotate_SpdPID.SetPIDParam(18.0f,0.0f,0.0f,10000.0f,10000.0f);
	RightRotate_SpdPID.SetPIDParam(18.0f,0.0f,0.0f,10000.0f,10000.0f);
	/* Extend Motor PID Config */
	LeftExtend_PosPID.SetPIDParam(0.3f,0.0f,0.0f,1000.0f,10000.0f);
	RightExtend_PosPID.SetPIDParam(0.3f,0.0f,0.0f,1000.0f,10000.0f);
	LeftExtend_SpdPID.SetPIDParam(8.0f,0.0f,0.0f,10000.0f,10000.0f);
	RightExtend_SpdPID.SetPIDParam(8.0f,0.0f,0.0f,10000.0f,10000.0f);
	/* Lift Motor PID Config */
	LeftLift_PosPID.SetPIDParam(0.4f,0.0f,0.0f,1000.0f,10000.0f);
	RightLift_PosPID.SetPIDParam(0.4f,0.0f,0.0f,1000.0f,10000.0f);
	LeftLift_SpdPID.SetPIDParam(8.0f,0.0f,0.0f,10000.0f,10000.0f);
	RightLift_SpdPID.SetPIDParam(8.0f,0.0f,0.0f,10000.0f,10000.0f);
	/* Turn Motor PID Config */
	Turn_PosPID.SetPIDParam(0.3f,0.0f,0.0f,1000.0f,7000.0f);
	Turn_SpdPID.SetPIDParam(5.0f,0.0f,0.0f,10000.0f,10000.0f);
}

/**
* @brief  ���PID���ƺ���.
* @param  void.
* @return void.
* @note  	����λ�û�PID�������ٶȻ�Ŀ��ֵ�������ٶȻ�PID.
*/
void Motor_Classdef::MotorPID_Control(void)
{
	/* Rotate PID Control */
	LeftRotate_PosPID.Adjust();
	RightRotate_PosPID.Adjust();
	LeftRotate_SpdPID.Target = LeftRotate_PosPID.Out;
	RightRotate_SpdPID.Target = RightRotate_PosPID.Out;
	LeftRotate_SpdPID.Adjust();
	RightRotate_SpdPID.Adjust();
	/* Extend PID Control */
	LeftExtend_PosPID.Adjust();
	RightExtend_PosPID.Adjust();
	LeftExtend_SpdPID.Target = LeftExtend_PosPID.Out;
	RightExtend_SpdPID.Target = RightExtend_PosPID.Out;
	LeftExtend_SpdPID.Adjust();
	RightExtend_SpdPID.Adjust();	
	/* Lift PID Control */
	LeftLift_PosPID.Adjust();
	RightLift_PosPID.Adjust();
	LeftLift_SpdPID.Target = LeftLift_PosPID.Out;
	RightLift_SpdPID.Target = RightLift_PosPID.Out;
	LeftLift_SpdPID.Adjust();
	RightLift_SpdPID.Adjust();	
	/* Turn PID Control */
	Turn_PosPID.Adjust();
	Turn_SpdPID.Target = Turn_PosPID.Out;
	Turn_SpdPID.Adjust();
}

/**
* @brief  ������ƺ���.
* @param  void.
* @return void.
* @note  	����PID�����͵������.
*/
void Motor_Classdef::Motor_Control()
{
		int16_t MotorMsg[4];
	/* ���PID���� --------------*/
		MotorPID_Control();	
	/* ����0x200������� --------------*/
		MotorMsg[0] = LeftExtend_SpdPID.Out;
		MotorMsg[1] = RightExtend_SpdPID.Out;
		MotorMsg[2] = LeftRotate_SpdPID.Out;
		MotorMsg[3] = RightRotate_SpdPID.Out;		
		MotorMsgSend(&hcan2,MotorMsg,0x200);
	/* ����0x1ff������� --------------*/
		MotorMsg[0] = LeftLift_SpdPID.Out;
		MotorMsg[1] = RightLift_SpdPID.Out;
		MotorMsg[2] = Turn_SpdPID.Out;
		MotorMsg[3] = 0;
		MotorMsgSend(&hcan2,MotorMsg,0x1ff); 
}

/*---------------------------------------------- Rotate Motor Function --------------------------------------------*/

/**
* @brief  ��ת��������Լ캯��.
* @param  void.
* @return POSTtypedef	����Լ�״̬.
* @note  	None.
*/
POSTtypedef Rotate_Motor_Classdef::Rotate_POST()
{
	LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target - 150.0f, - ( Rotate_Pos_Limit + 20000), Rotate_Pos_Limit + 20000);
	RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target + 150.0f, - ( Rotate_Pos_Limit + 20000), Rotate_Pos_Limit + 20000);
	if(LeftRotate_Torque < -8000 || RightRotate_Torque > 8000)
	{
		LeftRotato_ZeroOffset = - LeftRotateMotor.total_encoder;
		RightRotato_ZeroOffset = - RightRotateMotor.total_encoder;
		LeftRotate_PosPID.Target = 0.0f;
		RightRotate_PosPID.Target = 0.0f;
		return Rotate_POST_OK;
	}
}

/**
* @brief  ���ɷ�ת����.
* @param  pos	DR16���Ʊ���.
* @return void.
* @note  	���ֱ����Ʒ�ת.
*/
void Rotate_Motor_Classdef::Rotate_to_Pos(float pos)
{
	if(pos != 0)
	{
		LeftRotate_PosPID.Target = myConstrain( LeftRotate_PosPID.Target + 100.0f*pos, -Rotate_Pos_Limit, Rotate_Pos_Limit);
		RightRotate_PosPID.Target = myConstrain( RightRotate_PosPID.Target - 100.0f*pos, -Rotate_Pos_Limit, Rotate_Pos_Limit);
	}
}

/**
* @brief  ��ת����.
* @param  float ��תλ��.
* @param  float ��ת����λ��.
* @param  float ��ת�ٶȣ����Ǿ����ٶȣ���Ҫ���Σ�.
* @param  float ��ת�����ٶ�.
* @return void.
* @note  	����ָ����ת�ٶȷ�ת��ָ��λ��.
*/
void Rotate_Motor_Classdef::Rotate_Step(float Pos, float Pos_Middle, float Speed, float Buffer_Speed)
{
	Left_StartAngle = LeftRotate_PosPID.Current;
	Right_StartAngle = RightRotate_PosPID.Current;
	
	if(Left_StartAngle < Pos || Right_StartAngle > -Pos)
	{
		if(Left_StartAngle <= Pos_Middle || Right_StartAngle >= -Pos_Middle)
		{
			LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target + Speed,0.0f,Pos);
			RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target - Speed,-Pos,0.0f);
		}
		else
		{
			LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target + (Speed - Buffer_Speed),0.0f,Pos);
			RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target - (Speed - Buffer_Speed),-Pos,0.0f);
		}
	}
	else
	{
			LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target - Speed,Pos, Rotate_Pos_Limit);
			RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target + Speed, -Rotate_Pos_Limit, -Pos);
	}
}
/* ��ת��ߵ㺯�� --------------*/
void Rotate_Motor_Classdef::Rotate_Top()
{
	Rotate_Step(Rotate_Pos_Top, Rotate_Pos_Top_Middle, Rotate_Speed, Rotate_Buffer_Speed);
}
/* ��תС��㺯�� --------------*/
void Rotate_Motor_Classdef::Rotate_SmallBox()
{
	Rotate_Step(Rotate_Pos_SmallBox, Rotate_Pos_SmallBox_Middle, Rotate_Speed, Rotate_Buffer_Speed);
}
/* ��ת�һ��㺯�� --------------*/
void Rotate_Motor_Classdef::Rotate_Exchange()
{
	Rotate_Step(Rotate_Pos_Exchange, Rotate_Pos_Exchange_Middle, Rotate_Speed, Rotate_Buffer_Speed);
}
/* ��ת�ٴζһ��㺯�� --------------*/
void Rotate_Motor_Classdef::Rotate_ExchangeAgain()
{
	Rotate_Step(Rotate_Pos_ExchangeAgain, Rotate_Pos_ExchangeAgain_Middle, Rotate_Speed, Rotate_Buffer_Speed);
}
/* ��תˮƽ�Ƴ����� --------------*/
void Rotate_Motor_Classdef::Rotate_Push()
{
	Rotate_Step(Rotate_Pos_Push, Rotate_Pos_Push_Middle, Rotate_Speed, Rotate_Buffer_Speed);
}
/* ��תˮƽ���� --------------*/
void Rotate_Motor_Classdef::Rotate_Hor()
{
	Rotate_Step(Rotate_Pos_Hor, Rotate_Pos_Hor_Middle, Rotate_Speed, Rotate_Buffer_Speed);
}
/* ��ת���޺��� --------------*/
void Rotate_Motor_Classdef::Rotate_Limit()
{
	Rotate_Step(Rotate_Pos_Limit, Rotate_Pos_Limit_Middle, Rotate_Speed, Rotate_Buffer_Speed);
}

/**
* @brief  ��ת�ջ�ԭ�㺯��.
* @param  void.
* @return void.
* @note  	��ת�ջص�ԭ��λ�ã����٣�.
*/
void Rotate_Motor_Classdef::Rotate_Back_Start()
{
	Left_StartAngle = LeftRotate_PosPID.Current;
	Right_StartAngle = RightRotate_PosPID.Current;
	if(Left_StartAngle < Rotate_Pos_Start || Right_StartAngle > -Rotate_Pos_Start)
	{
		LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target + (Rotate_Speed - Rotate_Buffer_Speed), Rotate_Pos_Start, Rotate_Pos_Start);
		RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target - (Rotate_Speed - Rotate_Buffer_Speed), -Rotate_Pos_Start, -Rotate_Pos_Start);
	}
	else
	{
		if(Left_StartAngle < Rotate_Back_Start_Middle || Right_StartAngle > -Rotate_Back_Start_Middle)
		{
			LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target - (Rotate_Speed - Rotate_Buffer_Speed),Rotate_Pos_Start, Rotate_Pos_Limit);
			RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target + (Rotate_Speed - Rotate_Buffer_Speed), -Rotate_Pos_Limit, -Rotate_Pos_Start);
		}
		else
		{
			LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target - Rotate_Speed,Rotate_Pos_Start, Rotate_Pos_Limit);
			RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target + Rotate_Speed, -Rotate_Pos_Limit, -Rotate_Pos_Start);
		}
	}
}

/* �ջط�ת��ߵ㺯�� --------------*/
void Rotate_Motor_Classdef::Rotate_Topper()
{	
	Left_StartAngle = LeftRotate_PosPID.Current;
	Right_StartAngle = RightRotate_PosPID.Current;
	if(Left_StartAngle < Rotate_Pos_Topper || Right_StartAngle > -Rotate_Pos_Topper)
	{
		LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target + Rotate_Buffer_Speed, Rotate_Pos_Topper, Rotate_Pos_Topper);
		RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target - Rotate_Buffer_Speed, -Rotate_Pos_Topper, -Rotate_Pos_Topper);
	}
	else
	{
			LeftRotate_PosPID.Target = myConstrain(LeftRotate_PosPID.Target - Rotate_Buffer_Speed,Rotate_Pos_Topper, Rotate_Pos_Limit);
			RightRotate_PosPID.Target = myConstrain(RightRotate_PosPID.Target + Rotate_Buffer_Speed, -Rotate_Pos_Limit, -Rotate_Pos_Topper);
	}
}

/* ��תֹͣ���� --------------*/
void Rotate_Motor_Classdef::Rotate_Stop()
{
	LeftRotate_PosPID.Target = LeftRotate_PosPID.Current;
	RightRotate_PosPID.Target = RightRotate_PosPID.Current;
}

/*---------------------------------------------- Rotate Judge Function --------------------------------------------*/

/**
* @brief  ��ת�жϺ���.
* @param  float ��תλ��.
* @return bool �жϱ�־λ.
* @note  	��������Χ���ж��Ƿ�ת��ָ��λ��.
*/
bool Rotate_Motor_Classdef::Rotate_Judge(float Pos)
{
	return (abs(LeftRotate_PosPID.Current - Pos) <= DeathZone_Limit && abs(RightRotate_PosPID.Current + Pos) <= DeathZone_Limit);
}
bool Rotate_Motor_Classdef::Rotate_Start_Judge() {return Rotate_Judge(Rotate_Pos_Start);}
bool Rotate_Motor_Classdef::Rotate_Topper_Judge() {return Rotate_Judge(Rotate_Pos_Topper);}
bool Rotate_Motor_Classdef::Rotate_Top_Judge() {return Rotate_Judge(Rotate_Pos_Top);}
bool Rotate_Motor_Classdef::Rotate_SmallBox_Judge() {return Rotate_Judge(Rotate_Pos_SmallBox);}
bool Rotate_Motor_Classdef::Rotate_Exchange_Judge() {return Rotate_Judge(Rotate_Pos_Exchange);}
bool Rotate_Motor_Classdef::Rotate_ExchangeAgain_Judge() {return Rotate_Judge(Rotate_Pos_ExchangeAgain);}
bool Rotate_Motor_Classdef::Rotate_Push_Judge() {return Rotate_Judge(Rotate_Pos_Push);}
bool Rotate_Motor_Classdef::Rotate_Hor_Judge() {return Rotate_Judge(Rotate_Pos_Hor);}
bool Rotate_Motor_Classdef::Rotate_Limit_Judge(){return Rotate_Judge(Rotate_Pos_Limit);}

/*---------------------------------------------- Extend Motor Function --------------------------------------------*/

/**
* @brief  ��������Լ캯��.
* @param  void.
* @return POSTtypedef	����Լ�״̬.
* @note  	None.
*/
POSTtypedef Extend_Motor_Classdef::Extend_POST()
{
	LeftExtend_PosPID.Target = myConstrain(LeftExtend_PosPID.Target - 600.0f, -(Extension_Pos_Limit + 500000), (Extension_Pos_Limit + 500000));
	RightExtend_PosPID.Target = myConstrain(RightExtend_PosPID.Target + 600.0f, -(Extension_Pos_Limit + 500000), (Extension_Pos_Limit + 500000));

	if(LeftExtend_Torque < -8000 || RightExtend_Torque > 8000)
	{
		LeftExtend_ZeroOffset = - LeftExtendMotor.total_encoder;
		RightExtend_ZeroOffset = - RightExtendMotor.total_encoder;
		LeftExtend_PosPID.Target = 0.0f;
		RightExtend_PosPID.Target = 0.0f;
		return Extend_POST_OK;
	}
}

/**
* @brief  �����������.
* @param  pos	DR16���Ʊ���.
* @return void.
* @note  	���ֱ��������.
*					-	5000Ϊ����ٶȿ��Ʋ������ɵ���
*					-	��ΧΪ������λ����������λ��֮��
*/
void Extend_Motor_Classdef::Extend_to_Pos(float pos)
{
	LeftExtend_StartPos = LeftExtend_PosPID.Current;
	RightExtend_StartPos = RightExtend_PosPID.Current;
	if(pos != 0)
	{
//		LeftExtend_PosPID.Target = myConstrain( LeftExtend_StartPos + 30000.0f*pos, None_Extension_Pos, Second_Extension_Pos);
//		RightExtend_PosPID.Target = myConstrain( RightExtend_StartPos - 30000.0f*pos, -Second_Extension_Pos, -None_Extension_Pos);
		
		LeftExtend_PosPID.Target = myConstrain( LeftExtend_StartPos + 30000.0f*pos, -Second_Extension_Pos, Second_Extension_Pos);
		RightExtend_PosPID.Target = myConstrain( RightExtend_StartPos - 30000.0f*pos, -Second_Extension_Pos, Second_Extension_Pos);
	}
}

/**
* @brief  �����������.
* @param  uint8_t ���Ʊ�־λ.
* @return void.
* @note  	����տ��Ʊ�־λ��������.
*/
bool Extend_Motor_Classdef::Extend_Adjust(uint8_t sign)
{
	LeftExtend_StartPos = LeftExtend_PosPID.Current;
	RightExtend_StartPos = RightExtend_PosPID.Current;
	switch(sign)
	{
		case 0:
			return false;
		case 1:
			LeftExtend_PosPID.Target = myConstrain(LeftExtend_StartPos + 5000.0f , 0.0f , Second_Extension_Pos);
			RightExtend_PosPID.Target = myConstrain(RightExtend_StartPos - 5000.0f, -Second_Extension_Pos , 0.0f);
			return false;
		case 2:
			return true;
		case 3:
			LeftExtend_PosPID.Target = myConstrain(LeftExtend_StartPos - 5000.0f , Second_Extension_Pos , Extension_Pos_Limit);
			RightExtend_PosPID.Target = myConstrain(RightExtend_StartPos + 5000.0f, -Extension_Pos_Limit , -Second_Extension_Pos );
			return false;
		default:
			return false;
	}
}

/**
* @brief  �������.
* @param  float ���λ��.
* @param  float ����ٶ�.
* @param  float ����ջ��ٶ�.
* @return void.
* @note  	����ָ������ٶ������ָ��λ��.
*/
void Extend_Motor_Classdef::Extend_Step(float Pos, float OUT_Speed, float IN_Speed)
{	
	LeftExtend_StartPos = LeftExtend_PosPID.Current;
	RightExtend_StartPos = RightExtend_PosPID.Current;
	if(LeftExtend_StartPos < Pos || RightExtend_StartPos > -Pos)
	{
		LeftExtend_PosPID.Target = myConstrain(LeftExtend_StartPos + OUT_Speed, 0.0f , Pos);
		RightExtend_PosPID.Target = myConstrain(RightExtend_StartPos - OUT_Speed, -Pos , 0.0f);
	}
	else
	{
		LeftExtend_PosPID.Target = myConstrain(LeftExtend_StartPos - IN_Speed, Pos , Extension_Pos_Limit);
		RightExtend_PosPID.Target = myConstrain(RightExtend_StartPos + IN_Speed, -Extension_Pos_Limit , -Pos );
	}
}
/* ����������� --------------*/
void Extend_Motor_Classdef::Negative_Extension()
{	
	Extend_Step(Negative_Extension_Pos, 3000.0f, 15000.0f);
}
/* ���������� --------------*/
void Extend_Motor_Classdef::None_Extension()
{	
	Extend_Step(None_Extension_Pos, 3000.0f, 25000.0f);
}
/* ΢С������� --------------*/
void Extend_Motor_Classdef::Mini_Extension()
{	
	Extend_Step(Mini_Extension_Pos, 15000.0f, 25000.0f);
}
/* һ��������� --------------*/
void Extend_Motor_Classdef::First_Stage_Extension()
{
	Extend_Step(First_Extension_Pos, 25000.0f, 25000.0f);
}
/* ����������� --------------*/
void Extend_Motor_Classdef::Second_Stage_Extension()
{
	Extend_Step(Second_Extension_Pos, 30000.0f, 30000.0f);
}
/* ����������� --------------*/
void Extend_Motor_Classdef::Third_Stage_Extension()
{
	Extend_Step(Third_Extension_Pos, 30000.0f, 30000.0f);
}
/* ���ֹͣ���� --------------*/
void Extend_Motor_Classdef::Extend_Stop()
{
	LeftExtend_PosPID.Target = LeftExtend_PosPID.Current;
	RightExtend_PosPID.Target = RightExtend_PosPID.Current;
}

/*---------------------------------------------- Extend Judge Function --------------------------------------------*/
/**
* @brief  ����жϺ���.
* @param  float ���λ��.
* @return bool �жϱ�־λ.
* @note  	��������Χ���ж��Ƿ������ָ��λ��.
*/
bool Extend_Motor_Classdef::Extend_Judge(float Pos)
{
	return (abs(LeftExtend_PosPID.Current - Pos) <= DeathZone_Limit && abs(RightExtend_PosPID.Current + Pos) <= DeathZone_Limit);
}
bool Extend_Motor_Classdef::Extend_Negative_Judge() {return Extend_Judge(Negative_Extension_Pos);}
bool Extend_Motor_Classdef::Extend_None_Judge() {return Extend_Judge(None_Extension_Pos);}
bool Extend_Motor_Classdef::Extend_Mini_Judge() {return Extend_Judge(Mini_Extension_Pos);}
bool Extend_Motor_Classdef::Extend_First_Judge() {return Extend_Judge(First_Extension_Pos);}
bool Extend_Motor_Classdef::Extend_Second_Judge() {return Extend_Judge(Second_Extension_Pos);}
bool Extend_Motor_Classdef::Extend_Third_Judge() {return Extend_Judge(Third_Extension_Pos);}

/*---------------------------------------------- Lift Motor Function --------------------------------------------*/

uint64_t abc_flag;
/**
* @brief  ̧�������Լ캯��.
* @param  void.
* @return POSTtypedef	����Լ�״̬.
* @note  	None.
*/
POSTtypedef Lift_Motor_Classdef::Lift_POST()
{	
	if(Lift_POST_Sensor_flag)
	{
		Engineer_Sensor.PR_Updata();
		if(Engineer_Sensor.PR_F1_Status || Engineer_Sensor.PR_F2_Status)
		{
			Lift_POST_move_flag = 1;
		}
		else
		{
			Lift_POST_move_flag = 2;
		}
		Lift_POST_Sensor_flag = 0;
	}
	
	switch(Lift_POST_move_flag)
	{
		case 1:
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + 100.0f, - (Third_Lift_Pos + 600000), (Third_Lift_Pos + 600000));
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + 100.0f, - (Third_Lift_Pos + 600000), (Third_Lift_Pos + 600000));
			Engineer_Sensor.PR_Updata();
			if(!(Engineer_Sensor.PR_F1_Status || Engineer_Sensor.PR_F2_Status))
			{
				Lift_Death();
				Lift_POST_flag = 1;
				Lift_POST_move_flag = 0;
			}
			break;
		case 2:
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - 200.0f, - (Third_Lift_Pos + 600000), (Third_Lift_Pos + 600000));
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - 200.0f, - (Third_Lift_Pos + 600000), (Third_Lift_Pos + 600000));
			Lift_POST_Sensor_flag = 1;
			Lift_POST_move_flag = 0;
			break;
		default:
			break;
	}
	if(Lift_POST_flag)
	{
		Lift_POST_Sensor_flag = 0;
		Lift_POST_move_flag = 0;
		Lift_POST_Time ++;
		if(Lift_POST_Time >= 400)
		{
			xTaskNotify(TopPOST_Handle, (uint32_t)NULL, eNoAction);
			return Lift_POST_OK;
		}
	}
}
void Lift_Motor_Classdef::Lift_POST_Reset()
{
		LeftLift_ZeroOffset = - LeftLiftMotor.total_encoder;
		RightLift_ZeroOffset = - RightLiftMotor.total_encoder;
		LeftLift_PosPID.Target = 0.0f;
		RightLift_PosPID.Target = 0.0f;
		if(Lift_Judge(0.0) && LeftLift_PosPID.Target == 0 && RightLift_PosPID.Target == 0)
		{
			abc_flag++;
			Lift_Life();
			Lift_POST_Time = 0;
			Lift_POST_flag = 0;
		}
}
/**
* @brief  ����̧������.
* @param  pos	DR16���Ʊ���.
* @return void.
* @note  	���ֱ�����̧��.
*					-	5000Ϊ̧���ٶȿ��Ʋ������ɵ���
*					-	��ΧΪ���̧��λ�������̧��λ��֮��
*/
void Lift_Motor_Classdef::Lift_to_Pos(uint8_t site, float pos)
{
	switch(site)
	{
		case 0:
			if(pos != 0)
			{
				LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + 1000.0f*pos, - Lift_Pos_Limit, Lift_Pos_Limit);
				RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + 1000.0f*pos, - Lift_Pos_Limit, Lift_Pos_Limit);
			}
			break;
		case 1:
			if(pos != 0)
			{
				LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + 1000.0f*pos, - Lift_Pos_Limit, Lift_Pos_Limit);
			}
			break;
		case 2:
			if(pos != 0)
			{
				RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + 1000.0f*pos, - Lift_Pos_Limit, Lift_Pos_Limit);
			}
			break;
		default:
			break;
	}
}

/**
* @brief  ̧����������.
* @param  site	λ�ñ�־λ.
* @param  flag	���Ʊ�־λ.
* @return void.
* @note  	̧���ܿ��Ʊ�־λ�����߶�.
*					site��
*								0:˫�ߵ��	1:��ߵ��	2:�ұߵ��
*					flag:
*								0:�޲���	1:̧��		2����������		3���½�
*/
bool Lift_Motor_Classdef::Lift_Adjust(uint8_t site, uint8_t flag)
{
	switch(site)
	{
		case 0:
			switch(flag)
			{
				case 0:
					return false;
				case 1:
					LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + 0.1f * ULift_Speed, - Third_Lift_Pos, Third_Lift_Pos);
					RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + 0.1f * ULift_Speed, -Third_Lift_Pos, Third_Lift_Pos);
					return false;
				case 2:
					return true;
				case 3:
					LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - 0.1f * ULift_Speed, -Third_Lift_Pos, Third_Lift_Pos);
					RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - 0.1f * ULift_Speed, -Third_Lift_Pos, Third_Lift_Pos);
					return false;
				default:
					return false;
			}
			break;
		case 1:
			switch(flag)
			{
				case 0:
					return false;
				case 1:
					LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + 0.1f * ULift_Speed, - Third_Lift_Pos, Third_Lift_Pos);
					return false;
				case 2:
					return true;
				case 3:
					LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - 0.1f * ULift_Speed, -Third_Lift_Pos, Third_Lift_Pos);
					return false;
				default:
					return false;
			}
			break;
		case 2:
			switch(flag)
			{
				case 0:
					return false;
				case 1:
					RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + 0.1f * ULift_Speed, -Third_Lift_Pos, Third_Lift_Pos);
					return false;
				case 2:
					return true;
				case 3:
					RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - 0.1f * ULift_Speed, -Third_Lift_Pos, Third_Lift_Pos);
					return false;
				default:
					return false;
			}
			break;
		default:
			return false;
	}
}

/**
* @brief  ����̧������.
* @param  float Test_Pos ��������ֵ.
* @return void.
* @note  	̧��С�ξ��뱣������.
*/
void Lift_Motor_Classdef::Test_Lift(float Test_Pos, float Uspeed, float Dspeed)
{
	float Pos = myConstrain(Test_Pos, None_Lift_Pos, Third_Lift_Pos);
	
	if(LeftLift_PosPID.Target <= Pos || RightLift_PosPID.Target <= Pos)
	{
		LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + Uspeed, None_Lift_Pos, Pos);
		RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + Uspeed, None_Lift_Pos, Pos);
	}
	else
	{
		LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - Dspeed, Pos, Lift_Pos_Limit);
		RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - Dspeed, Pos, Lift_Pos_Limit);
	}
}

/**
* @brief  ����̧������.
* @param  void.
* @return void.
* @note  	̧��С�ξ��뱣������.
*/
void Lift_Motor_Classdef::Negative_Lift()
{
	
	if(LeftLift_PosPID.Target <= Negative_Lift_Pos || RightLift_PosPID.Target <= Negative_Lift_Pos)
	{
		LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + DLift_Speed, 0.0f, Negative_Lift_Pos);
		RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + DLift_Speed, 0.0f, Negative_Lift_Pos);
	}
	else
	{
		if(LeftLift_PosPID.Target <= Lift_Buffer_Zone || RightLift_PosPID.Target <= Lift_Buffer_Zone)
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - DLift_Buffer_Speed, Negative_Lift_Pos, Lift_Pos_Limit);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - DLift_Buffer_Speed, Negative_Lift_Pos, Lift_Pos_Limit);
		}
		else
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - DLift_Speed, Negative_Lift_Pos, Lift_Pos_Limit);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - DLift_Speed, Negative_Lift_Pos, Lift_Pos_Limit);
		}
	}
}

/**
* @brief  ���̧������.
* @param  void.
* @return void.
* @note  	̧��С�ξ��뱣������.
*/
void Lift_Motor_Classdef::None_Lift()
{
	
	if(LeftLift_PosPID.Target <= None_Lift_Pos || RightLift_PosPID.Target <= None_Lift_Pos)
	{
		LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + 0.4f * DLift_Speed, 0.0f, None_Lift_Pos);
		RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + 0.4f * DLift_Speed, 0.0f, None_Lift_Pos);
	}
	else
	{
		if(LeftLift_PosPID.Target <= Lift_Buffer_Zone || RightLift_PosPID.Target <= Lift_Buffer_Zone)
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - DLift_Buffer_Speed, None_Lift_Pos, Lift_Pos_Limit);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - DLift_Buffer_Speed, None_Lift_Pos, Lift_Pos_Limit);
		}
		else
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - DLift_Speed, None_Lift_Pos, Lift_Pos_Limit);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - DLift_Speed, None_Lift_Pos, Lift_Pos_Limit);
		}
	}
}

/**
* @brief  ̧������.
* @param  float ̧��λ��.
* @param  float ̧���ٶ�.
* @param  float ̧�������ٶ�.
* @return void.
* @note  	����ָ��̧���ٶ�̧����ָ��λ��.
*/
void Lift_Motor_Classdef::Step_Lift(float Pos, float Speed, float Buffer_Speed)
{
	if(LeftLift_PosPID.Target <= Pos || RightLift_PosPID.Target <= Pos)
	{
		if(LeftLift_PosPID.Target <= Lift_Buffer_Zone || RightLift_PosPID.Target <= Lift_Buffer_Zone)
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + Buffer_Speed, 0.0f, Pos);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + Buffer_Speed, 0.0f, Pos);
		}
		else
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target + Speed, 0.0f, Pos);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target + Speed, 0.0f, Pos);
		}
	}
	else
	{
		if(LeftLift_PosPID.Target <= Lift_Buffer_Zone || RightLift_PosPID.Target <= Lift_Buffer_Zone)
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - DLift_Buffer_Speed, Pos, Lift_Pos_Limit);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - DLift_Buffer_Speed, Pos, Lift_Pos_Limit);
		}
		else
		{
			LeftLift_PosPID.Target = myConstrain( LeftLift_PosPID.Target - DLift_Speed, Pos, Lift_Pos_Limit);
			RightLift_PosPID.Target = myConstrain( RightLift_PosPID.Target - DLift_Speed, Pos, Lift_Pos_Limit);
		}
	}
}
/* һ��̧������ --------------*/
void Lift_Motor_Classdef::First_Stage_Lift()
{
	Step_Lift(First_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* ����̧������ --------------*/
void Lift_Motor_Classdef::Second_Stage_Lift()
{
	Step_Lift(Second_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* ����̧������ --------------*/
void Lift_Motor_Classdef::Third_Stage_Lift()
{
	Step_Lift(Third_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* ��¼̧������ --------------*/
void Lift_Motor_Classdef::Test_jl_Lift()
{
	Step_Lift(Test_jl_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* ����Դ���Ӿ�̧������ --------------*/
void Lift_Motor_Classdef::Vision_BigBox_Lift()
{
	Step_Lift(Vision_BigBox_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* ����Դ��ȡ��̧������ --------------*/
void Lift_Motor_Classdef::Take_BigBox_Lift()
{
	Step_Lift(Take_BigBox_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* С��Դ��ȡ��̧������ --------------*/
void Lift_Motor_Classdef::Take_SmallBox_Lift()
{
	Step_Lift(Take_SmallBox_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* �һ���ʯ̧������ --------------*/
void Lift_Motor_Classdef::Exchange_Box_Lift()
{
	Step_Lift(Exchange_Box_Lift_Pos, ULift_Speed, ULift_Buffer_Speed);
}
/* ̧��ֹͣ���� --------------*/
void Lift_Motor_Classdef::Lift_Stop()
{
	LeftLift_PosPID.Target = LeftLift_PosPID.Current;
	RightLift_PosPID.Target = RightLift_PosPID.Current;
}
/* ̧����������� --------------*/
void Lift_Motor_Classdef::Lift_Death()
{
	LeftLift_SpdPID.SetPIDParam(15.0f,0.0f,0.0f,10000.0f,0.0f);
	RightLift_SpdPID.SetPIDParam(15.0f,0.0f,0.0f,10000.0f,0.0f);
}
/* ̧���ָ�������� --------------*/
void Lift_Motor_Classdef::Lift_Life()
{
	LeftLift_SpdPID.SetPIDParam(15.0f,0.0f,0.0f,10000.0f,16000.0f);
	RightLift_SpdPID.SetPIDParam(15.0f,0.0f,0.0f,10000.0f,16000.0f);
}

/*---------------------------------------------- Lift Judge Function --------------------------------------------*/
/**
* @brief  ̧���жϺ���.
* @param  float ̧��λ��.
* @return bool �жϱ�־λ.
* @note  	��������Χ���ж��Ƿ�̧����ָ��λ��.
*/
bool Lift_Motor_Classdef::Lift_Judge(float Pos)
{
	return (abs(LeftLift_PosPID.Current - Pos) <= DeathZone_Limit && abs(RightLift_PosPID.Current - Pos) <= DeathZone_Limit);
}
bool Lift_Motor_Classdef::Lift_Negative_Judge()	{return Lift_Judge(Negative_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_None_Judge()	{return Lift_Judge(None_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_First_Judge() {return Lift_Judge(First_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_Second_Judge() {return Lift_Judge(Second_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_Third_Judge() {return Lift_Judge(Third_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_Test_jl_Judge() {return Lift_Judge(Test_jl_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_Vision_BigBox_Judge() {return Lift_Judge(Vision_BigBox_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_Take_BigBox_Judge() {return Lift_Judge(Take_BigBox_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_Take_SmallBox_Judge() {return Lift_Judge(Take_SmallBox_Lift_Pos);}
bool Lift_Motor_Classdef::Lift_Exchange_Box_Judge() {return Lift_Judge(Exchange_Box_Lift_Pos);}

/**
* @brief  ̧��ˮƽ�жϺ���.
* @param  void.
* @return bool �жϱ�־λ.
* @note  	�ж�̧�����ҵ����ǰֵ֮���Ƿ�������ƽ�����.
*/
bool Lift_Motor_Classdef::Life_Balance_Protect()
{
	return (abs(LeftLift_PosPID.Current - RightLift_PosPID.Current) <= Balance_Error);
}
/*---------------------------------------------- Turn Motor Function --------------------------------------------*/

/**
* @brief  ������ת����.
* @param  pos	DR16���Ʊ���.
* @return void.
* @note  	���ֱ��������.
*					- 500Ϊ��ת�ٶȿ��Ʋ������ɵ���
*/
void Turn_Motor_Classdef::Turn_to_Pos(float pos)
{
	Turn_StartPos = Turn_PosPID.Current;
	if(pos != 0)
	{
		Turn_PosPID.Target = myConstrain(Turn_StartPos + pos*5000.0f, -Turn_Pos_Limit , Turn_Pos_Limit);
	}
}

/**
* @brief  ��ת��������.
* @param  sign	�Ӿ���־λ.
* @return void.
* @note  	��ת���Ӿ���־λ����ˮƽ.
*					0:�޲���	1:��ת		2����������		3����ת

*/
bool Turn_Motor_Classdef::Turn_to_QR(uint8_t sign)
{
	switch(sign)
	{
		case 0:
			return false;
		case 1:
			Turn_PosPID.Target = myConstrain(Turn_PosPID.Current + 8000.0f, -Turn_Pos_Limit , Turn_Pos_Limit);
			return false;
		case 2:
			return true;
		case 3:
			Turn_PosPID.Target = myConstrain(Turn_PosPID.Current - 8000.0f, -Turn_Pos_Limit , Turn_Pos_Limit);
			return false;
		default:
			return false;
	}
}
/* ��תֹͣ���� --------------*/
void Turn_Motor_Classdef::Turn_Stop()
{
	Turn_PosPID.Target = Turn_PosPID.Current;
}
/* ��ת��������� --------------*/
void Turn_Motor_Classdef::Turn_Death()
{
	Turn_SpdPID.SetPIDParam(6.0f,0.0f,0.0f,16000.0f,0.0f);
}
/* ��ת�ָ�������� --------------*/
void Turn_Motor_Classdef::Turn_Life()
{
	Turn_SpdPID.SetPIDParam(6.0f,0.0f,0.0f,16000.0f,16000.0f);
}

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
