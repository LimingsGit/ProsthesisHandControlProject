#include  "task.h"
#include  "motor.h"
#include  "led.h"
#include  "delay.h"
#include  "usart.h"
#include  "timer.h"

extern u16 TIM3_counter;
extern u8 command;

/*初始化底层驱动*/
void BSP_Init(void)
{
	delay_init(); 					//延时函数初始化	
	NVIC_Configuration();  	//中断分组初始化
	LED_Init();		  				//初始化与LED连接的硬件接口
  uart_init(9600);	 			//串口初始化
  TIM1_Init();						//定时器初始化
  TIM2_Init();
  TIM4_Init();
	TIM3_Init(99, 719); 		//定时器1ms
}

/*缺省命令/空闲状态处理函数*/
void Task_wait_func(u8 CommandNo)
{
	TIM3_counter = 0;
}

/*测试命令处理函数（命令1-a）*/
void Task_test_func(u8 CommandNo)
{
	Motor_dir flag[MotorNum] = {Default, Default, Default, Default, Default};
	float duty[MotorNum] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	u8 MotorNo = (CommandNo + 1) / 2 - 1;	 	//根据命令获得电机编号	
	duty[MotorNo] = 0.7f;								//设置对应的占空比
	flag[MotorNo] = (Motor_dir)((CommandNo + 1) % 2);		//设置电机运动方向
	LED0 = !LED0;
	LED1 = !LED1;
	motor_move(flag, duty, 100);
	command = wait_command;
}

/*手张开命令处理函数（命令b）*/
void Task_hand_open(u8 CommandNo)
{
	Motor_dir flag[MotorNum] = {Motor_REV, Motor_EWD, Motor_REV, Motor_EWD, Motor_REV};
	float duty[MotorNum] = {0.75f, 0.50f, 0.30f, 0.75f, 0.70f};
	LED0 = !LED0;
	LED1 = !LED1;
	motor_move(flag, duty, 100);
	command = wait_command;
}

/*手闭合命令处理函数（命令c）*/
void Task_hand_close(u8 CommandNo)
{
	Motor_dir flag[MotorNum] = {Motor_EWD, Motor_REV, Motor_EWD, Motor_REV, Motor_EWD};
	float duty[MotorNum] = {0.75f, 0.70f, 0.30f, 0.75f, 0.70f};
	LED0 = !LED0;
	LED1 = !LED1;
	motor_move(flag, duty, 100);
	command = wait_command;
}	

