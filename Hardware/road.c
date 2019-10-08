/*  Ñ²Ïß³ÌÐò @ stm32f10x_it.c */

#include "road.h"

RoadMode Road;

void Road_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_11 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB ,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 ;
	GPIO_Init(GPIOB ,&gpio);
	
	Road.Action_Mode = Action_Mode_End;
	Road.Road_Status = Road_Status_DISABLE;
	Road.times = 0;
}

void Road_Mode(void)
{
	if(Bluetooth_RX_Data == PAUSE)
	{
		Road.Road_Status = Road_Status_DISABLE;
		Motor_Pause() ;
	}
	switch(Road.Action_Mode)
	{
		case Action_Mode_Straight:
			Motor_ROAD_Speed(280, STRAIGHT, 0);
			break;
		case Action_Mode_Left:
			Motor_ROAD_Speed(340, RIGHT, 180);
			break;
		case Action_Mode_Left_Badly:
			Motor_ROAD_Speed(380, RIGHT, 220);
			break;
		case Action_Mode_Right:
			Motor_ROAD_Speed(340, LEFT, 180);
			break;
		case Action_Mode_Right_Badly:
			Motor_ROAD_Speed(380, LEFT, 220);
			break;
		case Action_Mode_End:
			Road.Road_Status = Road_Status_DISABLE;
			Motor_Pause();
			break;
		default:
			break; 
	}
}

