#include "sys.h"
#include "motor.h"
#include "delay.h"
#include "timer.h"

void Motor1_run(Motor_dir flag, float duty)
{
	switch(flag)
	{
		case Motor_EWD: //正转
			TIM_SetCompare3(TIM2, (u16)(duty * MAX_ARR));
			TIM_SetCompare4(TIM2, 0);
			break;
		case Motor_REV:
			TIM_SetCompare3(TIM2, 0);
			TIM_SetCompare4(TIM2, (u16)(duty * MAX_ARR));
			break;
		case Motor_STOP:
			TIM_SetCompare3(TIM2, 0);
			TIM_SetCompare4(TIM2, 0);
			break;
		default:
			break;
	}
}

void Motor2_run(Motor_dir flag, float duty)
{
	switch(flag)
	{
		case Motor_EWD:
			TIM_SetCompare1(TIM1, (u16)(duty * MAX_ARR));
			TIM_SetCompare2(TIM1, 0);
			break;
		case Motor_REV:
			TIM_SetCompare1(TIM1, 0);
			TIM_SetCompare2(TIM1, (u16)(duty * MAX_ARR));
			break;
		case Motor_STOP:
			TIM_SetCompare1(TIM1, 0);
			TIM_SetCompare2(TIM1, 0);
			break;
		default:
			break;
	}
}

void Motor3_run(Motor_dir flag, float duty)
{
	switch(flag)
	{
		case Motor_EWD:
			TIM_SetCompare3(TIM1, (u16)(duty * MAX_ARR));
			TIM_SetCompare4(TIM1, MAX_ARR);
			break;
		case Motor_REV:
			TIM_SetCompare3(TIM1, 0);
			TIM_SetCompare4(TIM1, (u16)((1.0f - duty) * MAX_ARR));
			break;
		case Motor_STOP:
			TIM_SetCompare3(TIM1, 0);
			TIM_SetCompare4(TIM1, MAX_ARR);
			break;
		default:
			break;
	}

}

void Motor4_run(Motor_dir flag, float duty)
{
	switch(flag)
	{
		case Motor_EWD:	
			TIM_SetCompare1(TIM4, (u16)(duty * MAX_ARR));
			TIM_SetCompare2(TIM4, 0);
			break;
		case Motor_REV:
			TIM_SetCompare1(TIM4, 0);
			TIM_SetCompare2(TIM4, (u16)(duty * MAX_ARR));
			break;
		case Motor_STOP:
			TIM_SetCompare1(TIM4, 0);
			TIM_SetCompare2(TIM4, 0);
			break;
		default:
			break;
	}

}

void Motor5_run(Motor_dir flag, float duty)
{
	switch(flag)
	{
		case Motor_EWD:
			TIM_SetCompare3(TIM4, (u16)(duty * MAX_ARR));
			TIM_SetCompare4(TIM4, 0);
			break;
		case Motor_REV:
			TIM_SetCompare3(TIM4, 0);
			TIM_SetCompare4(TIM4, (u16)(duty * MAX_ARR));
			break;
		case Motor_STOP:
			TIM_SetCompare3(TIM4, 0);
			TIM_SetCompare4(TIM4, 0);
			break;
		default:
			break;
	}

}

extern u16 TIM3_counter;
/*电机运动入口函数矩阵*/
typedef void (*MOTOR_RUN)(Motor_dir flag, float duty);
MOTOR_RUN Motor_run[MotorNum] = {Motor1_run, Motor2_run, Motor3_run, Motor4_run, Motor5_run}; 

/*电机运动函数，即电机沿设定的方向（flag），以一定的占空比(duty)运动time时间（ms），然后停止*/
void motor_move(Motor_dir *flag, float *duty, u16 time)
{
	u8 MotorNo;
	TIM3_counter = 0;
	for(MotorNo = 0;MotorNo < MotorNum;MotorNo++)
		Motor_run[MotorNo](flag[MotorNo], duty[MotorNo]);
	while(1)
	{
		if(TIM3_counter >= time)
		{
			for(MotorNo = 0;MotorNo < MotorNum;MotorNo++)
				Motor_run[MotorNo](Motor_STOP, duty[MotorNo]);
			break;
		}
	}
}




