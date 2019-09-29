#ifndef __PID_H__
#define __PID_H__
#include "init.h"
#define Tp 0.001

struct Pid
{
  int16_t Ki;
	int16_t Kp;
	int16_t Kd;
	int16_t Actualvalue;
	int16_t Setvalue;
	int16_t err;
	int16_t err_last;
	int16_t inite;
	int16_t max;
	int16_t min;
};

typedef struct Pid PID;

typedef int16_t PID_Ki;
typedef int16_t PID_Kp;
typedef int16_t PID_Kd;

extern PID speed;
extern PID pos;

int16_t PID_Control(int16_t setvalue, int16_t actualvalue, PID * pid);

int16_t LIMIT(int16_t Limited, int16_t min, int16_t max);

void PID_Init(PID_Kp p, PID_Ki i, PID_Kd d, PID *);


#endif

