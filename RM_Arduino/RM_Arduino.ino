/*超声波测距放在 timer2 定时器中断中，将接收到的数据进行PID处理，之后通过串口发送给stm32*/
/*超声波模块PID处理后的数据通过Data()函数转化为int 型返回给stm32*/

#include<Servo.h>
#include<NewPing.h>
#include<MsTimer2.h>

#define ENABLE 1
#define DISABLE !ENABLE

Servo servo1;
Servo servo2;

#define SIGNAL1 (unsigned char)0x01   
#define SIGNAL2 (unsigned char)0x02
#define SIGNAL3 (unsigned char)0x03
#define SIGNAL4 (unsigned char)0x04
#define SIGNAL5 (unsigned char)0x05
#define SIGNAL6 (unsigned char)0x06
#define SIGNAL7 (unsigned char)0x07
#define SIGNAL8 (unsigned char)0x08
#define SIGNAL9 (unsigned char)0x09
#define SIGNAL10 (unsigned char)0x0A
#define WRONG   (unsigned char)0xfa            
#define DONE    (unsigned char)0xff 
#define BEGINING (unsigned char)0x06   

#define SERVOUP (unsigned char)0x0B
#define SERVODOWN (unsigned char)0x0C


#define Pin_servo1 9
#define Pin_servo2 10

/*初始化超声波模块  distance 距离测量值*/
#define Trig 12
#define Echo 11

NewPing sonar(Trig, Echo, 50);
float distance;

/*PID 距离设定值 cm*/
#define SET_DISTANCE 6

/*周期*/
#define Tp 0.001

/*舵机旋转角度设定*/
int SET_POS_1=120;
int SET_POS_2=0;

/*------------*/
/*PID 参数结构体*/
/*PID 初始化函数*/
/*PID 处理函数  */
typedef float PID_Ki;
typedef float PID_Kp;
typedef float PID_Kd;
typedef unsigned char u8;
typedef struct
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
} PID ;

float LIMIT(float Limited, float umin, float umax)
{
  return (Limited <= umax ? Limited : umax) >= umin ? (Limited <= umax ? Limited : umax): umin ;
}

void PID_Init(PID_Kp p, PID_Ki i, PID_Kd d, PID * P)
{
  P->Actualvalue = 0;
  P->err = 0;
  P->err_last = 0;
  P->inite =0;
  P->Kd = d;
  P->Ki = i;
  P->Kp = p;
  P->Setvalue = 0;
  P->umax = P->Setvalue + 15;
  P->umin = P->Setvalue - 15;
}

float PID_Control(float setvalue, float actualvalue, PID * pid)
{
  int incrementvalue;
  pid->Setvalue = setvalue;
  pid->Actualvalue = actualvalue;
  pid->err = pid->Setvalue - pid->Actualvalue;
  pid->inite += pid->err;
  pid->inite = LIMIT(pid->inite, -100, 100);
  incrementvalue = pid->Kp * pid->err * Tp + pid->Ki * pid->inite * Tp + pid->Kd * (pid->err - pid->err_last);
  pid->err_last = pid->err;
  pid->Actualvalue = incrementvalue;
  pid->Actualvalue = LIMIT(pid->Actualvalue, pid->umin, pid->umax);
  return -(pid->Actualvalue)*6.0;
}

PID STM32Control;
u8 RX_Data ;
u8 TX_Data ;
int Data;
int Begin;
int End;

/*使能串口发送  ENABLE 开启串口发送  DISABLE 关闭*/
int USE = DISABLE; 

/*通过串口发送数据*/
void Send_to_STM(int8_t data)
{
  Serial.write(data);
}

/*SIGNAL_work*/
void SIGNAL1_Work(void)
{
  Send_to_STM(BEGINING);
  USE = ENABLE;
  distance = sonar.ping_cm();
  while(1)
  {
     distance = sonar.ping_cm();
     delay(10);
     TX_Data = (int8_t)(PID_Control(SET_DISTANCE, distance, &STM32Control)+0.5);
     if(USE)
        Send_to_STM(TX_Data);
     if(abs(STM32Control.Setvalue - STM32Control.Actualvalue) <= 1.5)
     {
        USE = DISABLE;
        break;
     }
  }
  Send_to_STM(SIGNAL3);
}

/*调整舵机*/
void SIGNAL2_Work(void)
{
  servo1.write(SET_POS_1);
  servo2.write(SET_POS_1);
  delay(100);
  Send_to_STM(SIGNAL4);
}

void SIGNAL5_Work(void)
{
  servo1.write(SET_POS_2);
  servo2.write(SET_POS_2);
  delay(100);
  Send_to_STM(DONE);
}

void SERVO_Up(void)
{
  servo1.write(90);
  servo2.write(90);
}

void SERVO_Down(void)
{
  servo1.write(0);
  servo2.write(0);
}
void setup() 
{
  Serial.begin(9600);
  servo1.attach(Pin_servo1);
  servo2.attach(Pin_servo2);
  PID_Init(700, 0, 1, &STM32Control);
}

void loop() 
{
  if(Serial.available())
  {
    RX_Data = Serial.read();
    Serial.flush();
    switch(RX_Data)
    {
      case SIGNAL1:
        SIGNAL1_Work();
        break;
      case SIGNAL2:
        delay(500);
        SIGNAL2_Work();
        break;
      case SIGNAL5:
        SIGNAL5_Work();
        delay(100);
        break;
      case SERVOUP:
        SERVO_Up();
        break;
      case SERVODOWN:
        SERVO_Down();
        break;
      default :
        break;
    }
  }
}
