/*超声波测距放在 timer2 定时器中断中，将接收到的数据进行PID处理，之后通过串口发送给stm32*/
/*超声波模块PID处理后的数据通过Data()函数转化为int 型返回给stm32*/

#include<Servo.h>
#include<NewPing.h>

Servo servo1;
Servo servo2;

#define Pin_servo1 9
#define Pin_servo2 5

#define Trig 3
#define Echo 2

#define LED1 14
#define LED2 15
#define LED3 16
#define LED4 17

int pos;
float distance;

/*-------------------------------------------------------------------------------------*/
/**/
struct Pid
{
  float Ki;
  float Kp;
  float Kd;
  float Actualvalue;
  float Setvalue;
  float err;
  float err_last;
  float inite;
  float umax;
  float umin;
};
typedef struct Pid PID;
typedef float PID_Ki;
typedef float PID_Kp;
typedef float PID_Kd;

float LIMIT(float Limited, float umin, float umax)
{
  return (Limited <= umax ? Limited : umax) >= umin ? (Limited <= umax ? Limited : umax): umin ;
}

void PID_Init(PID_Kp p, PID_Ki i, PID_Kd d)
{
  P->Actualvalue = 0;
  P->err = 0;
  P->err_last = 0;
  P->inite =0;
  P->Kd = d;
  P->Ki = i;
  P->Kp = p;
  P->Setvalue = 0;
  P->umax = P->Setvalue + 100.0;
  P->umin = P->Setvalue - 100.0;
}

int PID_Control(float setvalue, float actualvalue, PID * pid)
{
  float incrementvalue;
  pid->Setvalue = setvalue;
  pid->Actualvalue = actualvalue;
  pid->err = pid->Setvalue - pid->Actualvalue;
  if(pid->Actualvalue >pid->umax)
  {
    if(pid->err <= 0)
      pid->inite +=pid->err;
  }
  else if(pid->Actualvalue < pid->umin)
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
  pid->Actualvalue = LIMIT(pid->Actualvalue, pid->umin, pid->umax);
  return (int)(pid->Actualvalue);
}

//--------------------------------------------------------------------------------------------------------

//distance=pulseIn(3,HIGH)/57.88;
//servo1.write(pos)

void setup() 
{
  pinMode(Trig , INPUT);
  pinMode(Echo , OUTPUT);
  Serial.begin(9600);
  servo1.attach(Pin_servo1);
  servo2.attach(Pin_servo2);
}

void loop() 
{
  servo1.write(pos);
  
}
