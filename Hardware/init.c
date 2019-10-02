#include "init.h"

u8 GAME_STATUS = 0x03;

int16_t Set_Speed;

void Init_All(void)
{
	GAME_STATUS = 0x03;
	Motor_Init();
	uart_init(9600);
	Bluetooth_Init(9600);
	Road_Init();
	Valve_Init();
	LED_Init();
}
