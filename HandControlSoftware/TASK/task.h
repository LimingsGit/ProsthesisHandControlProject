#ifndef __TASK_H_
#define __TASK_H_
#include  "sys.h"

typedef enum COMMAND_FLAG
{	
	wait_command,				//0
	test_motor1_ewd,		//1       小拇指弯曲
	test_motor1_rev,		//2				小拇指伸展
	test_motor2_ewd,		//3				无名指伸展		
	test_motor2_rev,		//4				无名指弯曲
	test_motor3_ewd,		//5				中指弯曲
	test_motor3_rev,		//6				中指伸展
	test_motor4_ewd,		//7				食指伸展
	test_motor4_rev,		//8				食指弯曲
	test_motor5_ewd,		//9				大拇指弯曲
	test_motor5_rev,		//a				大拇指伸展
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
