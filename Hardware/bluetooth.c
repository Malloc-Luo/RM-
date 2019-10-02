#include "bluetooth.h"

u8 Bluetooth_RX_Data;

void Bluetooth_Init(u32 bound)
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart;
	NVIC_InitTypeDef nvic;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&gpio);
	
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &gpio);
	
	nvic.NVIC_IRQChannel = USART2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x03;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	usart.USART_BaudRate = bound;                                    
	usart.USART_WordLength = USART_WordLength_8b;                    
	usart.USART_StopBits = USART_StopBits_1;                        
	usart.USART_Parity = USART_Parity_No;                            
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART2, &usart);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Bluetooth_RX_Data = USART_ReceiveData(USART2);
		
		if(Bluetooth_RX_Data<=0x0f)
		{
			switch(Bluetooth_RX_Data)
			{
				case BEGIN:
					Send_to_Arduino(SIGNAL1);
					GAME_STATUS = (GAME_STATUS<<2);
					break;
				default :
					break;
			}
		}
	}
}

