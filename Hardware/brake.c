#include "brake.h"

void Brake_Init(void)
{
	EXTI_InitTypeDef exti;
	NVIC_InitTypeDef nvic;
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB , GPIO_PinSource9);
	
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	
	exti.EXTI_Line = EXTI_Line9 ;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
	
	nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&nvic);
}

void EXTI9_5_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line9);
	Motor_Pause();
	NVIC_DisableIRQ(EXTI9_5_IRQn);
	Motor_Start = DISABLE;
	Valve.Valve_EN = ENABLE;
	Valve.Valve_Status = CLOSE;
}
