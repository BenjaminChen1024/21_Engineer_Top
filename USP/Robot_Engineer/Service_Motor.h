/**
  ******************************************************************************
  * @file   : Service_Motor.h
  * @brief  : Service_Motor.cpp头文件
  ****************************************************************************** 
**/
#ifndef _SERVICE_MOTOCTRL_H_
#define _SERVICE_MOTOCTRL_H_
/* Includes ------------------------------------------------------------------*/
#include "System_DataPool.h"
/* Private defines ------------------------------------------------------------*/

/* 电机ID --------------*/
#define LeftExtendMotor_ID		0x201
#define RightExtendMotor_ID		0x202
#define LeftRotateMotor_ID		0x203
#define RightRotateMotor_ID		0x204
#define LeftLiftMotor_ID			0x205
#define RightLiftMotor_ID			0x206
#define TurnMotor_ID					0x207
/* 电机PID --------------*/
#define LeftExtend_PosPID 		MotorPID[0]	
#define LeftExtend_SpdPID 		MotorPID[1]	
#define RightExtend_PosPID 		MotorPID[2]	
#define RightExtend_SpdPID 		MotorPID[3]
#define LeftRotate_PosPID			MotorPID[4]
#define LeftRotate_SpdPID 		MotorPID[5]
#define RightRotate_PosPID 		MotorPID[6]
#define RightRotate_SpdPID 		MotorPID[7]
#define LeftLift_PosPID				MotorPID[8]
#define LeftLift_SpdPID 			MotorPID[9]
#define RightLift_PosPID 			MotorPID[10]	
#define RightLift_SpdPID 			MotorPID[11]	
#define Turn_PosPID 					MotorPID[12]	
#define Turn_SpdPID 					MotorPID[13]
/* 死区 --------------*/
#define DeathZone_Limit 					3000.0f

/* Private variables ---------------------------------------------------------*/

/* 电机类 --------------*/
extern Motor_C610 LeftExtendMotor,RightExtendMotor;
extern Motor_C620 LeftRotateMotor,RightRotateMotor;
extern Motor_C620 LeftLiftMotor,RightLiftMotor;
extern Motor_C610 TurnMotor;
//extern Motor_C620 TurnMotor;
/* 电机PID数组 --------------*/
extern myPID MotorPID[20];
/* 电机自检状态 --------------*/
enum POSTtypedef
{
	Rotate_POST_OK,
	Extend_POST_OK,
	Lift_POST_OK,
	Motor_POST_OK
};

/* Private function declarations ---------------------------------------------*/

/*---------------------------------------------- Rotate Motor Class --------------------------------------------*/
class Rotate_Motor_Classdef
{
	private:
		/* 翻转电机位置 --------------*/
		float Rotate_Pos_Limit= 								96000.0f;
		float Rotate_Pos_Limit_Middle=					88000.0f;
		float Rotate_Pos_Hor= 									81000.0f;
		float Rotate_Pos_Hor_Middle=						73000.0f;
//		float Rotate_Pos_Push= 									78000.0f;
//		float Rotate_Pos_Push_Middle=						70000.0f;
		float Rotate_Pos_Push= 									70000.0f;
		float Rotate_Pos_Push_Middle=						62000.0f;
		float Rotate_Pos_SmallBox= 							67000.0f;
		float Rotate_Pos_SmallBox_Middle=				59000.0f;
		float Rotate_Pos_Exchange= 							71000.0f;
		float Rotate_Pos_Exchange_Middle=				63000.0f;
		float Rotate_Pos_ExchangeAgain= 				75000.0f;
		float Rotate_Pos_ExchangeAgain_Middle=	67000.0f;
		float Rotate_Pos_Top= 									56000.0f;
		float Rotate_Pos_Top_Middle=						48000.0f;
		float Rotate_Pos_Topper_Middle=					18000.0f;
		float Rotate_Pos_Topper= 								10000.0f;
		float Rotate_Back_Start_Middle=					9000.0f;
		float Rotate_Pos_Start= 								1000.0f;
		/* 翻转电机速度 --------------*/
		float Rotate_Speed=									100.0f;
		float Rotate_Buffer_Speed=					80.0f;
		/* 翻转电机初始位置 --------------*/
		float Left_StartAngle,Right_StartAngle;
		/* 翻转电机函数 --------------*/
		void Rotate_Step(float, float, float, float);				//翻转函数（翻转位置，翻转缓冲位置，翻转速度，翻转缓冲速度）
		bool Rotate_Judge(float);				//翻转判断函数（翻转位置）
	
