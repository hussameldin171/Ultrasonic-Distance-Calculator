/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultrasonic sensor driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#include "gpio.h"
#include "ultrasonic.h"
#include "icu.h"
#include "util/delay.h"
#include "math.h"

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/
volatile uint8 g_edgeCount = 0 ;
volatile uint16 g_timeHigh = 0 ;

static const ICU_configType ULTRASONIC_config = {F_CPU_8 , RISING_EDGE};


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the Ultrasonic Sensor Module
 * 	1. Initialize ICU Driver.
 * 	2. Set ICU Call Back Function.
 * 	3. Set the Trigger Pin as Output Pin.
 */

void ULTRASONIC_init(void)  {

	ICU_init(&ULTRASONIC_config);

	ICU_setCallBack(ULTRASONIC_edgeProcessing);

	GPIO_setupPinDirection(US_SENSOR_PORT , US_SENSOR_TRIGGER_PIN , PIN_OUTPUT);


}

/*
 * Description :Sends the trigger pulse to the Ultrasonic sensor.
 */

void ULTRASONIC_trigger(void) {

	GPIO_writePin(US_SENSOR_PORT , US_SENSOR_TRIGGER_PIN ,LOGIC_HIGH);

	_delay_us(20);

	GPIO_writePin(US_SENSOR_PORT , US_SENSOR_TRIGGER_PIN ,LOGIC_LOW);
}


/*
 * Description :reads the distance measured by the Sensor.
 */

uint16 ULTRASONIC_readDistance(void) {

	uint16 distance ;

	ULTRASONIC_trigger();


		distance  = g_timeHigh * 0.017 + 1 + ((g_timeHigh * 0.017 + 1)>58 ? 1:0) ;


	return distance ;

}

/*
 * Description :Call back function called by the ICU.
 */

void ULTRASONIC_edgeProcessing(void) {

	g_edgeCount++;

	if(g_edgeCount == 1) {

		ICU_clearTimer();
		ICU_setEdgeToDetect(FALLING_EDGE);

	}
	else if(g_edgeCount == 2) {

		g_timeHigh = ICU_regValue();

		ICU_setEdgeToDetect(RISING_EDGE);

		g_edgeCount = 0 ;
	}

}


