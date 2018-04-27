#include "sys.h"
#include "motor.h"
#include "delay.h"
#include "timer.h"

void Motor1_run(Motor_dir flag, float duty)
{
	switch(flag)
	{
		case Motor_EWD: //��ת
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
/*����˶���ں�������*/
typedef void (*MOTOR_RUN)(Motor_dir flag, float duty);
MOTOR_RUN Motor_run[MotorNum] = {Motor1_run, Motor2_run, Motor3_run, Motor4_run, Motor5_run}; 

/*����˶�������������������趨�ķ���flag�����Ը��Ե�ռ�ձ�(duty)�˶�timeʱ�䣨ms����Ȼ��ֹͣ*/
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

/*������������������������ת*/
const float MaxLocation[5] = {10.0f, 10.0f, 9.0f, 10.0f, 6.0f}; //����˶�����
float DecLocation[5] = {10.0f/9.0f, 10.0f/8.0f, 9.0f/8.0f, 1.0f, 1.0f}; //��������
static float NowLocation[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}; //��ʼ״̬������ȫ��չ״̬
void UpdateSafeDis(Motor_dir *flag, float *duty, u8 index)
{
	if(index == 0 || index == 2 || index == 4)   //СĴָ  ��ָ  ��Ĵָ 
	{
		if(flag[index] == Motor_EWD) //����
		{
			if(NowLocation[index] + 1.0f > MaxLocation[index])
				duty[index] = 0;
			else
				NowLocation[index] += 1.0f;
		}
		else if(flag[index] == Motor_REV) //��չ  
		{
			if(NowLocation[index] - DecLocation[index] < 0)
				duty[index] = 0;
			else
				NowLocation[index] -= DecLocation[index];
		}
	}
	else    //����ָ��ʳָ
	{
		if(flag[index] == Motor_REV) //����
		{
			if(NowLocation[index] + 1.0f > MaxLocation[index])   //����������ֵ
				duty[index] = 0;
			else
				NowLocation[index] += 1.0f;
		}
		else if(flag[index] == Motor_EWD) //��չ
		{
			if(NowLocation[index] - DecLocation[index] < 0)  //��չ������ֵ
				duty[index] = 0;
			else
				NowLocation[index] -= DecLocation[index];
		}
	}
}

/*���㰲ȫ�ƶ���duty�������������ת*/
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


