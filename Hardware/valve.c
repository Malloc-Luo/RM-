#include "valve.h"

void Valve_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP ;
	gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB, &gpio);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

