#include "servo.h"

/*TIM2_CH2  TIM2_CH1*/
/*  PA.1      PA.0  */

void Servo_Init(void)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef time;
	TIM_OCInitTypeDef oc;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	                    
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE); 
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
                               
	time.TIM_Period=9999;                         
	time.TIM_Prescaler=143;                      
	time.TIM_ClockDivision=0x00;                    
	time.TIM_CounterMode=TIM_CounterMode_Up;     
	TIM_TimeBaseInit(TIM2,&time); 
	
	oc.TIM_OCMode = TIM_OCMode_PWM1;             
 	oc.TIM_OutputState = TIM_OutputState_Enable; 
	oc.TIM_OCPolarity = TIM_OCPolarity_High;  
	
  TIM_OC2Init(TIM2, &oc);
	TIM_OC1Init(TIM2, &oc);
	
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
  
	TIM_Cmd(TIM2,ENABLE); 
}

void Servo_Span_Degree(DEGREE degree)
{
	degree = (degree+45)*500/90;
	
	TIM_SetCompare1(TIM2, degree);
	TIM_SetCompare2(TIM2, degree);
}
