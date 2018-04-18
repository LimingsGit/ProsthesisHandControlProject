#ifndef	__MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"

/*电机名称*/
typedef enum MOTORNO
{
	Motor1,
	Motor2,
	Motor3,
	Motor4,
	Motor5,
	MotorNum
}EN_MotorNo;

/*电机运动方向*/
typedef enum MOTOR_DIR
{
	Motor_EWD,  //0
	Motor_REV,	//1
	Motor_STOP,
	Default
}Motor_dir;

void Motor1_run(Motor_dir flag, float duty);
void Motor2_run(Motor_dir flag, float duty);
void Motor3_run(Motor_dir flag, float duty);
void Motor4_run(Motor_dir flag, float duty);
void Motor5_run(Motor_dir flag, float duty);

/*电机运动函数，即电机沿设定的方向（flag），以一定的占空比(duty)运动time时间（ms），然后停止*/
void motor_move(Motor_dir *flag, float *duty, u16 time);
#endif

