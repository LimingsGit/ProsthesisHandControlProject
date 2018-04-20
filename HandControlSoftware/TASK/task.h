#ifndef __TASK_H_
#define __TASK_H_
#include  "sys.h"

typedef enum COMMAND_FLAG
{	
	wait_command,				//0
	test_motor1_ewd,		//1       СĴָ����
	test_motor1_rev,		//2				СĴָ��չ
	test_motor2_ewd,		//3				����ָ��չ		
	test_motor2_rev,		//4				����ָ����
	test_motor3_ewd,		//5				��ָ����
	test_motor3_rev,		//6				��ָ��չ
	test_motor4_ewd,		//7				ʳָ��չ
	test_motor4_rev,		//8				ʳָ����
	test_motor5_ewd,		//9				��Ĵָ����
	test_motor5_rev,		//a				��Ĵָ��չ
	hand_open,					//b
	hand_close,					//c
	hand_reset,					//d
	COMMAND_NUMBER
}Comand_Flag;

void BSP_Init(void);	
void Task_wait_func(u8 CommandNo);
void Task_test_func(u8 CommandNo);
void Task_hand_open(u8 CommandNo);
void Task_hand_close(u8 CommandNo);
void Task_hand_reset(u8 CommandNo);

#endif
