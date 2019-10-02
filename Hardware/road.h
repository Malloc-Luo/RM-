#ifndef __ROAD_H
#define __ROAD_H
#include "sys.h"

/*       六路红外循迹          */
/*      由左到右依次为：       */
/*PA12 PA13 PA14 PB14 PB13 PB12*/

#define L1 PAin(12)
#define L2 PAin(13)
#define L3 PAin(14)
#define R1 PBin(12)
#define R2 PBin(13)
#define R3 PBin(14)

#define BLACK 0
#define WHITE 1

void Road_Init(void);


	
#endif

