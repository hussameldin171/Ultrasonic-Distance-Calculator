/* ============================================================================
 Name        : main.c
 Author      : Hussam Eldin Wael
 Description : Mini Project 4
 Date        : 16/10/2021
 ===============================================================================
 */

#include "LCD.h"
#include "ultrasonic.h"



int main(void) {

	LCD_init();
	uint16 sensor_reading = 0 ;
	ULTRASONIC_init();

	EnableInterrupts();
	LCD_displayString("    Distance    ");

	while(1) {
		LCD_moveCursor(1,6);


		sensor_reading = ULTRASONIC_readDistance();

		LCD_displayNumber( sensor_reading);
		LCD_displayString(" cm");
	}

}
