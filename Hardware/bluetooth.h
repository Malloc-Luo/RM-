#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#include "init.h"

/*Command*/
#define BEGIN 0x01
#define PAUSE 0x00
#define ROAD_MODE 0x03
#define CONTROL_MODE 0x05

/*usart2 TX PA.2
				 RX PA.3
	外接HC-05模块
	Bluetooth_Init() 初始化波特率 9600
	模块命名 yuqiBluetooth
*/

void Bluetooth_Init(u32 bound);

#endif


