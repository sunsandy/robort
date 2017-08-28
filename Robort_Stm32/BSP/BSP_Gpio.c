//#include "Common.h" 

#include "BSP_Gpio.h"

void STM32_GPIO_SetPin( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, u8 val)
{
	if( 1==val)
		GPIO_SetBits(GPIOx,GPIO_Pin);						 
	else if( 0== val)
		GPIO_ResetBits( GPIOx, GPIO_Pin);
}

void STM32_GPIO_ConfgPin(uint8_t gpio, uint8_t pin, uint8_t mode)
{
	GPIO_TypeDef *in_gpio = GPIOA;
	uint16_t in_pin = GPIO_Pin_0;
	GPIOMode_TypeDef in_mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDef GPIO_InitStructure;  
 	
	switch (gpio)
	{
		case U_GPIO_A:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			break;
		case U_GPIO_B:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		break;
		case U_GPIO_C:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		break;
		case U_GPIO_D:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		break;
		case U_GPIO_E:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		break;
		case U_GPIO_F:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		break;
		case U_GPIO_G:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		break;
		default:
			assert_param(0);
		break;
	}
	
	switch (pin)
	{
		case U_PIN_0: in_pin = GPIO_Pin_0; break;
		case U_PIN_1: in_pin = GPIO_Pin_1; break;
		case U_PIN_2: in_pin = GPIO_Pin_2; break;
		case U_PIN_3: in_pin = GPIO_Pin_3; break;
		case U_PIN_4: in_pin = GPIO_Pin_4; break;
		case U_PIN_5: in_pin = GPIO_Pin_5; break;
		case U_PIN_6: in_pin = GPIO_Pin_6; break;
		case U_PIN_7: in_pin = GPIO_Pin_7; break;
		case U_PIN_8: in_pin = GPIO_Pin_8; break;
		case U_PIN_9: in_pin = GPIO_Pin_9; break;
		case U_PIN_10: in_pin = GPIO_Pin_10; break;
		case U_PIN_11: in_pin = GPIO_Pin_12; break;
		case U_PIN_12: in_pin = GPIO_Pin_12; break;
		case U_PIN_13: in_pin = GPIO_Pin_13; break;
		case U_PIN_14: in_pin = GPIO_Pin_14; break;
		case U_PIN_15: in_pin = GPIO_Pin_15; break;

		default:
//assert(0);
		break;
	}

	switch (mode)
	{
		case U_MODE_AIN: 		in_mode = GPIO_Mode_AIN; 			break;
		case U_MODE_FLOATING: 	in_mode = GPIO_Mode_IN_FLOATING; 	break;
		case U_MODE_IPD: 		in_mode = GPIO_Mode_IPD; 			break;
		case U_MODE_IPU: 		in_mode = GPIO_Mode_IPU; 			break;
		case U_MODE_OUT_OD: 	in_mode = GPIO_Mode_Out_OD; 		break;
		case U_MODE_OUT_PP:		in_mode = GPIO_Mode_Out_PP; 		break;
		case U_MODE_AF_OD: 		in_mode = GPIO_Mode_AF_OD; 			break;
		case U_MODE_AF_PP: 		in_mode = GPIO_Mode_AF_PP; 			break;
		default:
			//assert(0);
		break;
	}

	
	
	GPIO_InitStructure.GPIO_Pin   = in_pin;      
  	GPIO_InitStructure.GPIO_Mode  = in_mode;		
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(in_gpio, &GPIO_InitStructure); 
}
