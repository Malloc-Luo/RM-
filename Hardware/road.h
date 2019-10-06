#ifndef __ROAD_H
#define __ROAD_H
#include "init.h"

/*    五路红外循迹        */
/*   由左到右依次为：     */
/*PA12 PA11 PB11 PB13 PB12*/
/* L1   L2   M0   R2   R1 */
/* 保证 M0 的值为 BLACK   L1 L2 R1 R2 值位 WHITE 则小车在直线上行走 */

#define L1 PAin(12)
#define L2 PAin(11)
#define M0 PBin(11)
#define R1 PBin(12)
#define R2 PBin(13)

#define BLACK 0
#define WHITE 1

typedef struct 
{
	u8 Road_Status;
	u8 times;
	u8 Action_Mode;
}RoadMode;

/* RoadMode.Action_Mode */

#define Action_Mode_Straight    0x00
#define Action_Mode_Right       0x01
#define Action_Mode_Left        0x02
#define Action_Mode_Right_Badly 0x03
#define Action_Mode_Left_Badly  0x04
#define Action_Mode_End         0x05

#define Road_Status_ENABLE  0x01
#define Road_Status_DISABLE 0x02

extern RoadMode Road;

void Road_Init(void);

void Road_Mode(void);

#endif

