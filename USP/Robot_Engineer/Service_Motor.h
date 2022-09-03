/**
  ******************************************************************************
  * @file   : Service_Motor.h
  * @brief  : Service_Motor.cppͷ�ļ�
  ****************************************************************************** 
**/
#ifndef _SERVICE_MOTOCTRL_H_
#define _SERVICE_MOTOCTRL_H_
/* Includes ------------------------------------------------------------------*/
#include "System_DataPool.h"
/* Private defines ------------------------------------------------------------*/

/* ���ID --------------*/
#define LeftExtendMotor_ID		0x201
#define RightExtendMotor_ID		0x202
#define LeftRotateMotor_ID		0x203
#define RightRotateMotor_ID		0x204
#define LeftLiftMotor_ID			0x205
#define RightLiftMotor_ID			0x206
#define TurnMotor_ID					0x207
/* ���PID --------------*/
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
/* ���� --------------*/
#define DeathZone_Limit 					3000.0f

/* Private variables ---------------------------------------------------------*/

/* ����� --------------*/
extern Motor_C610 LeftExtendMotor,RightExtendMotor;
extern Motor_C620 LeftRotateMotor,RightRotateMotor;
extern Motor_C620 LeftLiftMotor,RightLiftMotor;
extern Motor_C610 TurnMotor;
//extern Motor_C620 TurnMotor;
/* ���PID���� --------------*/
extern myPID MotorPID[20];
/* ����Լ�״̬ --------------*/
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
		/* ��ת���λ�� --------------*/
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
		/* ��ת����ٶ� --------------*/
		float Rotate_Speed=									100.0f;
		float Rotate_Buffer_Speed=					80.0f;
		/* ��ת�����ʼλ�� --------------*/
		float Left_StartAngle,Right_StartAngle;
		/* ��ת������� --------------*/
		void Rotate_Step(float, float, float, float);				//��ת��������תλ�ã���ת����λ�ã���ת�ٶȣ���ת�����ٶȣ�
		bool Rotate_Judge(float);				//��ת�жϺ�������תλ�ã�
	
	public:
		/* ��ת��������� --------------*/
		float LeftRotato_ZeroOffset = 0;
		float RightRotato_ZeroOffset = 0;
		/* ��ת���Ť��ת�� --------------*/
		int16_t LeftRotate_Torque,RightRotate_Torque;
		int16_t LeftRotate_rpm,RightRotate_rpm;
		/* ��ת����������� --------------*/
		POSTtypedef Rotate_POST();				//��ת��������Լ캯������
		void Rotate_to_Pos(float);				//���ɷ�ת������DR16���Ʊ�����
		void Rotate_Topper();				//��ת���ߵ㺯������
		void Rotate_Top();				//��ת��ߵ㺯������
		void Rotate_SmallBox();				//��תС��㺯������
		void Rotate_Exchange();				//��ת�һ��㺯������
		void Rotate_ExchangeAgain();				//��ת�ٴζһ��㺯������
		void Rotate_Push();				//��תˮƽ�Ƴ���������
		void Rotate_Hor();				//��תˮƽ��������
		void Rotate_Limit();				//��ת���޺�������
		void Rotate_Back_Start();				//��ת�ջ�ԭ�㺯������
		void Rotate_Stop();				//��תֹͣ��������
		/* ��ת����жϺ��� --------------*/
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
		/* ������λ�� --------------*/
		float Extension_Buffer_Zone=			20000.0f;
		float Vision_Extension_Pos=				600.0f;
		float Negative_Extension_Pos=			10000.0f;
		float None_Extension_Pos= 				60000.0f;
		float Mini_Extension_Pos= 				140000.0f;
		float First_Extension_Pos= 				240000.0f;
		float Second_Extension_Pos= 			290000.0f;
		float Third_Extension_Pos=				290000.0f;
		float Extension_Pos_Limit=				290000.0f;
		/* ��������ʼλ�� --------------*/
		float LeftExtend_StartPos,RightExtend_StartPos;
		/* ���������� --------------*/
		void Extend_Step(float Pos, float OUT_Speed, float IN_Speed);				//������������λ�ã�����ٶȣ��ջ��ٶȣ�
		bool Extend_Judge(float Pos);				//����жϺ��������λ�ã�
	
	public:
		/* ������������ --------------*/
		float LeftExtend_ZeroOffset = 0;
		float RightExtend_ZeroOffset = 0;
		/* ������Ť�� --------------*/
		int16_t LeftExtend_Torque,RightExtend_Torque;
		/* �������������� --------------*/
		POSTtypedef Extend_POST();				//�����������Լ캯������
		void Extend_to_Pos(float);				//�������������DR16���Ʊ�����
		bool Extend_Adjust(uint8_t);				//������������������־λ��
		void Negative_Extension();				//���������������
		void None_Extension();				//��������������
		void Mini_Extension();				//΢С�����������
		void First_Stage_Extension();				//һ�������������
		void Second_Stage_Extension();				//���������������
		void Third_Stage_Extension();				//���������������
		void Extend_Stop();				//���ֹͣ��������
		/* �������жϺ��� --------------*/
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
		/* ̧�����λ�� --------------*/
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
			/* ̧������ٶ� --------------*/
		float ULift_Speed=								800.0f;
		float ULift_Buffer_Speed=					400.0f;
		float DLift_Speed=								700.0f;
		float DLift_Buffer_Speed=					300.0f;
		/* ̧��������ƽ����� --------------*/
		float Balance_Error=						300000.0f;
		/* ̧�������ʼλ�� --------------*/
		float LeftLift_StartPos,RightLift_StartPos;
		/* ̧����������Լ��־λ --------------*/
		uint8_t Lift_POST_flag;
		uint8_t Lift_POST_Sensor_flag = 1;
		uint8_t Lift_POST_move_flag;
		float Lift_POST_Time;
		/* ̧��������� --------------*/
		void Step_Lift(float, float, float);				//̧��������̧��λ�ã�̧���ٶȣ�̧�������ٶȣ�
		bool Lift_Judge(float Pos);				//̧���жϺ�����̧��λ�ã�

	public:
		/* ̧����������� --------------*/
		float LeftLift_ZeroOffset = 0;
		float RightLift_ZeroOffset = 0;
		/* ̧�����Ť�� --------------*/
		int16_t LeftLift_Torque,RightLift_Torque;
		/* ̧������������� --------------*/
		POSTtypedef Lift_POST();				//̧����������Լ캯������
		void Lift_POST_Reset();
		void Lift_to_Pos(uint8_t, float);				//����̧��������DR16���Ʊ�����
		bool Lift_Adjust(uint8_t, uint8_t);				//̧���������������λ�ã����ת����־λ��
		void Test_Lift(float, float, float);				//����̧��������̧��λ�ã������ٶȣ��½��ٶȣ�
		void Negative_Lift();				//����̧����������
		void None_Lift();				//���̧����������
		void First_Stage_Lift();				//һ��̧����������
		void Second_Stage_Lift();				//����̧����������
		void Third_Stage_Lift();				//����̧����������
		void Test_jl_Lift();				//��¼̧����������
		void Vision_BigBox_Lift();				//����Դ��ȡ��̧����������
		void Take_BigBox_Lift();				//����Դ��ȡ��̧����������
		void Take_SmallBox_Lift();				//С��Դ��ȡ��̧����������
		void Exchange_Box_Lift();				//�һ���ʯ̧����������
		void Lift_Stop();				//̧��ֹͣ��������
		void Lift_Death();				//̧���������������
		void Lift_Life();				//̧���ָ������������
		/* ̧������жϺ��� --------------*/
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
		/* ��ת���λ�� --------------*/
		float Turn_Pos_Limit=9000000000000000000.0f;
		/* ��ת�����ʼλ�� --------------*/
		float Turn_StartPos;

	public:
		uint8_t Turn_close_flag;
		/* ��ת���Ť�� --------------*/
		int16_t Turn_Torque;
		/* ��ת����Ӿ���־λ --------------*/
		uint8_t Turn_QR;
		/* ��ת����������� --------------*/
		void Turn_to_Pos(float);				//������ת������DR16���Ʊ�����
		bool Turn_to_QR(uint8_t);				//��ת�����������Ӿ���־λ��
		void Turn_Stop();				//��תֹͣ��������
		void Turn_Death();				//��ת�������������
		void Turn_Life();				//��ת�ָ������������
};

/*---------------------------------------------- Universal Motor Class --------------------------------------------*/
class Motor_Classdef
{
	private:
		void MotorMsgSend(CAN_HandleTypeDef *hcan,int16_t Motor_Msg[],int StdID);				//������ݷ��ͺ�����CAN�ڣ����ݰ������ID��
		void MotorPID_Control(void);				//���PID���ƺ�������
	
	public:
		/* ����� --------------*/
		Rotate_Motor_Classdef Rotate_Motor;
		Extend_Motor_Classdef Extend_Motor;
		Lift_Motor_Classdef Lift_Motor;
		Turn_Motor_Classdef Turn_Motor;
		/* ������� --------------*/
		void Update_Motor(uint8_t *,uint32_t );				//������ݸ��º��������ݰ������ID��
		void MotorPIDInit();				//���PID��ʼ����������
		void Motor_Control();				//������ƺ�������
};

#endif
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
