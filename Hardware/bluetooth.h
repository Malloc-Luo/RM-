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
	���HC-05ģ��
	Bluetooth_Init() ��ʼ�������� 9600
	ģ������ yuqiBluetooth
*/

void Bluetooth_Init(u32 bound);

#endif


