#include "App_Steer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Next is  cloud stage's controller
/////////////////////////////////////////////////////////////////////////////////////////////////////




//���ݽǶ�ֵ�������ռ�ձ�
static unsigned char calDutyCycle(short turnAngle)
{
	uint8 out_dutycycle = 0;
	out_dutycycle = turnAngle * ((ANGLE180_DUTY_CYCLE-ANGLE0_DUTY_CYCLE) * 1.0 / 
                    (ANGLE_MAX_ANGLE - ANGLE_MIN_ANGLE)) + ANGLE0_DUTY_CYCLE;
	
    return out_dutycycle;
}



//1�Ŷ���Ƕȿ���
static void  SteerOneControl(short turnAngle)
{
	uint8 dutyCycle= 0;
	
	dutyCycle = calDutyCycle(turnAngle); //����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM3_PWM1, CLOUD_STAGE_STEER_PERIOD, dutyCycle); //20ms/1.5ms 
}


//2�Ŷ���Ƕȿ���
static void  SteerTwoControl(short turnAngle)
{
	unsigned char dutyCycle = 0;

	dutyCycle= calDutyCycle(turnAngle); //;//����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM3_PWM2, CLOUD_STAGE_STEER_PERIOD, dutyCycle); 
}

//3�Ŷ���Ƕȿ���
static void  SteerThreeControl(short turnAngle)
{
	unsigned char dutyCycle = 0;

	dutyCycle= calDutyCycle(turnAngle); //;//����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM3_PWM3, CLOUD_STAGE_STEER_PERIOD, dutyCycle); 
}
//4�Ŷ���Ƕȿ���
static void  SteerFourControl(short turnAngle)
{
	unsigned char dutyCycle = 0;

	dutyCycle= calDutyCycle(turnAngle); //;//����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM3_PWM4, CLOUD_STAGE_STEER_PERIOD, dutyCycle); 
}
//5�Ŷ���Ƕȿ���
static void  SteerFiveControl(short turnAngle)
{
	unsigned char dutyCycle = 0;

	dutyCycle= calDutyCycle(turnAngle); //;//����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM4_PWM1, CLOUD_STAGE_STEER_PERIOD, dutyCycle); 
}
//6�Ŷ���Ƕȿ���
static void  SteerSixControl(short turnAngle)
{
	unsigned char dutyCycle = 0;

	dutyCycle= calDutyCycle(turnAngle); //;//����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM4_PWM2, CLOUD_STAGE_STEER_PERIOD, dutyCycle); 
}
//7�Ŷ���Ƕȿ���
static void  SteerSevenControl(short turnAngle)
{
	unsigned char dutyCycle = 0;

	dutyCycle= calDutyCycle(turnAngle); //;//����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM4_PWM3, CLOUD_STAGE_STEER_PERIOD, dutyCycle); 
}
//8�Ŷ���Ƕȿ���
static void  SteerEightControl(short turnAngle)
{
	unsigned char dutyCycle = 0;

	dutyCycle= calDutyCycle(turnAngle); //;//����ת�����Ӧ������cnt	

	STM32_TIMER3_PWMControl(TIM4_PWM4, CLOUD_STAGE_STEER_PERIOD, dutyCycle); 
}

/*************************************************************************************************
*****
***** ��������void  Robort_Steer_Controller()
*****
***** ��ڲ�����steerNum  --- ROBORT_STEER1 or ROBORT_STEER2
*****			turnAngle --- 0-180
*****
***** ��������������ĽǶȿ���
***** 
*****							
***** ���ã� ��		   
*****
***** ����ֵ����
*****
***** ���ߣ�Sandy
****				
****
**************************************************************************************************/
char Robort_Steer_Control(ROBORT_STEER_TAG steerNo,  short turnAngle)
{
//	if (steerNo!=ROBORT_STEER1 && steerNo!=ROBORT_STEER2)
//		return -1;
	
	if (turnAngle<0 || turnAngle>180)
		return -1;

	if (steerNo == ROBORT_STEER1)
	{
		SteerOneControl(turnAngle); //1�Ŷ������
	}
	else if( steerNo== ROBORT_STEER2)
	{
		SteerTwoControl(turnAngle); //2�Ŷ������
	}
	else if( steerNo== ROBORT_STEER3)
	{
		SteerThreeControl(turnAngle); //3�Ŷ������
	}
	else if( steerNo== ROBORT_STEER4)
	{
		SteerFourControl(turnAngle); //4�Ŷ������
	}
	else if( steerNo== ROBORT_STEER5)
	{
		SteerFiveControl(turnAngle); //5�Ŷ������
	}
	else if( steerNo== ROBORT_STEER6)
	{
		SteerSixControl(turnAngle); //6�Ŷ������
	}
	else if( steerNo== ROBORT_STEER7)
	{
		SteerSevenControl(turnAngle); //7�Ŷ������
	}
	else if( steerNo== ROBORT_STEER8)
	{
		SteerEightControl(turnAngle); //8�Ŷ������
	}
	


	return 0;
}


void Robort_Steer_Init(void)
{
	TIM3_PWM_Init(20000,71);
	STM32_TIMER3_PWMControl(TIM3_PWM1, CLOUD_STAGE_STEER_PERIOD, 75); //steer1-PA6,Period/H-Voltage 20ms/1.5ms 
	STM32_TIMER3_PWMControl(TIM3_PWM2, CLOUD_STAGE_STEER_PERIOD, 75); //steer2-PA7:Period/H-Voltage 20ms/1.5ms 
	STM32_TIMER3_PWMControl(TIM3_PWM3, CLOUD_STAGE_STEER_PERIOD, 75); //steer3-PB0:Period/H-Voltage 20ms/1.5ms 
	STM32_TIMER3_PWMControl(TIM3_PWM4, CLOUD_STAGE_STEER_PERIOD, 75); //steer4-PB1:Period/H-Voltage 20ms/1.5ms 
	TIM4_PWM_Init(20000,71);
	STM32_TIMER4_PWMControl(TIM4_PWM1, CLOUD_STAGE_STEER_PERIOD, 75); //steer1-PA6: 20ms/1.5ms 
     
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Next is  Arm steer 's controller
/////////////////////////////////////////////////////////////////////////////////////////////////////



