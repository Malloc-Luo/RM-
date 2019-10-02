#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_Init(GPIOB , &gpio);
	
	GPIO_ResetBits(GPIOA , GPIO_Pin_4);
	GPIO_ResetBits(GPIOA , GPIO_Pin_5);
	GPIO_ResetBits(GPIOB , GPIO_Pin_8);
	GPIO_ResetBits(GPIOB , GPIO_Pin_9);
	
}

void LED_Mode(u8 status)
{
	switch(status)
	{
		case 0xC0:
			LED4 = ON;
		case 0x30:
			LED3 = ON;
		case 0x0C:
			LED2 = ON;
		case 0x03:
			LED1 = ON;
			break;
		default :
			break;
	}
}

