#include "App_Beep.h"



void Robort_Beep_Control(ROBORT_BEEP_TAG beep_status)
{
    if (ROBORT_BEEP_ON==beep_status) 
        STM32_GPIO_SetPin(GPIOA, GPIO_Pin_12, 1);
    else
        STM32_GPIO_SetPin(GPIOA, GPIO_Pin_12, 0); 

}


void Robort_Beep_Init(void)
{
	STM32_GPIO_ConfgPin(U_GPIO_A, U_PIN_12, U_MODE_OUT_PP);
	
    STM32_GPIO_SetPin(GPIOA, GPIO_Pin_12, 0); 
}




