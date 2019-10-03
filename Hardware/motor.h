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

/*PID控制阶段调速*/
void Motor_PID_Speed(SPEED ); 

/*巡线阶段调速*/
void Motor_ROAD_Speed(SPEED , DIRECTION , DELTA );

/*原地旋转90° 顺时针 or 逆时针*/
void Motor_SPAN_90Degree(SPEED, DIRECTION );

/*侧向移动，ACTION4阶段*/
void Motor_TRAN_Move(SPEED , DIRECTION );

/*电机停止转动*/
void Motor_Pause(void);

/*测试程序*/
void TEST_P(void);

#endif

//==================EXPLAIN=====================
/*stm32f103开发板输出八路PWM波，控制电机正反转
	定义 TIM2_CH1 TIM2_CH2 控制左前轮
			 TIM3_CH1 TIM3_CH2 控制右前轮
			 TIM4_CH1 TIM4_CH2 控制左后轮
			 TIM3_CH3 TIM3_CH4 控制右后轮
	且 当TIM2_CH1 TIM3_CH1 TIM4_CH1 TIM3_CH3 同时拉高时，小车沿规定正方向运动
*/

