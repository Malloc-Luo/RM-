/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
 
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
 
void SysTick_Handler(void)
{
	static u8 n = 0;
	static u8 EN ;
	
	if(L1==WHITE && L2==WHITE && M0==BLACK && R2==WHITE && R1==WHITE)
		Road.Action_Mode = Action_Mode_Straight;
	else if(L1==WHITE && L2==WHITE && M0==BLACK && R2==BLACK && R1==WHITE)
		Road.Action_Mode = Action_Mode_Left;
	else if(L1==WHITE && L2==WHITE && R2==BLACK && R1==BLACK)
		Road.Action_Mode = Action_Mode_Left_Badly;
	else if(L1==WHITE && L2==BLACK && M0==BLACK && R2==WHITE && R1==WHITE)
		Road.Action_Mode = Action_Mode_Right;
	else if(L1==BLACK && L2==BLACK && R2==WHITE && R1==WHITE)
		Road.Action_Mode = Action_Mode_Right_Badly;
	else if(L1==BLACK && L2==BLACK && M0==BLACK && R2==BLACK && R1==BLACK)
		EN = ENABLE;
	else if(L1==WHITE && L2==WHITE && M0==WHITE && R2==WHITE && R1==WHITE)
		Road.Action_Mode = Action_Mode_End;
	if(EN && Road.Road_Status == Road_Status_ENABLE)
	{
		if(n++ >=5)
			if((L1==WHITE || L2==WHITE) && (R2==WHITE || R1==WHITE))
			{
				Road.times++;
				EN = DISABLE;
				n = 0;
				if(Road.times == 3)
					Road.Action_Mode = Action_Mode_End;
			}
	}
	if(Road.Road_Status==Road_Status_ENABLE && Road.times<3)
	{
		Road_Mode();
	}
	if(Road.times >=3 )
		Motor_Pause();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