	public:
		/* 翻转电机相对零点 --------------*/
		float LeftRotato_ZeroOffset = 0;
		float RightRotato_ZeroOffset = 0;
		/* 翻转电机扭矩转速 --------------*/
		int16_t LeftRotate_Torque,RightRotate_Torque;
		int16_t LeftRotate_rpm,RightRotate_rpm;
		/* 翻转电机动作函数 --------------*/
		POSTtypedef Rotate_POST();				//翻转电机开机自检函数（）
		void Rotate_to_Pos(float);				//自由翻转函数（DR16控制变量）
		void Rotate_Topper();				//翻转更高点函数（）
		void Rotate_Top();				//翻转最高点函数（）
		void Rotate_SmallBox();				//翻转小矿点函数（）
		void Rotate_Exchange();				//翻转兑换点函数（）
		void Rotate_ExchangeAgain();				//翻转再次兑换点函数（）
		void Rotate_Push();				//翻转水平推出函数（）
		void Rotate_Hor();				//翻转水平函数（）
		void Rotate_Limit();				//翻转极限函数（）
		void Rotate_Back_Start();				//翻转收回原点函数（）
		void Rotate_Stop();				//翻转停止函数（）
		/* 翻转电机判断函数 --------------*/
		bool Rotate_Start_Judge();
		bool Rotate_Topper_Judge();
		bool Rotate_Top_Judge();
		bool Rotate_SmallBox_Judge();
		bool Rotate_Exchange_Judge();
		bool Rotate_ExchangeAgain_Judge();
		bool Rotate_Push_Judge();
		bool Rotate_Hor_Judge();
		bool Rotate_Limit_Judge();
};

/*---------------------------------------------- Extend Motor Class --------------------------------------------*/
class Extend_Motor_Classdef
{
	private:
		/* 伸出电机位置 --------------*/
		float Extension_Buffer_Zone=			20000.0f;
		float Vision_Extension_Pos=				600.0f;
		float Negative_Extension_Pos=			10000.0f;
		float None_Extension_Pos= 				60000.0f;
		float Mini_Extension_Pos= 				140000.0f;
		float First_Extension_Pos= 				240000.0f;
		float Second_Extension_Pos= 			290000.0f;
		float Third_Extension_Pos=				290000.0f;
		float Extension_Pos_Limit=				290000.0f;
		/* 伸出电机初始位置 --------------*/
		float LeftExtend_StartPos,RightExtend_StartPos;
		/* 伸出电机函数 --------------*/
		void Extend_Step(float Pos, float OUT_Speed, float IN_Speed);				//伸出函数（伸出位置，伸出速度，收回速度）
		bool Extend_Judge(float Pos);				//伸出判断函数（伸出位置）
	
	public:
		/* 伸出电机相对零点 --------------*/
		float LeftExtend_ZeroOffset = 0;
		float RightExtend_ZeroOffset = 0;
		/* 伸出电机扭矩 --------------*/
		int16_t LeftExtend_Torque,RightExtend_Torque;
		/* 伸出电机动作函数 --------------*/
		POSTtypedef Extend_POST();				//伸出电机开机自检函数（）
		void Extend_to_Pos(float);				//自由伸出函数（DR16控制变量）
		bool Extend_Adjust(uint8_t);				//伸出调整函数（伸出标志位）
		void Negative_Extension();				//负阶伸出函数（）
		void None_Extension();				//零阶伸出函数（）
		void Mini_Extension();				//微小伸出函数（）
		void First_Stage_Extension();				//一阶伸出函数（）
		void Second_Stage_Extension();				//二阶伸出函数（）
		void Third_Stage_Extension();				//三阶伸出函数（）
		void Extend_Stop();				//伸出停止函数（）
		/* 伸出电机判断函数 --------------*/
		bool Extend_Negative_Judge();
		bool Extend_None_Judge();
		bool Extend_Mini_Judge();
		bool Extend_First_Judge();
		bool Extend_Second_Judge();
		bool Extend_Third_Judge();
};

/*---------------------------------------------- Lift Motor Class --------------------------------------------*/
class Lift_Motor_Classdef
{
	private:
		/* 抬升电机位置 --------------*/
		float Lift_Buffer_Zone=					230000.0f;
		float Negative_Lift_Pos=				5000.0f;
		float None_Lift_Pos= 						35000.0f;
		float First_Lift_Pos= 					80000.0f;
		float Second_Lift_Pos= 					500000.0f;
//		float Third_Lift_Pos= 					1350000.0f;
		float Third_Lift_Pos= 					750000.0f;
//		float Test_jl_Lift_Pos=					830000.0f;
		float Test_jl_Lift_Pos=					900000.0f;
		float Vision_BigBox_Lift_Pos= 	160000.0f;
		float Take_BigBox_Lift_Pos= 		630000.0f;
//		float Take_SmallBox_Lift_Pos= 	1350000.0f;
//		float Exchange_Box_Lift_Pos=		1350000.0f;
//		float Lift_Pos_Limit=						1350000.0f;
		float Take_SmallBox_Lift_Pos= 	1000000.0f;
		float Exchange_Box_Lift_Pos=		1000000.0f;
		float Lift_Pos_Limit=						1000000.0f;
			/* 抬升电机速度 --------------*/
		float ULift_Speed=								800.0f;
		float ULift_Buffer_Speed=					400.0f;
		float DLift_Speed=								700.0f;
		float DLift_Buffer_Speed=					300.0f;
		/* 抬升电机最大平衡误差 --------------*/
		float Balance_Error=						300000.0f;
		/* 抬升电机初始位置 --------------*/
		float LeftLift_StartPos,RightLift_StartPos;
		/* 抬升电机开机自检标志位 --------------*/
		uint8_t Lift_POST_flag;
		uint8_t Lift_POST_Sensor_flag = 1;
		uint8_t Lift_POST_move_flag;
		float Lift_POST_Time;
		/* 抬升电机函数 --------------*/
		void Step_Lift(float, float, float);				//抬升函数（抬升位置，抬升速度，抬升缓冲速度）
		bool Lift_Judge(float Pos);				//抬升判断函数（抬升位置）

