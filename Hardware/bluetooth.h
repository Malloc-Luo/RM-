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
	���HC-05ģ��
	Bluetooth_Init() ��ʼ�������� 9600
	ģ������ yuqiBluetooth
*/

void Bluetooth_Init(u32 bound);

#endif


