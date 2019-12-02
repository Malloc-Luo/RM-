#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#include "init.h"

/*                   Command                           */

#define BEGIN     '1'   /* begin with automatic        */
#define ROAD_MODE '2'   /* road mode                   */
#define SERVO     '3'   /* control the servo upward    */
#define SPAN_CLK  '4'   /* control the span freequently*/
#define BACK      '5'   /* backward                    */
#define FORWARD   '6'   /* forward                     */
#define SPAN_ANTI '7'
#define TRAN_R    '8'   /* to the right translation    */
#define PAUSE     '9'   /* pause all                   */
#define TRAN_L    '0'   /* to the left translation     */
#define HIT 'b'
#define VALVE_OPEN 'a'
#define VALVE_CLOSE 'e'
#define STATUS1 'f'
#define STATUS2 'g'
#define STATUS3 'h'

#define ServoMode(n) ((n%2 == 0) ? SERVOUP : SERVODOWN)

/*usart2 TX PA.2
				 RX PA.3
	外接HC-05模块
	Bluetooth_Init() 初始化波特率 9600
	模块命名 yuqiBluetooth
*/

void Bluetooth_Init(u32 bound);

#endif


