#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define Forward_Left_Speed0 TIM_SetCompare1(TIM2, 0)


void Motor_Init(void);



#endif

//==================EXPLAIN=====================
/*stm32f103开发板输出八路PWM波，控制电机正反转
  或输出四路PWM波，反转通过拉高电平
	
*/

