#ifndef __INIT_H
#define __INIT_H
#include "sys.h"
#include "stdio.h"
#include "motor.h"
#include "road.h"
#include "usart.h"
#include "delay.h"
#include "bluetooth.h"
#include "valve.h"
#include "led.h"
#include "stm32f10x_it.h"
//#include "timer.h"

#define ON 1
#define OFF 0

#define ROAD 0
#define AUTO 1

/* u8 Game_Staus 
 * 比赛进程标志
 * 00 00 00 11 ACTION1 0x03
 * 00 00 11 00 ACTION2 0x0c
 * 00 11 00 00 ACTION3 0x30
 * 11 00 00 00 ACTION4	0xc0 */
	
extern u8 GAME_STATUS;          /*进入下一阶段，GAME_STATUS 右移两位*/

extern int16_t Set_Speed;       /*ACTION1阶段PID调节速度值*/

extern u8 Bluetooth_RX_Data;		//bluetooth recived datas

void Init_All(void);

#endif


