#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define Forward_Left_Speed0 TIM_SetCompare1(TIM2, 0)


void Motor_Init(void);



#endif

//==================EXPLAIN=====================
/*stm32f103�����������·PWM�������Ƶ������ת
  �������·PWM������תͨ�����ߵ�ƽ
	
*/

