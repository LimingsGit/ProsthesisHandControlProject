/*
 * Copyright (C), 2018, Xi'an jiaotong University
 * File name: main.c
 * Author:Zhangliming 	Version:1.0  Date:2018/04/01
 * date 2018/04/18
 * Description: ������λ����ָ���ɲ��ԡ������ſ����պϵȼ򵥹��� 
 * History:  
*/
#include  "task.h"

u8 command = wait_command;
/********************************************************
	����										��Ӧ��״̬							
	wait_command,				0:	ȱʡ����/����״̬
	test_motor1_ewd,		1:  СĴָ����
	test_motor1_rev,		2:	СĴָ��չ
	test_motor2_ewd,		3:	����ָ��չ		
	test_motor2_rev,		4:	����ָ����
	test_motor3_ewd,		5:	��ָ����
	test_motor3_rev,		6:	��ָ��չ
	test_motor4_ewd,		7:	ʳָ��չ
	test_motor4_rev,		8:	ʳָ����
	test_motor5_ewd,		9:	��Ĵָ����
	test_motor5_rev,		a:	��Ĵָ��չ
	hand_open,					b:	�����ſ���ִ�и����������ָ��չһ���ľ��룬Ϊ��������ת����ȷ�����ִ��ڱպ�״̬
	hand_close,					c:	���ֱպϣ�ͬ�ϣ���ȷ�����ִ�����չ״̬
	
	��ע�������������ָ�1)����ö�ٱ���COMMAND_FLAG��������ָ������;
													2)�����������ھ���TaskProcFun�������µ��������ָ��;
													3)��task.c��task.h���������������
**********************************************************/
//�������ں�������
typedef void (*TASKPROCFUN)(u8 CommandNo);
TASKPROCFUN TaskProcFun[COMMAND_NUMBER] = {	
	Task_wait_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_hand_open, Task_hand_close
};

int main(void)
{
	BSP_Init();  //Ӳ����ʼ��
	while(1)
	{
		TaskProcFun[command](command);  //���ݽ��յ�����������Ӧ������������к�������
	}		
}

