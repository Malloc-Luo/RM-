#include "speed.h"

//	TIM3_CH1  PA.6
//	TIM3_CH2  PA.7
//	TIM3_CH3  PB.0
//	TIM3_CH4  PB.1

TIM_ICInitTypeDef tim5 ;

void Speed_Init(void)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef time;
	NVIC_InitTypeDef nvic;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_IPD ;
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	
	GPIO_Init(GPIOA, &gpio);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	
	time.TIM_ClockDivision = TIM_CKD_DIV1;
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_Period = 0xffff;
	time.TIM_Prescaler = 71;
	
	TIM_TimeBaseInit(TIM5, &time);
	
	tim5.TIM_Channel = TIM_Channel_1;
	
	
	
	
	
	
}




