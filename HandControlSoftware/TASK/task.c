#include  "task.h"
#include  "motor.h"
#include  "led.h"
#include  "delay.h"
#include  "usart.h"
#include  "timer.h"

extern u16 TIM3_counter;
extern u8 command;

/*��ʼ���ײ�����*/
void BSP_Init(void)
{
	delay_init(); 					//��ʱ������ʼ��	
	NVIC_Configuration();  	//�жϷ����ʼ��
	LED_Init();		  				//��ʼ����LED���ӵ�Ӳ���ӿ�
  uart_init(9600);	 			//���ڳ�ʼ��
  TIM1_Init();						//��ʱ����ʼ��
  TIM2_Init();
  TIM4_Init();
	TIM3_Init(99, 719); 		//��ʱ��1ms
}

/*����Ŀǰ�Ѿ�������ȫ��չ״̬������HaveReceiveResetOrder��״̬*/
u8 HaveReceiveResetOrder = 0;
void Task_hand_reset(u8 CommandNo)
{
	LED0 = !LED0;
	LED1 = !LED1;
	HaveReceiveResetOrder = 1;
}

/*ȱʡ����/����״̬������*/
void Task_wait_func(u8 CommandNo)
{
	TIM3_counter = 0;
}

/*�����������������1-a��*/
void Task_test_func(u8 CommandNo)
{
	Motor_dir flag[MotorNum] = {Default, Default, Default, Default, Default};
	float duty[MotorNum] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	u8 MotorNo = (CommandNo + 1) / 2 - 1;	 	//���������õ�����	
	flag[MotorNo] = (Motor_dir)((CommandNo + 1) % 2);		//���õ���˶�����
	if(MotorNo == 2)
		duty[MotorNo] = 0.3f;
	else
		duty[MotorNo] = 0.7f;								//���ö�Ӧ��ռ�ձ�
	LED0 = !LED0;
	LED1 = !LED1;
	if(HaveReceiveResetOrder == 1) 
		CalSafeMoveDis(flag, duty);
	motor_move(flag, duty, 100);
	command = wait_command;
}

/*���ſ��������������b��*/
void Task_hand_open(u8 CommandNo)
{
	Motor_dir flag[MotorNum] = {Motor_REV, Motor_EWD, Motor_REV, Motor_EWD, Motor_REV};
	float duty[MotorNum] = {0.75f, 0.70f, 0.30f, 0.75f, 0.70f};
	LED0 = !LED0;
	LED1 = !LED1;
	if(HaveReceiveResetOrder == 1) 
		CalSafeMoveDis(flag, duty);	
	motor_move(flag, duty, 100);
	command = wait_command;
}


/*�ֱպ��������������c��*/
void Task_hand_close(u8 CommandNo)
{
	Motor_dir flag[MotorNum] = {Motor_EWD, Motor_REV, Motor_EWD, Motor_REV, Motor_EWD};
	float duty[MotorNum] = {0.75f, 0.70f, 0.30f, 0.75f, 0.70f};
	LED0 = !LED0;
	LED1 = !LED1;
	if(HaveReceiveResetOrder == 1) 
		CalSafeMoveDis(flag, duty);
	motor_move(flag, duty, 100);
	command = wait_command;
}	





