#include "bluetooth.h"

u8 Bluetooth_RX_Data;

void Bluetooth_Init(u32 bound)
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart;
	NVIC_InitTypeDef nvic;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&gpio);
	
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &gpio);
	
	nvic.NVIC_IRQChannel = USART2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	usart.USART_BaudRate = bound;                                    
	usart.USART_WordLength = USART_WordLength_8b;                    
	usart.USART_StopBits = USART_StopBits_1;                        
	usart.USART_Parity = USART_Parity_No;                            
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART2, &usart);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void)
{
	static u8 times = 0;
	static u8 hittimes = 0;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Bluetooth_RX_Data = USART_ReceiveData(USART2);
		
		switch(Bluetooth_RX_Data)
		{
			case BEGIN:
				Send_to_Arduino(SIGNAL3);
				GAME_STATUS = 0x03;
				break;
			case VALVE_CLOSE:
				Valve.Valve_EN = ENABLE;
				Valve.Valve_Status = CLOSE;
				Valve_Control();
				Valve.Valve_EN = DISABLE;
				break;
			case VALVE_OPEN:
				Valve.Valve_EN = ENABLE;
				Valve.Valve_Status = OPEN;
				Valve_Control();
				Valve.Valve_EN = DISABLE;
				break;
			case HIT:
				Hit(HitSpeed(hittimes));
				hittimes ++;
				break;
			case FORWARD:
				Motor_PID_Speed(600, Delta);
				break;
			case BACK:
				Motor_PID_Speed(-600, Delta);
				break;
			case TRAN_R:
				Motor_TRAN_Move(650, RIGHT, Delta);
				break;
			case TRAN_L:
				Motor_TRAN_Move(650, LEFT, Delta);
				break;
			case SPAN_CLK:
				Motor_SPAN(650, CLOCKWISE, Delta);	
				break;
			case PAUSE:
				Road.Road_Status = Road_Status_DISABLE;
				Motor_Start = DISABLE;
				Motor_Pause();
				break;
			case SPAN_ANTI:
				Motor_SPAN(650, ANTICLOCKWISE, Delta);
				break;
			case SERVO:
				Send_to_Arduino(ServoMode(times));
				times ++ ;
				break;
			case ROAD_MODE:
				Road.Road_Status = Road_Status_ENABLE;
				Road.times = 0 ;
				break;
			case STATUS1:
				Delta = 300;
				break;
			case STATUS2:
				Delta = 150;
				break;
			case STATUS3:
				Delta = 0;
				break;
			default :
				Motor_Pause();
				break;
		}
	}
}

