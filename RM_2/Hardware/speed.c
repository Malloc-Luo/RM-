#include "speed.h"

//	TIM3_CH1  PA.6
//	TIM3_CH2  PA.7
//	TIM3_CH3  PB.0
//	TIM3_CH4  PB.1

TIM_ICInitTypeDef tim3 ;
GET_TIME Speed_Time;

u8 TIM3CH1_CAPTURE_STA = 0x00;
u16 TIM3CH1_CAPTURE_VAL ;

u8 TIM3CH2_CAPTURE_STA = 0x00;
u16 TIM3CH2_CAPTURE_VAL ;

u8 TIM3CH3_CAPTURE_STA = 0x00;
u16 TIM3CH3_CAPTURE_VAL ;

u8 TIM3CH4_CAPTURE_STA = 0x00;
u16 TIM3CH4_CAPTURE_VAL ;

void Speed_Init(void)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef time;
	NVIC_InitTypeDef nvic;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
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
	
	TIM_TimeBaseInit(TIM3, &time);
	
	tim3.TIM_Channel = TIM_Channel_1;
	tim3.TIM_ICFilter = 0;
	tim3.TIM_ICPolarity = TIM_ICPolarity_Rising;
	tim3.TIM_ICPrescaler = TIM_ICPSC_DIV1 ;
	tim3.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3, &tim3);
	
	tim3.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM3, &tim3);
	
	tim3.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM3, &tim3);
	
	tim3.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM3, &tim3);
	
	nvic.NVIC_IRQChannel = TIM3_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	
	NVIC_Init(&nvic);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);
	
}

void TIM3_IRQHandler(void)
{
	/*------------------TIM3_CH1-----------------------*/
	if(!(TIM3CH1_CAPTURE_STA&0x80))
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(TIM3CH1_CAPTURE_STA&0x40)
			{
				if((TIM3CH1_CAPTURE_STA&0x3f) == 0x3f)
				{
					TIM3CH1_CAPTURE_STA |= 0x80;
					TIM3CH1_CAPTURE_VAL = 0xffff;
				}
				else
					TIM3CH1_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC1)!= RESET)
		{
			if(TIM3CH1_CAPTURE_STA&0x40)
			{
				TIM3CH1_CAPTURE_STA |=0x80;
				TIM3CH1_CAPTURE_VAL = TIM_GetCapture1(TIM3);
				TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			}
			
			else
			{
				TIM3CH1_CAPTURE_STA = 0x00;
				TIM3CH1_CAPTURE_VAL = 0x00;
				TIM_SetCounter(TIM3, 0);
				TIM3CH1_CAPTURE_STA |= 0x40;
				TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			}
		}
	}
	
	/*------------------TIM3_CH2-----------------------*/
	if(!(TIM3CH2_CAPTURE_STA&0x80))
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(TIM3CH2_CAPTURE_STA&0x40)
			{
				if((TIM3CH2_CAPTURE_STA&0x3f) == 0x3f)
				{
					TIM3CH2_CAPTURE_STA |= 0x80;
					TIM3CH2_CAPTURE_VAL = 0xffff;
				}
				else
					TIM3CH2_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC2)!= RESET)
		{
			if(TIM3CH2_CAPTURE_STA&0x40)
			{
				TIM3CH2_CAPTURE_STA |=0x80;
				TIM3CH2_CAPTURE_VAL = TIM_GetCapture2(TIM3);
				TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			}
			
			else
			{
				TIM3CH2_CAPTURE_STA = 0x00;
				TIM3CH2_CAPTURE_VAL = 0x00;
				TIM_SetCounter(TIM3, 0);
				TIM3CH2_CAPTURE_STA |= 0x40;
				TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			}
		}
	}
	/*------------------TIM3_CH1-----------------------*/
	if(!(TIM3CH3_CAPTURE_STA&0x80))
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(TIM3CH3_CAPTURE_STA&0x40)
			{
				if((TIM3CH3_CAPTURE_STA&0x3f) == 0x3f)
				{
					TIM3CH3_CAPTURE_STA |= 0x80;
					TIM3CH3_CAPTURE_VAL = 0xffff;
				}
				else
					TIM3CH3_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC3)!= RESET)
		{
			if(TIM3CH3_CAPTURE_STA&0x40)
			{
				TIM3CH3_CAPTURE_STA |=0x80;
				TIM3CH3_CAPTURE_VAL = TIM_GetCapture3(TIM3);
				TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			}
			
			else
			{
				TIM3CH3_CAPTURE_STA = 0x00;
				TIM3CH3_CAPTURE_VAL = 0x00;
				TIM_SetCounter(TIM3, 0);
				TIM3CH3_CAPTURE_STA |= 0x40;
				TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			}
		}
	}
	/*------------------TIM3_CH1-----------------------*/
	if(!(TIM3CH4_CAPTURE_STA&0x80))
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			if(TIM3CH4_CAPTURE_STA&0x40)
			{
				if((TIM3CH4_CAPTURE_STA&0x3f) == 0x3f)
				{
					TIM3CH4_CAPTURE_STA |= 0x80;
					TIM3CH4_CAPTURE_VAL = 0xffff;
				}
				else
					TIM3CH4_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC4)!= RESET)
		{
			if(TIM3CH4_CAPTURE_STA&0x40)
			{
				TIM3CH4_CAPTURE_STA |=0x80;
				TIM3CH4_CAPTURE_VAL = TIM_GetCapture4(TIM3);
				TIM_OC4PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			}
			
			else
			{
				TIM3CH4_CAPTURE_STA = 0x00;
				TIM3CH4_CAPTURE_VAL = 0x00;
				TIM_SetCounter(TIM3, 0);
				TIM3CH4_CAPTURE_STA |= 0x40;
				TIM_OC4PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			}
		}
	}
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}


