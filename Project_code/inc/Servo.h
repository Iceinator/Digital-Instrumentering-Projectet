////////////////////////////////////////////////////////////////////////////////
//****************************** SERVO ****************************************//
////////////////////////////////////////////////////////////////////////////////

#ifndef _SERVO_H_
#define _SERVO_H_

/*
* This file holds print functions
* the STM32f302r8 Mikrocontroller.
* This file is part of the course project for Digital Instrumentation - 30021
* Author: Christoffer Frost
*/



////////////Includes///////////////

#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"
////////////Defines////////////////



////////////Functions//////////////
void Posistion_Select(uint8_t xDeg, uint8_t yDeg);
void TIM15_INIT_Servo(void);
void GPIO_INIT_Servo(void);


#endif /* _SERVO_IO_H_ */

