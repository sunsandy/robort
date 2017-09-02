#ifndef _APP_MAIN_H
#define _APP_MAIN_H

#include "Common.h" 
#include "stm32f10x.h"                   //STM32??????????,????
//#include "user_Config.h"                  //???????,??????????,????????
#include "misc.h"
#include "stm32f10x_exti.h" 
#include "stm32f10x_conf.h"
#include "App_Protocol.h"
#include "App_Message.h"
#include "APP_GPS.H"
#include "App_SysDelay.h"
/******************************/
#include "BSP_GPS.h"
#include <string.h>

#define _ENABLE_MODULE_1  1
#define _ENABLE_MODULE_2  1
#define _ENABLE_MODULE_3  1
#define _ENABLE_MODULE_4  1


//Module序号
typedef enum Module_Tag
{
	MODULE_LIGHT = 0,
	MODULE_BEEP,
	MODULE_MOTOR,
	MODULE_STEER,
	
	MODULE_END
}ROBORT_MODULE_TAG;

//Module测试函数
static void Robort_Light_Test(void);
static void Robort_Beep_Test(void);
static void Robort_Motor_Test(void);
static void Robort_Steer_Test(void);

//Module测试函数地址列表
typedef void (* P_DEBUG_FUNC)(void);
static P_DEBUG_FUNC Robort_Debug_Func[MODULE_END] = 
{
	Robort_Light_Test, 
	Robort_Beep_Test,
	Robort_Motor_Test,
	Robort_Steer_Test,
};


#endif
