#include "Common.h" 
#include "stm32f10x.h"                   //STM32??????????,????
//#include "user_Config.h"                  //???????,??????????,????????
#include "misc.h"
#include "stm32f10x_exti.h" 
#include "stm32f10x_conf.h"
#include "App_Protocol.h"
#include "App_Message.h"
#include "APP_GPS.H"
/******************************/
#include "BSP_GPS.h"
#include <string.h>

#define USE_FULL_ASSERT 1
extern void nmea_decode_test(void);
static void Hardware_Test(void);


App_Robort_Dat_Tag g_ProtocolData = {0};
    
u8 u[17]="\r\nDMA 测试成功\r\n";
u8 w[17]="\r\nDMA 中断测试\r\n";

/****************************************************************************************
// System clock is configured defaultly in /STARTUP/startup_stm32f10x_hd.s line 152,
// in the function SystemInit(), by define SYSCLK_FREQ_72MHz.
//                                                                 
//                                               -- GPIOA
//                                              |-- GPIOC
//                    --PreScale1 - APB2(72M) — | 
//                   |
//                   |
// HSE(8M)->PLL(9) - |--PreScale1 - HCLK(72M)
//                   |
//                   |                          -- 72M(2x) -- TIMER2
//                   |                         |
//                   |__PreScale2 - APB1(36M) -|
//
//
*****************************************************************************************/
int main(void)
{
	  
	delay_init();
	TIMER_Init();
	Robort_Beep_Init();
	Robort_Light_Init();
	Robort_Motor_Init();
	Robort_Steer_Init();
	Robort_Uart_Init();
	//Robort_GPS_Init(); 
	//GPS_DATA_Init(); 
//		printf("\r\n系统初始化完毕\r\n");
    //Steer_Test( );

	//assert_param(0);
    while (1)
    {
		Hardware_Test();
		__NOP; 
	//Robort_Get_Nema();
//		if (Robort_Receive_Frame(&g_ProtocolData) == RET_OK)
//		{
//			Protocol_Parser(&g_ProtocolData);		
//		}
//		if(Task_50ms)
//		{
//			Task_50ms=0;	
//			GPS_Message_Upload();
//		}
    }

 
}


static void Hardware_Test()
{

     App_Robort_Dat_Tag ProtocolData = {0};
     uSensorInfoTag SensorEntry = {0};
			 
//	while (1)
//	{
//		Robort_Light_Control( ROBORT_LIGHT_ONE, ROBORT_LIGHT_ON);
//		delay_ms(1000);
//		Robort_Light_Control( ROBORT_LIGHT_ONE, ROBORT_LIGHT_OFF);
//		delay_ms(1000);
//	}
/******************************************************************************************
						BEEP TEST
******************************************************************************************/   
//     Robort_Beep_Control(ROBORT_BEEP_ON);
//     delay_ms(1000);
//     Robort_Beep_Control(ROBORT_BEEP_OFF);
//     delay_ms(1000);
     
///******************************************************************************************
//						LIGHT TEST
//******************************************************************************************/     
//     Robort_Light_Control( ROBORT_LIGHT_ONE, ROBORT_LIGHT_ON);
//     delay_ms(1000);
//     Robort_Light_Control( ROBORT_LIGHT_ONE, ROBORT_LIGHT_OFF);
//     delay_ms(1000);
//     
///******************************************************************************************
//						MOTOR TEST
//******************************************************************************************/
     //Robort_Direction_Control(ROBORT_STOP, 0);
//     delay_ms(10000);

//     Robort_Direction_Control(ROBORT_BACK, 50);
//     delay_ms(10000);
     
//     Robort_Direction_Control(ROBORT_FORWARD, 50);
	 Robort_Speed_Control(ROBORT_SPEED_L, 60);
//	 Robort_Speed_Control(ROBORT_SPEED_R, 60);
//	 Robort_Direction_Control(ROBORT_FORWARD, 60);
//     delay_ms(10000);
//     

//	while(1);
     
//     Robort_Direction_Control(ROBORT_LEFT, 50);
//     delay_ms(10000);
//     
//     Robort_Direction_Control(ROBORT_RIGHT, 50);
//     delay_ms(1000);
//     
///******************************************************************************************
//                       STEER TEST
//******************************************************************************************/
     Robort_Steer_Control(ROBORT_STEER1,  90); //Stay 90 angle
     Robort_Steer_Control(ROBORT_STEER2,  90); //Stay 90 angle
     delay_ms(2000);
	 
	 Robort_Steer_Control(ROBORT_STEER1,  0); //Stay 0 angle
     Robort_Steer_Control(ROBORT_STEER2,  0); //Stay 0 angle
     delay_ms(2000);
    
     Robort_Steer_Control(ROBORT_STEER1,  180); //Stay 90 angle
     Robort_Steer_Control(ROBORT_STEER2,  180); //Stay 90 angle
     delay_ms(2000);
//    
///******************************************************************************************
//                       ADC TEST
//******************************************************************************************/
// 
//     Robort_Get_Sensor_Data(HUMIDITY_TYPE, &SensorEntry);
//     Robort_Get_Sensor_Data(TEMPERATURE_TYPE, &SensorEntry);
//     Robort_Get_Sensor_Data(ENERGY_TYPE, &SensorEntry);
//     Robort_Get_Sensor_Data(DISTANCE_TYPE, &SensorEntry);
//     
///******************************************************************************************
//                       UART TEST
//******************************************************************************************/     

//     Robort_Receive_Frame(&ProtocolData);
//     Robort_Send_Frame((void *)&ProtocolData);
     
    
}


/******************* (C) COPYRIGHT 2015 X-SPACE *****END OF FILE****/



/*********************************************END OF FILE**********************/


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	printf("wrong file:%s,wrong line:%d\n", file, line); 
  /* Infinite loop */
  while (1)
  {
  }
}
#endif