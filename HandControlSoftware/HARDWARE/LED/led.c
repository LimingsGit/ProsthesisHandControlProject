#include "led.h"

void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;					 					//定义GPIO结构体
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;			//LED-->PB8端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 						//根据设定参数初始化PB_8
	
 GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);						 //PB_8 PB_9 初始输出高			
}

