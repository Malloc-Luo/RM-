/* @ stm32f10x_it.c */
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

/*巡线专用旋转程序*/

void Road_Mode_Span(int16_t SpanDirection, int16_t speed)
{
	if(SpanDirection == CLOCKWISE)
	{
		ForLeft(speed-60, F);
		BackLeft(speed-60, F);
		
		ForRight(speed+50, B);
		BackRight(speed+50, B);
		
	}
	else
	{
		ForLeft(speed+50, B);
		BackLeft(speed+50, B);
		
		ForRight(speed-60, F);
		BackRight(speed-60, F);
	}
}

void Road_Mode(void)
{
	switch(Road.Action_Mode)
	{
		case Action_Mode_Inline:
			Motor_ROAD_Speed(400, STRAIGHT, 0);
			break;
		case Action_Mode_Straight:
			Motor_ROAD_Speed(450, STRAIGHT, 0);
			break;
		case Action_Mode_Left:
			Motor_ROAD_Speed(450, RIGHT, 350);
			break;
		case Action_Mode_Left_Badly:
			Motor_Pause();
			Road_Mode_Span(CLOCKWISE, 450);
			break;
		case Action_Mode_Right:
			Motor_ROAD_Speed(450, LEFT, 350);
			break;
		case Action_Mode_Right_Badly:
			Motor_Pause();
			Road_Mode_Span(ANTICLOCKWISE, 450);
			break;
		case Action_Mode_End:
			Road.Road_Status = Road_Status_DISABLE;
			Motor_Pause();
			break;
		default:
			break; 
	}
}

