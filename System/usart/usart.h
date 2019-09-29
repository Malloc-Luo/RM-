#ifndef __USART_H
#define __USART_H
#include "init.h"	 

/*usart1 command*/

#define SIGNAL1 0x01   //arduino开始对数据PID，并将数据发回stm32
#define SIGNAL2 0x02
#define SIGNAL3 0x03
#define SIGNAL4 0x04
#define SIGNAL5 0x05
#define WRONG   0xfa            //Send data error
#define DONE  0xff            //complete a action

extern u8 USART1_RX_Data;       //usart1 recived datas
extern u8 USART1_RX_LastData;
extern u8 TX_Status;            //success 1
extern u8 RX_Status;            //fail    0

void uart_init(u32 bound);

void Send_to_Arduino(u8 );

#endif


