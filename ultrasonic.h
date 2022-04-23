 /******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the Ultrasonic sensor driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                           Definitions                                       *
 *******************************************************************************/

#define US_SENSOR_PORT            PORTB_ID
#define US_SENSOR_TRIGGER_PIN     PIN5_ID


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/


extern volatile uint8 g_edgeCount;
extern volatile uint16 g_timeHigh ;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description : Function to initialize the Ultrasonic Sensor Module
 * 	1. Initialize ICU Driver.
 * 	2. Set ICU Call Back Function.
 * 	3. Set the Trigger Pin as Output Pin.
 */

void ULTRASONIC_init(void) ;


/*
 * Description :Sends the trigger pulse to the Ultrasonic sensor.
 */

void ULTRASONIC_trigger(void) ;


/*
 * Description :reads the distance measured by the Sensor.
 */

uint16 ULTRASONIC_readDistance(void) ;

/*
 * Description :Call back function called by the ICU.
 */

void ULTRASONIC_edgeProcessing(void) ;



#endif /* ULTRASONIC_H_ */
