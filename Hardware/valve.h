#ifndef __VALVE_H__
#define __VALVE_H__
#include "init.h"

#define CLOSE 1
#define OPEN 0

/*¿ØÖÆÆø¸×µç´Å·§*/
/*PB.4*/

typedef struct
{
	u8 Valve_Status;
	u8 Valve_EN;
	
}VALVE_SetTypeDef;

extern VALVE_SetTypeDef Valve;

#define Valve_OPEN GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define Valve_CLOSE GPIO_SetBits(GPIOB, GPIO_Pin_9)

void Valve_Init(void);

void Valve_Control(void);

#endif


