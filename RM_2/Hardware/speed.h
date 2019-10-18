#ifndef __SPEED_H__
#define __SPEED_H__
#include "init.h"

extern u8 TIM3CH1_CAPTURE_STA ;
extern u16 TIM3CH1_CAPTURE_VAL ;

extern u8 TIM3CH2_CAPTURE_STA ;
extern u16 TIM3CH2_CAPTURE_VAL ;

extern u8 TIM3CH3_CAPTURE_STA ;
extern u16 TIM3CH3_CAPTURE_VAL ;

extern u8 TIM3CH4_CAPTURE_STA ;
extern u16 TIM3CH4_CAPTURE_VAL ;

typedef struct
{
	u8 Time1;
	u8 Time2;
	u8 Time3;
	u8 Time4;
}
GET_TIME;

extern GET_TIME Speed_Time;

void Speed_Init(void);

#endif
