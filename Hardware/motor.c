#include "motor.h"

//----------------------------------
/*TIM2_CH1  PA.0 TIM_SetCompare1(TIM2, value)
  TIM2_CH2  PA.1
	TIM3_CH1  PA.6
	TIM3_CH2  PA.7
	TIM3_CH3  PB.0
	TIM3_CH4  PB.1
	TIM4_CH1  PB.6
	TIM4_CH2  PB.7
*/

void Motor_Init(void)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef time;
	TIM_OCInitTypeDef oc;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_6 |GPIO_Pin_7 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA ,&gpio);
	GPIO_Init(GPIOB ,&gpio);
	
	time.TIM_ClockDivision = 0;
	time.TIM_Prescaler = 0;
	time.TIM_Period = 899;
	time.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM2, &time);
	TIM_TimeBaseInit(TIM3, &time);
	TIM_TimeBaseInit(TIM4, &time);
	
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &oc);
	TIM_OC1Init(TIM3, &oc);
	TIM_OC2Init(TIM2, &oc);
	TIM_OC2Init(TIM3, &oc);
	TIM_OC1Init(TIM4, &oc);
	TIM_OC2Init(TIM4, &oc);
	TIM_OC3Init(TIM3, &oc);
	TIM_OC4Init(TIM3, &oc);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}


/*单独控置每一个轮*/
/*direction  F 表示向前  B 表示向后*/

void ForLeft(SPEED speed, DIRECTION direction)
{
	if(direction)
	{
		For_Left_A(speed);
		For_Left_B(SPEED0);
	}
	else
	{
		For_Left_B(speed);
		For_Left_A(SPEED0);
	}
}
void ForRight(SPEED speed, DIRECTION direction)
{
	if(direction)
	{
		For_Right_A(speed);
		For_Right_B(SPEED0);
	}
	else
	{
		For_Right_B(speed);
		For_Right_A(SPEED0);
	}
}
void BackLeft(SPEED speed, DIRECTION direction)
{
	if(direction)
	{
		Back_Left_A(speed);
		Back_Left_B(SPEED0);
	}
	else
	{
		Back_Left_B(speed);
		Back_Left_A(SPEED0);
	}
}
void BackRight(SPEED speed, DIRECTION direction)
{
	if(direction)
	{
		Back_Right_A(speed);
		Back_Right_B(SPEED0);
	}
	else
	{
		Back_Right_B(speed);
		Back_Right_A(SPEED0);
	}
}



/*在PID调整距离阶段使用*/
/*这里面当speed > 0 小车反向运动
          否则，小车正向运动*/
void PID_Adjust_Speed(SPEED speed)
{
	if(speed > 0)
	{
		TIM_SetCompare1(TIM2, 0);
		TIM_SetCompare2(TIM2, speed);
		
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, speed);
		
		TIM_SetCompare1(TIM4, 0);
		TIM_SetCompare2(TIM4, speed);
		
		TIM_SetCompare3(TIM3, 0);
		TIM_SetCompare4(TIM3, speed);
	}
	else
	{
		TIM_SetCompare1(TIM2, -speed);
		TIM_SetCompare2(TIM2, 0);
		
		TIM_SetCompare1(TIM3, -speed);
		TIM_SetCompare2(TIM3, 0);
		
		TIM_SetCompare1(TIM4, -speed);
		TIM_SetCompare2(TIM4, 0);
		
		TIM_SetCompare3(TIM3, -speed);
		TIM_SetCompare4(TIM3, 0);
	}
}

void ROAD_Adjust_Speed(SPEED speed, DIRECTION direction)
{
	if(direction)
	{
		ForRight(speed, F);
		ForLeft(speed-100, F);
		BackRight(speed-50, F);
		BackLeft(speed-150, F);
	}
	else
	{
		ForRight(speed-100, F);
		ForLeft(speed, F);
		BackRight(speed-150, F);
		BackLeft(speed-50, F);
	}
}

void SPAN_90Degree(DIRECTION direction)
{
	
	
	
}









