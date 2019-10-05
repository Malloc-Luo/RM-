#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#include "init.h"

/*Command*/
#define BEGIN '1'
#define PAUSE '9'
#define ROAD_MODE '2'
#define CONTROL_MODE '3'
#define SPAN '4'
#define BACK '5'
#define FORWARD '6'
#define TRAN_L '0'
#define TRAN_R '8'

/*usart2 TX PA.2
				 RX PA.3
	外接HC-05模块
	Bluetooth_Init() 初始化波特率 9600
	模块命名 yuqiBluetooth
*/

void Bluetooth_Init(u32 bound);

#endif


