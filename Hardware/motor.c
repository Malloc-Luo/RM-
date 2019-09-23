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
	
	
	
	
	
	
	
	
	
}




