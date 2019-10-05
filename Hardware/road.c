#include "road.h"

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
}

void Road_Mode(void)
{
	static u8 times = 0;
	
	while(1)
	{
		if(Bluetooth_RX_Data == PAUSE)
		{
			Motor_Pause();
			break;
		}
		if(L1==WHITE && L2==BLACK && M0==BLACK && R2==BLACK && R1==WHITE)
		{
			Motor_ROAD_Speed(300, STRAIGHT, 0);
		}
		if(L1==WHITE && (L2==WHITE || R1==BLACK) )
		{
			Motor_ROAD_Speed(320, RIGHT, 80);
		}
		if(L1==WHITE && L2==WHITE && R1==BLACK)
		{
			Motor_ROAD_Speed(340, RIGHT, 100);
		}
		if(R1==WHITE && (R2==WHITE || L1==BLACK) )
		{
			Motor_ROAD_Speed(320, LEFT, 80);
		}
		if(R1==WHITE && R2==WHITE && L1==BLACK )
		{
			Motor_ROAD_Speed(340, LEFT, 100);
		}
		if(R1==BLACK && L1==BLACK )
		{
			times ++ ;
			if(times >= 3)
			{
				delay_ms(100);
				Motor_Pause();
				Motor_SPAN_90Degree(250, CLOCKWISE);
				GAME_STATUS = GAME_STATUS <<2;
				Send_to_Arduino(DONE);
			}
		}
	}
}

