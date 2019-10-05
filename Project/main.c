#include "init.h"

int main(void)
{
	Init_All();
	while(1)
	{
			if(GAME_STATUS == 0x0C)
			{
				Road_Mode();
			}
	}
} 

