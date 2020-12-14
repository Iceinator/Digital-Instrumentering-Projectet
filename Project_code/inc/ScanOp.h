////////////////////////////////////////////////////////////////////////////////
//****************************** ANSI ****************************************//
////////////////////////////////////////////////////////////////////////////////

#ifndef _SCANOP_H_
#define _SCANOP_H_

/*
* This file holds print functions
* the STM32f302r8 Mikrocontroller.
* This file is part of the course project for Digital Instrumentation - 30021
* Author: Christoffer Frost
*/



////////////Includes////////////////
#include "stm32f30x_conf.h"
#include "Servo.h"
#include "IMU.h"
#include "Timer.h"
#include "SD_Driver.h"
////////////Defines////////////////
#define Startposy 60
#define Startposx 60
#define FIX2_SHIFT 2
#define FIX2_MULT(a, b) ( (a)*(b) >> FIX2_SHIFT )
#define FIX2_DIV(a, b) ( ((a) << FIX2_SHIFT) / b )
#define Stopval 100

//////////////// Structs///////////
struct DATA {
    int8_t XDeg;
    int8_t YDeg;
    int8_t ZDeg;

    uint16_t DistRF;
    uint16_t DistUS;

};


////////////Functions//////////////
void run_Scan(struct IMU *IMU1,struct DATA *DATA1);
void Turn_Check_and_data(struct IMU *IMU1,struct DATA *DATA1);
void DATA_load_to_SD(struct DATA *DATA1);

#endif /* _SCANOP_H_ */
