#include "brake.h"

void Brake_Init(void)
{
	EXTI_InitTypeDef exti;
	NVIC_InitTypeDef nvic;
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA , GPIO_PinSource4);
	
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Pin = GPIO_Pin_4;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	
	exti.EXTI_Line = EXTI_Line4 ;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&exti);
	
	nvic.NVIC_IRQChannel = EXTI4_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&nvic);
}

void EXTI4_IRQHandler(void)
{
	Motor_Pause();
	
	Motor_Start = DISABLE;
	
	Valve.Valve_EN = ENABLE;
	Valve.Valve_Status = CLOSE;
	
	NVIC_DisableIRQ(EXTI4_IRQn);
	EXTI_ClearITPendingBit(EXTI_Line4);
}
