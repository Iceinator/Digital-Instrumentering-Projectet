////////////////////////////////////////////////////////////////////////////////
//****************************** RangeFinder ****************************************//
////////////////////////////////////////////////////////////////////////////////

#ifndef _RANGEFINDER_H_
#define _RANGEFINDER_H_

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
struct FlagRF {
    uint16_t RDY;
    uint32_t DATA;
};
struct FlagRF RF1;


////////////Functions//////////////
void init_spi_RF();
uint32_t RF_measure_Read();
void RF_measure_Write();
void RF_comtest();
void init_interrupt2(void);
void RDY_Check();

#endif /* _RangeFinder_H_ */
