#include "Common.h" 

uchar Task_Uart1_Rx =0;
uchar Tx_Buffer[Tx_Array_Size];			              //发送缓存区
uchar Rx_Buffer[Rx_Array_Size];			              //接受缓存区
uchar Rx_Process_Buffer[Rx_Array_Size];	          //接受处理缓存区
uchar Tx_Ptr,Rx_Ptr; 	 		               	        // 发送接收指针
uchar Tx_Tail,Rx_Tail;    			   	              //发送接收尾指针
uchar Rx_Step=0;							                      // 接收步骤
uchar Tx_Count,Rx_Count;				                  // 发送接收计时
uchar Temp=0;
uchar i=0;
uchar DMA1_Uart_Status=0;



void UART2_Init(ulong bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART2 GPIO config */
	/* Configure USART2 Tx (PA.02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Rx (PA.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = bound;                //GPS模块默认使用波特率：9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure); 

	USART_Cmd(USART2, ENABLE);
}

void UART3_Init(ulong bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* USART2 GPIO config */
	/* Configure USART2 Tx (PA.02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART2 Rx (PA.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = bound;                //GPS模块默认使用波特率：9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure); 

	USART_Cmd(USART3, ENABLE);
}
void UART1_Init( ulong bound)
{

	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	USART_DeInit(USART1);  //复位串口1
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9

	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

	//Usart1 NVIC 配置

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART1, ENABLE);                    //使能串口 
}

void UART_Init(void)
{
	UART1_Init(9600);
	//UART2_Init(9600);
	//UART3_Init(9600);
	DMA_Uart1_Init();
}


void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		Rx_Buffer[Rx_Ptr] =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		if(Rx_Ptr>(Rx_Array_Size-1)) Rx_Ptr=0;
		Rx_Ptr++;
		switch (Rx_Step)										//开始标志
		{
			case 0x00:											  //校验帧头
				Rx_Count=0;
				if(Rx_Buffer[0]==0xFF) 
					{
					Rx_Step++; 
					}
   				else Rx_Ptr=0;
				break;
			case 0x01:											//本机模块号：0x01
				Rx_Count=0;
				if(Rx_Buffer[1]==0x01)
					{
					Rx_Step++;
					}	
				else {           
						Rx_Ptr=0;
						Rx_Step=0;
						}
				break;
      case 0x02:											
			    Rx_Count=0;
				if(Rx_Ptr==4)
				{
					Temp=Rx_Buffer[3];
					Rx_Tail= ((u16)Rx_Buffer[2]<<8 | Temp) +7;			
			    if (Rx_Tail>(Rx_Array_Size-1))			// 长度无效
					{
						Rx_Ptr=0;
						Rx_Step=0;
						}
					else Rx_Step++;
					}
				break;
			case 0x03:											        //提取数据
				Rx_Count=0;
				if(Rx_Ptr==Rx_Tail)
				{
					for ( i=0;i<Rx_Tail;i++){
						Rx_Process_Buffer[i]=Rx_Buffer[i]; 
						}
					Rx_Ptr=0;
					Rx_Tail=0;
					Rx_Step=0;
					Task_Uart1_Rx=1;
					}
				break;
			default:;  											// 
			}
	}
		
}


int Crc16(uchar *ptr, int count)
{
	int crc, i;
	crc = 0;
	while (--count >= 0){
		crc = (crc ^ (((int)*ptr++) << 8));
		for (i = 0; i < 8; ++i)
		if (crc & 0x8000)
		crc = ((crc << 1) ^ 0x1021);
		else
		crc = crc << 1;
	}
	return (crc & 0xFFFF);
}

//void UART_Rx_process(void)// 串口1通信处理程序
//{
//	uint temp;
//	int crc_code;

//	temp=Rx_Process_Buffer[3];//数据长度
//	temp=(temp<<8)+Rx_Process_Buffer[2]+7;
//	crc_code=Crc16(&Rx_Process_Buffer[1],5); //CRC校验
//	if ((Rx_Process_Buffer[6]==(uchar)(crc_code&0xff))&&
//		(Rx_Process_Buffer[7]==(uchar)(crc_code>>8)))
//	{
//		switch (Rx_Process_Buffer[4])
//		{
//			
//			case 0x00://停止命令
//						   
//				break;
//			case 0x01://前进命令
//			   
//				break;
//			case 0x02://后退命令
//				
//				break;
//			case 0x03://左转命令
//				
//				break;
//			case 0x04://右转命令
//				
//				break;
//			case 0x05://水平舵机命令左右
//				Horizontal_Angle=Rx_Process_Buffer[5];
//			  Horizontal_Angle=Horizontal_Angle*100/180;
//			  H_ACT_Ctrl(Horizontal_Angle);
//				break;
//			case 0x06://垂直舵机命令上下
//				
//				break;
//			case 0x07://舵机X命令
//						   
//				break;
//			case 0x08://左侧速度档命令
//			   
//				break;
//			case 0x09://右侧速度档命令
//				
//				break;
//			case 0x0A://开灯命令
//				
//				break;
//			case 0x0B://关灯命令
//				
//				break;
//			default:
//				
//				break;
//			}
//		}
//}

void STM32_UART_Write(u8 uartNo, void *src, u16 len)
{
	u8 t=0;
	if( 1 ==uartNo){
		for(t=0;t<len;t++)
			{
				USART1->DR =*((u8*)src+t);
				while((USART1->SR&0X40)==0);//查询发送是否结束
			}
		}
	else if( 2==uartNo){
		for(t=0;t<len;t++)
			{
				USART2->DR =*((u8*)src+t);
				while((USART2->SR&0X40)==0);//查询发送是否结束
			}
		}
}


/// 重定向c库函数printf到USART1
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	
		return (ch);
}

/// 重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
 u8 STM32_UART_Read(u8 uartNo, void *dst, u16 len)
 {
	 u8 i=0;
	 u16 dat_len = 0;
	 u16 crc_code = 0;
	 
	if( Task_Uart1_Rx)
	{
		dat_len = ((u16)Rx_Process_Buffer[2]<<8 | Rx_Process_Buffer[3])+7;
		
		crc_code=Crc16(&Rx_Process_Buffer[0],dat_len-2); //CRC code calculation
		
		//CRC check
		if ((crc_code&0xff == Rx_Process_Buffer[dat_len-1]) && ((crc_code>>8)&0xff == Rx_Process_Buffer[dat_len-2]))
		{
			//assert(0);
			return 0;
		}		
		
		for(i=0;i<len;i++ )
			*((u8*)dst+i) =Rx_Process_Buffer[i];
		
		Task_Uart1_Rx=0;
		return 1;
	}	
	return 0;
 }
 
 
 //***************************************需要DMA减负******************************************
 //***************************************后期需要升级添加函数*********************************

 void DMA_Uart1_Init( void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	DMA_DeInit(DMA1_Channel4);   //将DMA的通道1寄存器重设为缺省值
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;  //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Tx_Buffer;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = 10;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// DMA2 Channel Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断

	/*使能DMA*/
	DMA_Cmd (DMA1_Channel4,ENABLE);		
    
  /* 配置串口 向 DMA发出TX请求 */
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}


void DMA1_DATA_Trans_Task_ON()
{
	DMA1_Uart_Status=1;
}

void DMA1_DATA_Trans_Task_OFF()
{
	DMA1_Uart_Status=0;
}
u8 DMA1_Uart1_Status_Get( void)
{
	return DMA1_Uart_Status;
}
void STM32_UART1_Write(u8* Tx_Buff,u8 Data_Len)
{
	DMA1_Channel4->CCR&=~(1<<0);
	DMA1_Channel4->CMAR=(u32)Tx_Buff;
	DMA1_Channel4->CNDTR=Data_Len;
	DMA1_Channel4->CCR|=(1<<0);
	DMA1_DATA_Trans_Task_ON();
}
void Upload_ProcessDMAIRQ( void)
{
	if( DMA_GetITStatus(DMA1_IT_TC4))
	{
		DMA1_DATA_Trans_Task_OFF();
		DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
	}
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

/*********************************************END OF FILE**********************/
