#ifndef __VALVE_H__
#define __VALVE_H__
#include "init.h"

#define CLOSE 0
#define OPEN 1

/*¿ØÖÆÆø¸×µç´Å·§*/
/*PB.4*/

typedef struct
{
	u8 Valve_Status;
	u8 Valve_EN;
	
}VALVE_SetTypeDef;

extern VALVE_SetTypeDef Valve;

#define Valve_VALVE1 PBout(4)

void Valve_Init(void);

void Valve_Control(void);

#endif


