#ifndef __ROAD_H
#define __ROAD_H
#include "init.h"

/*    ��·����ѭ��        */
/*   ����������Ϊ��     */
/*PA12 PA11 PB11 PB13 PB12*/
/* L1   L2   M0   R2   R1 */
/* ��֤L2, M0, R2��ֵΪ BLACK ��С����ֱ�������� */

#define L1 PAin(12)
#define L2 PAin(11)
#define M0 PBin(11)
#define R1 PBin(12)
#define R2 PBin(13)

#define BLACK 0
#define WHITE 1

void Road_Init(void);

void Road_Mode(void);

#endif

