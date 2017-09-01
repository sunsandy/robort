#include "App_Motor.h"

static uint8 gRobortSpeed_L = 0;
static uint8 gRobortSpeed_R = 0;

static uint8 gFlagSpeedRset = 0;
   
   


static void Set_Motor_Direction(MOTOR_TAG motorNo, DIRECTION_TAG  dir)
{
    static MOTOR_TAG preMotorNo = MOTOR_NONE;
    static DIRECTION_TAG preDir = MOTOR_NONE;
    
    if (preMotorNo==motorNo && preDir==dir)
    {
        return ;
    }
    
    preMotorNo = motorNo;
    preDir = dir;
    
    switch (motorNo)
    {
     case MOTOR_LT:
     {
        if (dir == DIR_POSITIVE)
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_9, 1);   // DIR1=HIGH
        }
        else
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_9, 0);  // DIR1=LOW
        }
     }
     break;
     
     case MOTOR_RT:
        if (dir == DIR_POSITIVE)
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_8, 1);   // DIR2=HIGH
        }
        else
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_8, 0);    // DIR2=LOW
        }
     break;
     case MOTOR_LB:
        if (dir == DIR_POSITIVE)
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_7, 1);   // DIR3=HIGH
        }
        else
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_7, 0);    // DIR3=LOW
        }
     break;
     case MOTOR_RB:
        if (dir == DIR_POSITIVE)
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_6, 1);   // DIR4=HIGH
        }
        else
        {
             STM32_GPIO_SetPin(GPIOC, GPIO_Pin_6, 0);   // DIR4=LOW
        }
     break;  

     default: break;
    }
    
    return ;
}


static uint16  CalPWMDutyCycle(unsigned char speed)
{
	uint16 DutyCycle = 0;

	DutyCycle = (uint16) (speed*1.0 / 100 * 1000);
	

	return DutyCycle;
}

//speed: 0~100
static void Set_Motor_Speed(MOTOR_TAG motorNo, uint8 speed)
{
    static MOTOR_TAG preMotorNo;
    static uint8    preSpeed;
    uint16 ratio = 0;
    
    if (preMotorNo==motorNo && preSpeed==speed)
    {
        return ;
    }
    
    preMotorNo = motorNo;
    preSpeed = speed;
    
    ratio =  CalPWMDutyCycle(speed);
    
    switch (motorNo)
    {
     case MOTOR_LT:
        STM32_TIMER2_PWMControl(TIM2_PWM1, MOTOR_PERIOD_DEFAULT, ratio);
     break;
     case MOTOR_RT:
        STM32_TIMER2_PWMControl(TIM2_PWM2, MOTOR_PERIOD_DEFAULT, ratio);
     break;
     case MOTOR_LB:
        STM32_TIMER2_PWMControl(TIM2_PWM3, MOTOR_PERIOD_DEFAULT, ratio);
     break;
     case MOTOR_RB:
        STM32_TIMER2_PWMControl(TIM2_PWM4, MOTOR_PERIOD_DEFAULT, ratio);
     break;  

     default: break;
    }
    
    return ;
}



