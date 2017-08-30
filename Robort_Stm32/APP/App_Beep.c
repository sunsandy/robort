#include "App_Beep.h"


/*************************************************************************************************
*****
***** ��������void  Robort_Beep_Init()
*****
***** ��ڲ�����beep_status--������״̣(ROBORT_BEEP_ON-����, ROBORT_BEEP_OFF-�ر�) 
*****
***** ����������������״̬����
***** 
*****							
***** ���ã� STM32_GPIO_SetPin()		   
*****
***** ����ֵ����
*****
***** ���ߣ�Sandy
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
***** ��������void  Robort_Beep_Init()
*****
***** ��ڲ�������
*****
***** ������������������ʼ��, GPIOA-Pin12-50M, 
***** 
*****							
***** ���ã� STM32_GPIO_ConfgPin(), STM32_GPIO_SetPin()		   
*****
***** ����ֵ����
*****
***** ���ߣ�Sandy
****				
****
**************************************************************************************************/
void Robort_Beep_Init(void)
{
	STM32_GPIO_ConfgPin(U_GPIO_A, U_PIN_12, U_MODE_OUT_PP, U_SPEED_50M);
	
    STM32_GPIO_SetPin( U_GPIO_A, U_PIN_12, 0); 
}




