#ifndef __LED_H__
#define __LED_H__
#include "init.h"

/*四个LED指示灯，在四个动作中依次亮起*/

#define LED1 PAout(4)		//white
#define LED2 PAout(5)		//yellow
#define LED3 PBout(8)		//blue
#define LED4 PBout(9)		//green

void LED_Init(void);

void LED_Mode(u8 status);

#endif