void Robort_Direction_Control(ROBORT_DIRECTION_TAG dir, uint8 speed)
{
    uint8 sysSpeed_L = (gFlagSpeedRset==0) ? 30 : gRobortSpeed_L;
    uint8 sysSpeed_R = (gFlagSpeedRset==0) ? 30 : gRobortSpeed_R;
    
    switch (dir)
    {
     case ROBORT_STOP:
     {
           Set_Motor_Direction( MOTOR_LT,  DIR_STOPPED);   //left-top motor stop
           Set_Motor_Speed( MOTOR_LT,  0);       //speed=0 so stopped
           
           Set_Motor_Direction( MOTOR_RT,  DIR_STOPPED);   //right-top motor stop
           Set_Motor_Speed( MOTOR_RT,  0);
                      
           Set_Motor_Direction( MOTOR_LB,  DIR_STOPPED);   //left-bottom motor stop
           Set_Motor_Speed( MOTOR_LB,  0);
           
           Set_Motor_Direction( MOTOR_RT,  DIR_STOPPED);   //right-bottom motor stop
           Set_Motor_Speed( MOTOR_RB,  0);
            
           break;
     }
     case ROBORT_FORWARD:
     {
           Set_Motor_Direction( MOTOR_LT,  DIR_POSITIVE);   //left-top motor stop
           Set_Motor_Speed( MOTOR_LT,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RT,  DIR_POSITIVE);   //right-top motor stop
           Set_Motor_Speed( MOTOR_RT,  sysSpeed_R);
                      
           Set_Motor_Direction( MOTOR_LB,  DIR_POSITIVE);   //left-bottom motor stop
           Set_Motor_Speed( MOTOR_LB,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RB,  DIR_POSITIVE);   //right-bottom motor stop
           Set_Motor_Speed( MOTOR_RB,  sysSpeed_R);
            
        break;
     }
     case ROBORT_BACK:
     {
           Set_Motor_Direction( MOTOR_LT,  DIR_NEGTIVE);   //left-top motor stop
           Set_Motor_Speed( MOTOR_LT,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RT,  DIR_NEGTIVE);   //right-top motor stop
           Set_Motor_Speed( MOTOR_RT,  sysSpeed_R);
                      
           Set_Motor_Direction( MOTOR_LB,  DIR_NEGTIVE);   //left-bottom motor stop
           Set_Motor_Speed( MOTOR_LB,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RB,  DIR_NEGTIVE);   //right-bottom motor stop
           Set_Motor_Speed( MOTOR_RB,  sysSpeed_R);
            
        break;
     }
     case ROBORT_LEFT:
     {
           Set_Motor_Direction( MOTOR_LT,  DIR_NEGTIVE);   //left-top motor stop
           Set_Motor_Speed( MOTOR_LT,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RT,  DIR_POSITIVE);   //right-top motor stop
           Set_Motor_Speed( MOTOR_RT,  sysSpeed_R);
                      
           Set_Motor_Direction( MOTOR_LB,  DIR_NEGTIVE);   //left-bottom motor stop
           Set_Motor_Speed( MOTOR_LB,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RB,  DIR_POSITIVE);   //right-bottom motor stop
           Set_Motor_Speed( MOTOR_RB,  sysSpeed_R);
            
        break;
     } 
     case ROBORT_RIGHT:
     {
           Set_Motor_Direction( MOTOR_LT,  DIR_POSITIVE);   //left-top motor stop
           Set_Motor_Speed( MOTOR_LT,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RT,  DIR_NEGTIVE);   //right-top motor stop
           Set_Motor_Speed( MOTOR_RT,  sysSpeed_R);
                      
           Set_Motor_Direction( MOTOR_LB,  DIR_POSITIVE);   //left-bottom motor stop
           Set_Motor_Speed( MOTOR_LB,  sysSpeed_L);
           
           Set_Motor_Direction( MOTOR_RB,  DIR_NEGTIVE);   //right-bottom motor stop
           Set_Motor_Speed( MOTOR_RB,  sysSpeed_R);
            
        break;
     } 
     
     default: break;
    }  
}

//if set speed, then robort move by the new speed next time
void  Robort_Speed_Control(ROBORT_SPEED_TAG robort_dir, unsigned char robort_speed)
{
    gFlagSpeedRset = 1;   //标志为1，代表客户端设定了速度
    
    switch (robort_dir)
    {
     case ROBORT_SPEED_L:
     {
          gRobortSpeed_L =  robort_speed;
          break;
     }
     case ROBORT_SPEED_R:
     {
          gRobortSpeed_R =  robort_speed;
          break;
     }
  
     default: break;
    }  
    
}

void Robort_Motor_Init(void)
{
//   STM32_GPIO_ConfigPin(GPIOC, GPIO_Pin_6, out); 
//   STM32_GPIO_ConfigPin(GPIOC, GPIO_Pin_7, out); 
//   STM32_GPIO_ConfigPin(GPIOC, GPIO_Pin_8, out); 
//   STM32_GPIO_ConfigPin(GPIOC, GPIO_Pin_9, out); 
   
   GPIO_InitTypeDef GPIO_InitStructure;  
 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 			
   /* Pin9-DIR1, Pin8-DIR2, Pin7-DIR3, Pin6-DIR4 */
   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;			
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);  
    
   STM32_GPIO_SetPin(GPIOC, GPIO_Pin_6, 1);
   STM32_GPIO_SetPin(GPIOC, GPIO_Pin_7, 1);
   STM32_GPIO_SetPin(GPIOC, GPIO_Pin_8, 1);
   STM32_GPIO_SetPin(GPIOC, GPIO_Pin_9, 1);
     
   TIM2_PWM_Init(MOTOR_PERIOD_DEFAULT,71);
   STM32_TIMER2_PWMControl(TIM2_PWM1, MOTOR_PERIOD_DEFAULT, 0); // PWM out low 
   STM32_TIMER2_PWMControl(TIM2_PWM2, MOTOR_PERIOD_DEFAULT, 0); // PWM out low 
   STM32_TIMER2_PWMControl(TIM2_PWM3, MOTOR_PERIOD_DEFAULT, 0); // PWM out low 
   STM32_TIMER2_PWMControl(TIM2_PWM4, MOTOR_PERIOD_DEFAULT, 0); // PWM out low  
   
   
}








