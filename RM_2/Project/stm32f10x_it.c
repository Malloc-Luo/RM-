#include "stm32f10x_it.h" 

/* 50ms执行一次 */
void Timer_50ms(void)
{
}

/* 100ms执行一次 */
void Timer_100ms(void)
{
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
	
}


