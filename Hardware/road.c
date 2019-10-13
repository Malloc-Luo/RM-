/*  Ѳ�߳��� @ stm32f10x_it.c */

#include "road.h"

RoadMode Road;

void Road_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_IPD;
	gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_5 | GPIO_Pin_11 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB ,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 ;
	GPIO_Init(GPIOA ,&gpio);
	
	Road.Action_Mode = Action_Mode_End;
	Road.Road_Status = Road_Status_DISABLE;
	Road.times = 0;
}

void Road_Mode(void)
{
	
	switch(Road.Action_Mode)
	{
		case Action_Mode_Straight:
			Motor_ROAD_Speed(300, STRAIGHT, 0);
			break;
		case Action_Mode_Left:
			Motor_ROAD_Speed(350, RIGHT, 160);
			break;
		case Action_Mode_Left_Badly:
			Motor_ROAD_Speed(800, RIGHT, 700);
			break;
		case Action_Mode_Right:
			Motor_ROAD_Speed(350, LEFT, 160);
			break;
		case Action_Mode_Right_Badly:
			Motor_ROAD_Speed(800, LEFT, 700);
			break;
		case Action_Mode_End:
			Road.Road_Status = Road_Status_DISABLE;
			Motor_Pause();
			break;
		default:
			break; 
	}
}

