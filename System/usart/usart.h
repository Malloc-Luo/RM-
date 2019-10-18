#ifndef __USART_H
#define __USART_H
#include "init.h"	 

/*usart1 command (auto)*/

#define SIGNAL0 0x00
#define SIGNAL1 0x01
#define SIGNAL2 0x02
#define SIGNAL3 0xfe
#define SIGNAL4 0x04
#define SIGNAL5 0x05
#define SIGNAL6 0x06
#define SIGNAL7 0x07
#define SIGNAL8 0x08
#define SIGNAL9 0x09
#define SIGNAL10 0x0A
#define WRONG   0xfa            //Send data error
#define DONE  0xff            //complete a action
#define BEGINING 0x06

/*usart1 command (manual)*/

#define SERVOUP 0x0B
#define SERVODOWN 0x0C

extern int16_t USART1_RX_Data;       //usart1 recived datas
extern u8 USART1_RX_LastData;
extern u8 TX_Status;            //success 1
extern u8 RX_Status;            //fail    0
extern u8 PID_CTRL;

void uart_init(u32 bound);

void Send_to_Arduino(u8 );

#endif


