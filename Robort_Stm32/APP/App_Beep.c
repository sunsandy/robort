﻿#include "App_Beep.h"


/*************************************************************************************************
*****
***** 函数名：void  Robort_Beep_Init()
*****
***** 入口参数：beep_status--蜂鸣器状蹋(ROBORT_BEEP_ON-开启, ROBORT_BEEP_OFF-关闭) 
*****
***** 功能描述：蜂鸣器状态控制
***** 
*****							
***** 调用： STM32_GPIO_SetPin()		   
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****
**************************************************************************************************/
void Robort_Beep_Control(ROBORT_BEEP_TAG beep_status)
{
    if (ROBORT_BEEP_ON==beep_status) 
		STM32_GPIO_SetPin( U_GPIO_A, U_PIN_12, 1);
    else
        STM32_GPIO_SetPin( U_GPIO_A, U_PIN_12, 0); 
}

/*************************************************************************************************
*****
***** 函数名：void  Robort_Beep_Init()
*****
***** 入口参数：无
*****
***** 功能描述：蜂鸣器初始化, GPIOA-Pin12-50M, 
***** 
*****							
***** 调用： STM32_GPIO_ConfgPin(), STM32_GPIO_SetPin()		   
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****
**************************************************************************************************/
void Robort_Beep_Init(void)
{
	STM32_GPIO_ConfgPin(U_GPIO_A, U_PIN_12, U_MODE_OUT_PP, U_SPEED_50M);
	
    STM32_GPIO_SetPin( U_GPIO_A, U_PIN_12, 0); 
}