	public:
		/* 抬升电机相对零点 --------------*/
		float LeftLift_ZeroOffset = 0;
		float RightLift_ZeroOffset = 0;
		/* 抬升电机扭矩 --------------*/
		int16_t LeftLift_Torque,RightLift_Torque;
		/* 抬升电机动作函数 --------------*/
		POSTtypedef Lift_POST();				//抬升电机开机自检函数（）
		void Lift_POST_Reset();
		void Lift_to_Pos(uint8_t, float);				//自由抬升函数（DR16控制变量）
		bool Lift_Adjust(uint8_t, uint8_t);				//抬升调整函数（电机位置，电机转动标志位）
		void Test_Lift(float, float, float);				//测试抬升函数（抬升位置，上升速度，下降速度）
		void Negative_Lift();				//负阶抬升函数（）
		void None_Lift();				//零阶抬升函数（）
		void First_Stage_Lift();				//一阶抬升函数（）
		void Second_Stage_Lift();				//二阶抬升函数（）
		void Third_Stage_Lift();				//三阶抬升函数（）
		void Test_jl_Lift();				//检录抬升函数（）
		void Vision_BigBox_Lift();				//大资源岛取矿抬升函数（）
		void Take_BigBox_Lift();				//大资源岛取矿抬升函数（）
		void Take_SmallBox_Lift();				//小资源岛取矿抬升函数（）
		void Exchange_Box_Lift();				//兑换矿石抬升函数（）
		void Lift_Stop();				//抬升停止函数（）
		void Lift_Death();				//抬升无输出函数（）
		void Lift_Life();				//抬升恢复输出函数（）
		/* 抬升电机判断函数 --------------*/
		bool Lift_Negative_Judge();
		bool Lift_None_Judge();
		bool Lift_Take_Judge();
		bool Lift_First_Judge();
		bool Lift_Second_Judge();
		bool Lift_Third_Judge();
		bool Lift_Test_jl_Judge();
		bool Lift_Vision_BigBox_Judge();
		bool Lift_Take_BigBox_Judge();
		bool Lift_Take_SmallBox_Judge();
		bool Lift_Exchange_Box_Judge();
		bool Life_Balance_Protect();
};

/*---------------------------------------------- Turn Motor Class --------------------------------------------*/
class Turn_Motor_Classdef
{
	private:
		/* 旋转电机位置 --------------*/
		float Turn_Pos_Limit=9000000000000000000.0f;
		/* 旋转电机初始位置 --------------*/
		float Turn_StartPos;

	public:
		uint8_t Turn_close_flag;
		/* 旋转电机扭矩 --------------*/
		int16_t Turn_Torque;
		/* 旋转电机视觉标志位 --------------*/
		uint8_t Turn_QR;
		/* 旋转电机动作函数 --------------*/
		void Turn_to_Pos(float);				//自由旋转函数（DR16控制变量）
		bool Turn_to_QR(uint8_t);				//旋转调整函数（视觉标志位）
		void Turn_Stop();				//旋转停止函数（）
		void Turn_Death();				//旋转无输出函数（）
		void Turn_Life();				//旋转恢复输出函数（）
};

/*---------------------------------------------- Universal Motor Class --------------------------------------------*/
class Motor_Classdef
{
	private:
		void MotorMsgSend(CAN_HandleTypeDef *hcan,int16_t Motor_Msg[],int StdID);				//电机数据发送函数（CAN口，数据包，电机ID）
		void MotorPID_Control(void);				//电机PID控制函数（）
	
	public:
		/* 电机类 --------------*/
		Rotate_Motor_Classdef Rotate_Motor;
		Extend_Motor_Classdef Extend_Motor;
		Lift_Motor_Classdef Lift_Motor;
		Turn_Motor_Classdef Turn_Motor;
		/* 电机函数 --------------*/
		void Update_Motor(uint8_t *,uint32_t );				//电机数据更新函数（数据包，电机ID）
		void MotorPIDInit();				//电机PID初始化函数（）
		void Motor_Control();				//电机控制函数（）
};

#endif
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
