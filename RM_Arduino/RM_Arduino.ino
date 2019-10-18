#include<Servo.h>
#include<MsTimer2.h>

#define ENABLE 1
#define DISABLE !ENABLE

Servo servo1;
Servo servo2;

#define SIGNAL0 (unsigned char)0x00
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

/*舵机旋转角度设定*/
int SET_POS_1=120;
int SET_POS_2=0;

u8 RX_Data ;
u8 TX_Data ;

/*通过串口发送数据*/
void Send_to_STM(int8_t data)
{
  Serial.write(data);
}

void SIGNAL3_Work(void)
{
  servo1.write(160);
  servo2.write(0);

  Send_to_STM(SIGNAL2);
}

void SIGNAL1_Work(void)
{
  servo1.write(0);
  servo2.write(160);
  delay(500);
  Send_to_STM(DONE);
}

/*调整舵机*/
void SERVO_Up(void)
{
  servo1.write(0);
  servo2.write(160);
}

void SERVO_Down(void)
{
  servo1.write(160);
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
      case SIGNAL3:
        SIGNAL3_Work();
        break;
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
