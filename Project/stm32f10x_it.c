#include "stm32f10x_it.h" 

/* 50ms执行一次 */
void Timer_50ms(void)
{
	if(Valve.Valve_EN == ENABLE)
	{
		Valve_Control();
		Valve.Valve_EN = DISABLE;
		Send_to_Arduino(SIGNAL1);
	}
}

/* 100ms执行一次 */
void Timer_100ms(void)
{
	LED_Mode(GAME_STATUS);
	if(Motor_Start)
	{
		Motor_PID_Speed(-280);
	}
}

/* 200ms执行一次 */
void Timer_200ms(void)
{
	
}

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}

/* 5ms执行一次 */
void SysTick_Handler(void)
{
	static u8 n = 0;
	static u8 EN ;
	static uint16_t timer = 0;
	
	timer ++;
	
	if(timer%10 == 0)
		Timer_50ms();
	if(timer%20 == 0)
		Timer_100ms();
	if(timer%40 == 0)
		Timer_200ms();
	if(timer >= 65530)
		timer = 0;
	
	if(Road.Road_Status)
	{
		if(L1==WHITE && L2==WHITE && M0==BLACK && R2==WHITE && R1==WHITE)
			Road.Action_Mode = Action_Mode_Straight;
		else if(L1==WHITE && L2==WHITE && R2==BLACK && R1==WHITE)
			Road.Action_Mode = Action_Mode_Left;
		else if(L1==WHITE && L2==WHITE && R2==BLACK && R1==BLACK)
			Road.Action_Mode = Action_Mode_Left_Badly;
		else if(L1==WHITE && L2==BLACK && R2==WHITE && R1==WHITE)
			Road.Action_Mode = Action_Mode_Right;
		else if(L1==BLACK && L2==BLACK && R2==WHITE && R1==WHITE)
			Road.Action_Mode = Action_Mode_Right_Badly;
		else if((L1==BLACK || L2==BLACK) && M0==BLACK && (R2==BLACK || R1==BLACK))
			EN = ENABLE;
		if(EN)
		{
			if(n++ >=5)
				if((L1==WHITE || L2==WHITE) && (R2==WHITE || R1==WHITE) && M0==BLACK)
				{
					Road.times++;
					EN = DISABLE;
					n = 0;
					if(Road.times == 3)
						Road.Action_Mode = Action_Mode_End;
				}
		}
		if(Road.times<3)
		{
			Road_Mode();
		}
		if(Road.times >=3 )
			Motor_Pause();
	}
}


