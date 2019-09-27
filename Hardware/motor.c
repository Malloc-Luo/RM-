#include "motor.h"

//----------------------------------
/*TIM2_CH1  PA.0
  TIM2_CH2  PA.1
	TIM3_CH1  PA.6
	TIM3_CH2  PA.7
*/

void Motor_Init(void)
{
	GPIO_InitTypeDef gpio;
	NVIC_InitTypeDef nvic;
	TIM_TimeBaseInitTypeDef time;
	TIM_OCInitTypeDef oc;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_6 |GPIO_Pin_7 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&gpio);
	
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannel = TIM2_IRQn ;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	
	NVIC_Init(&nvic);
	
	nvic.NVIC_IRQChannel = TIM3_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvic.NVIC_IRQChannelSubPriority = 0x02;
	
	NVIC_Init(&nvic);
	
	time.TIM_ClockDivision = 0;
	time.TIM_Prescaler = 0;
	time.TIM_Period = 899;
	time.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM2, &time);
	TIM_TimeBaseInit(TIM3, &time);
	
	oc.TIM_OCMode = TIM_OCMode_Toggle;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &oc);
	TIM_OC1Init(TIM3, &oc);
	TIM_OC2Init(TIM2, &oc);
	TIM_OC2Init(TIM3, &oc);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	
	TIM_ITConfig(TIM2, TIM_IT_CC1|TIM_IT_CC2, ENABLE );
	TIM_ITConfig(TIM3, TIM_IT_CC1|TIM_IT_CC2, ENABLE );

}




