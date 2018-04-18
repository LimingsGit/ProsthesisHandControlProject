#include "timer.h"
#include "led.h"
extern u8 Command_Flag;

/* ��ʱ��2��ʼ�� motor1*/
void TIM2_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;					//����GPIO�ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	  //�������� Motor1_fault
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	//TIM4��������������
	TIM_DeInit(TIM2); 
 	TIM_TimeBaseStructure.TIM_Period = MAX_ARR;//�Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 
  //����Ƚ�ͨ��
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_Pulse = 0;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  

	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
  
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}


/* ��ʱ��1��ʼ�� motor2 & motor3*/
void TIM1_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 			//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 					

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;									//�������� PA12 Motor3_Fault
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;									//�������� PB13 Motor2_Fault
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//TIM1��������������
	TIM_DeInit(TIM1); 
	TIM_TimeBaseStructure.TIM_Period = MAX_ARR;//�Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	//TIM1����Ƚ�ͨ������
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_Pulse = 0;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); //Motor2_IN1
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); //Motor2_IN2
	TIM_OC3Init(TIM1, &TIM_OCInitStructure); //Motor3_IN1
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); //Motor3_IN2
	
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); 
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);   

	TIM_SetCompare3(TIM1, 0);
	TIM_SetCompare4(TIM1, MAX_ARR);
}

/* ��ʱ��4��ʼ�� motor4 & motor5*/
void TIM4_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;					//����GPIO�ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_15;	  //�������� Motor4_Fault  Motor5_Fault
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	//TIM4��������������
	TIM_DeInit(TIM4); 
 	TIM_TimeBaseStructure.TIM_Period = MAX_ARR;//�Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
  //����Ƚ�ͨ��
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_Pulse = 0;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx					 
}



/* TIM3��ʼ�� */
void TIM3_Init(u16 arr, u16 psc)//Tout= ((arr+1)*(psc+1))/72M
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
}

/* TIM3�жϷ����� */
u16 TIM3_counter = 0;
void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); //����жϱ�־λ
		TIM3_counter++;
	}
}











