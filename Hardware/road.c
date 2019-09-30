#include "road.h"

void Road_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA ,&gpio);
	GPIO_Init(GPIOB ,&gpio);
	
}

