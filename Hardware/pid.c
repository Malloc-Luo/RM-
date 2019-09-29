#include "pid.h"

int16_t LIMIT(int16_t Limited, int16_t min, int16_t max)
{
	return (Limited <= max ? Limited : max) >= min ? (Limited <= max ? Limited : max): min ;
}

void PID_Init(PID_Kp p, PID_Ki i, PID_Kd d, PID *P)
{
	P->Actualvalue = 0;
	P->err = 0;
	P->err_last = 0;
	P->inite =0;
	P->Kd = d;
	P->Ki = i;
	P->Kp = p;
	P->Setvalue = 0;
	P->max = P->Setvalue + 10000;
	P->min = P->Setvalue - 10000;
}

int16_t PID_Control(int16_t setvalue, int16_t actualvalue, PID * pid)
{
	int16_t incrementvalue;
	
	pid->Setvalue = setvalue;
	
	pid->Actualvalue = actualvalue;
	
	pid->err = pid->Setvalue - pid->Actualvalue;
	
	if(pid->Actualvalue >pid->max)
	{
		if(pid->err <= 0)
			pid->inite +=pid->err;
	}

	else if(pid->Actualvalue < pid->min)
	{
		if(pid->err >= 0)
			pid->inite += pid->err;
	}
	
	else 
		pid->inite += pid->err;
	
	pid->inite = LIMIT(pid->inite, -10000, 10000);
		
	incrementvalue = pid->Kp * pid->err * Tp + pid->Ki * pid->inite * Tp + pid->Kd * (pid->err - pid->err_last);
	
	pid->err_last = pid->err;
	
	pid->Actualvalue = incrementvalue;
	
	pid->Actualvalue = LIMIT(pid->Actualvalue, pid->min, pid->max);
	
	return pid->Actualvalue;
	
}
