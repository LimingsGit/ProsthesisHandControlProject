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

/*电机运动函数，即各个电机沿设定的方向（flag），以各自的占空比(duty)运动time时间（ms），然后停止*/
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

/*软件保护函数，保护电机不堵转*/
const float MaxLocation[5] = {10.0f, 10.0f, 9.0f, 10.0f, 6.0f}; //最大运动次数
float DecLocation[5] = {10.0f/9.0f, 10.0f/8.0f, 9.0f/8.0f, 1.0f, 1.0f}; //返程增量
static float NowLocation[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}; //初始状态，即完全伸展状态
void UpdateSafeDis(Motor_dir *flag, float *duty, u8 index)
{
	if(index == 0 || index == 2 || index == 4)   //小拇指  中指  大拇指 
	{
		if(flag[index] == Motor_EWD) //弯曲
		{
			if(NowLocation[index] + 1.0f > MaxLocation[index])
				duty[index] = 0;
			else
				NowLocation[index] += 1.0f;
		}
		else if(flag[index] == Motor_REV) //伸展  
		{
			if(NowLocation[index] - DecLocation[index] < 0)
				duty[index] = 0;
			else
				NowLocation[index] -= DecLocation[index];
		}
	}
	else    //无名指和食指
	{
		if(flag[index] == Motor_REV) //弯曲
		{
			if(NowLocation[index] + 1.0f > MaxLocation[index])   //弯曲超过阈值
				duty[index] = 0;
			else
				NowLocation[index] += 1.0f;
		}
		else if(flag[index] == Motor_EWD) //伸展
		{
			if(NowLocation[index] - DecLocation[index] < 0)  //伸展超过阈值
				duty[index] = 0;
			else
				NowLocation[index] -= DecLocation[index];
		}
	}
}

/*计算安全移动的duty，保护电机不堵转*/
void CalSafeMoveDis(Motor_dir *flag, float *duty)
{
	u8 i = 0;
	for(i = 0;i < 5;i++)
	{
		if(flag[i] < 2)
		{
			UpdateSafeDis(flag, duty, i);
		}
	}
}	


