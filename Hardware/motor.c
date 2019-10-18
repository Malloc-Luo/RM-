#include "motor.h"

/*TIM2_CH1  PA.0
  TIM2_CH2  PA.1
	TIM3_CH1  PA.6
	TIM3_CH2  PA.7
	TIM3_CH3  PB.0
	TIM3_CH4  PB.1
	TIM4_CH1  PB.6
	TIM4_CH2  PB.7
	
	TIM4_CH3  PB.8
*/

u8 Motor_Start;

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
	
	gpio.GPIO_Pin = GPIO_Pin_8;
	
	GPIO_Init(GPIOB, &gpio);
	
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
	TIM_OC3Init(TIM4, &oc);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

/*停止运动*/

void Motor_Pause(void)
{
	For_Left_A(0);
	For_Left_B(0);
	
	For_Right_A(0);
	For_Right_B(0);
	
	Back_Left_A(0);
	Back_Left_B(0);
	
	Back_Right_A(0);
	Back_Right_B(0);
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
void Motor_PID_Speed(SPEED speed)
{
	if(speed > 0)
	{
		ForLeft(speed, F);
		ForRight(speed, F);
		BackLeft(speed, F);
		BackRight(speed, F);
	}
	else
	{
		ForLeft(-speed, B);
		ForRight(-speed, B);
		BackRight(-speed, B);
		BackLeft(-speed, B);
	}
}

/*  巡线过程中速度调整函数  */
/*有所需速度大小和方向两个参数*/
/*DIRECTION 参见宏定义 - RIGHT - - LEFT-*/

void Motor_ROAD_Speed(SPEED speed, DIRECTION direction, DELTA delta)
{
	if(direction == LEFT)
	{
		ForRight(speed, F);
		ForLeft(speed-delta, F);
		BackRight(speed-delta/5, F);
		BackLeft(speed-delta-50, F);
	}
	else if(direction == RIGHT)
	{
		ForRight(speed-delta, F);
		ForLeft(speed, F);
		BackRight(speed-delta-50, F);
		BackLeft(speed-delta/5, F);
	}
	else if(direction == CLOCKWISE || direction == ANTICLOCKWISE)
		Motor_SPAN(speed - delta, direction);
	else
	{
		ForRight(speed-delta, F);
		ForLeft(speed-delta, F);
		BackLeft(speed-delta, F);
		BackRight(speed-delta, F);
	}
}

/*原地旋转90度*/
/*DIRECTION 参见宏定义 - CLOCKWISE - - ANTICLOCKWISE - */

void Motor_SPAN(SPEED speed, DIRECTION direction)
{
	if(direction == CLOCKWISE)
	{
		ForLeft(speed, F);
		BackLeft(speed, F);
		
		ForRight(speed, B);
		BackRight(speed, B);
	}
	else
	{
		ForLeft(speed, B);
		BackLeft(speed, B);
		
		ForRight(speed, F);
		BackRight(speed, F);
	}
}

/*侧移*/
/*SPEED  - SPEED0 - -->  - SPEED8 -*/
/*DIRECTION  - F - - B -*/

void Motor_TRAN_Move(SPEED speed, DIRECTION direction)
{
	if(direction == LEFT)
	{
		ForLeft(speed, B);
		BackLeft(speed, F);
		
		ForRight(speed, F);
		BackRight(speed, B);
	}
	else
	{
		ForLeft(speed, F);
		BackLeft(speed, B);
		
		ForRight(speed, B);
		BackRight(speed, F);
	}
}


