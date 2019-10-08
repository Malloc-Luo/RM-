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
#define SIGNAL3 (unsigned char)0xfe
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

void SIGNAL1_Work(void)
{
  servo1.write(SET_POS_1);
  servo2.write(SET_POS_1);
  delay(500);
  Send_to_STM(DONE);
}

/*调整舵机*/
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
