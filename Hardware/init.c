#include "init.h"

void Init_All(void)
{
	Motor_Init();
	uart_init(9600);
	
	
	
}
