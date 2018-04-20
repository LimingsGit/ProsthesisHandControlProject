/*
假手控制板程序
2018/3/30 by ZhangLiming
*/
#include  "task.h"

u8 command = wait_command;
/********************************************************
	命令										对应的状态							
	wait_command,				0:	缺省命令/空闲状态
	test_motor1_ewd,		1:  小拇指弯曲
	test_motor1_rev,		2:	小拇指伸展
	test_motor2_ewd,		3:	无名指伸展		
	test_motor2_rev,		4:	无名指弯曲
	test_motor3_ewd,		5:	中指弯曲
	test_motor3_rev,		6:	中指伸展
	test_motor4_ewd,		7:	食指伸展
	test_motor4_rev,		8:	食指弯曲
	test_motor5_ewd,		9:	大拇指弯曲
	test_motor5_rev,		a:	大拇指伸展
	hand_open,					b:	假手张开：执行该命令，各个手指伸展一定的距离，为避免电机堵转，请确保假手处于闭合状态
	hand_close,					c:	假手闭合：同上，请确保假手处于伸展状态
	hand_reset,        	d； 发送该指令意味着假手目前已经处于完全伸展状态
	
	备注：若想继续增添指令，1)请在枚举变量COMMAND_FLAG后增加新指令名称;
													2)在命令处理函数入口矩阵TaskProcFun中增加新的命令处理函数指针;
													3)在task.c、task.h中增加命令处理函数；
**********************************************************/
//命令处理入口函数矩阵
typedef void (*TASKPROCFUN)(u8 CommandNo);
TASKPROCFUN TaskProcFun[COMMAND_NUMBER] = {	
	Task_wait_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_test_func, Task_test_func,
	Task_hand_open, Task_hand_close,
	Task_hand_reset
};

int main(void)
{
	BSP_Init();  //硬件初始化
	while(1)
	{
		TaskProcFun[command](command);  //根据接收到的命令，进入对应的命令处理函数进行函数处理
	}		
}

