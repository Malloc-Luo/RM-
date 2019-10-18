#include "valve.h"

VALVE_SetTypeDef Valve;

void Valve_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP ;
	gpio.GPIO_Pin = GPIO_Pin_4 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB, &gpio);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
	Valve.Valve_EN = DISABLE ;
	Valve.Valve_Status = OPEN ;
}

void Valve_Control(void)
{
	if(Valve.Valve_Status == OFF)
	{
		Valve_VALVE1 = OFF;
	}
	else if(Valve.Valve_Status == ON)
	{
		Valve_VALVE1 = ON;
	}
}

