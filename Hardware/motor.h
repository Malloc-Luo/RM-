#ifndef __MOTOR_H
#define __MOTOR_H
#include "init.h"

#define RIGHT 0
#define LEFT  1
#define STRAIGHT 2

#define F 1
#define B 0

#define CLOCKWISE 1
#define ANTICLOCKWISE 0

#define For_Left_A(speed) TIM_SetCompare1(TIM2, speed)
#define For_Left_B(speed) TIM_SetCompare2(TIM2, speed)
#define For_Right_A(speed) TIM_SetCompare1(TIM3, speed)
#define For_Right_B(speed) TIM_SetCompare2(TIM3, speed)
#define Back_Left_A(speed) TIM_SetCompare1(TIM4, speed)
#define Back_Left_B(speed) TIM_SetCompare2(TIM4, speed)
#define Back_Right_A(speed) TIM_SetCompare3(TIM3, speed)
#define Back_Right_B(speed) TIM_SetCompare4(TIM3, speed)

#define SPEED0 0
#define SPEED1 150
#define SPEED2 200
#define SPEED3 250
#define SPEED4 300
#define SPEED5 350
#define SPEED6 400
#define SPEED7 450
#define SPEED8 500

typedef int16_t SPEED;
typedef int16_t DIRECTION;
typedef int16_t DELTA;

void Motor_Init(void);

void ForLeft(SPEED , DIRECTION);
void ForRight(SPEED , DIRECTION);
void BackRight(SPEED , DIRECTION);
void BackLeft(SPEED , DIRECTION);

/*PID���ƽ׶ε���*/
void Motor_PID_Speed(SPEED ); 

/*Ѳ�߽׶ε���*/
void Motor_ROAD_Speed(SPEED , DIRECTION , DELTA );

/*ԭ����ת90�� ˳ʱ�� or ��ʱ��*/
void Motor_SPAN_90Degree(SPEED, DIRECTION );

/*�����ƶ���ACTION4�׶�*/
void Motor_TRAN_Move(SPEED , DIRECTION );

/*���ֹͣת��*/
void Motor_Pause(void);

/*���Գ���*/
void TEST_P(void);

#endif

//==================EXPLAIN=====================
/*stm32f103�����������·PWM�������Ƶ������ת
	���� TIM2_CH1 TIM2_CH2 ������ǰ��
			 TIM3_CH1 TIM3_CH2 ������ǰ��
			 TIM4_CH1 TIM4_CH2 ���������
			 TIM3_CH3 TIM3_CH4 �����Һ���
	�� ��TIM2_CH1 TIM3_CH1 TIM4_CH1 TIM3_CH3 ͬʱ����ʱ��С���ع涨�������˶�
*/

