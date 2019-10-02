#include "timer.h"

void TIMER_Init(u8 arr, u8 psc)
{
	TIM_TimeBaseInitTypeDef time ;
	NVIC_InitTypeDef nvic ;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	time.TIM_ClockDivision = 0;
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_Period = arr;
	time.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM5, &time);
	
	
	
	
	
}
