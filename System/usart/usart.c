#include "sys.h"
#include "usart.h"	  
 
#pragma import(__use_no_semihosting)    

u8 USART1_RX_Data;
u8 USART1_RX_LastData;
u8 TX_Status = 0;
u8 RX_Status = 0;
            
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
    
void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);
    USART1->DR = (u8) ch;      
	return ch;
}     

void uart_init(u32 bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         //TX  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 
  GPIO_Init(GPIOA, &GPIO_InitStructure);          
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        //RX   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);               

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   
	NVIC_Init(&NVIC_InitStructure);
  
	USART_InitStructure.USART_BaudRate = bound;                                    
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         
	USART_InitStructure.USART_Parity = USART_Parity_No;                            
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               
	
	USART_Init(USART1, &USART_InitStructure);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
  USART_Cmd(USART1, ENABLE);                    
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART1_RX_Data = USART_ReceiveData(USART1);
		
		if(USART1_RX_Data<=0x0f)
		{
			switch(USART1_RX_Data)
			{
				
				
			}
	  }
		else if(USART1_RX_Data == ERROR)
			Send_to_Arduino(USART1_RX_LastData);
		else if(USART1_RX_Data == DONE)
			TX_Status = 1;
		else
		{
			Send_to_Arduino(WRONG);
			TX_Status = 0;
		}
		
		switch(GAME_STATUS)
		{
			case 0x03:
				Set_Speed = USART_ReceiveData(USART1);
				break;
			case 0x0C:
				break;
			case 0x30:
				break;
			case 0xC0:
				break;
			default :
				break;
		}
	}
}

void Send_to_Arduino(u8 data)
{
	USART_SendData(USART1, data);
}

