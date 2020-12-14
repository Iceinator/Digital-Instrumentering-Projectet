////////////////////////////////////////////////////////////////////////////////
//****************************** ANSI ****************************************//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ANSI_H_
#define _ANSI_H_

/*
* This file holds print functions
* the STM32f302r8 Mikrocontroller.
* This file is part of the course project for Digital Instrumentation - 30021
* Author: Christoffer Frost
*/



////////////Includes////////////////
#include "stm32f30x_conf.h"

////////////Defines////////////////
#define ESC 0x1B


////////////Functions//////////////
void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void underline(uint8_t on);
void blink(uint8_t on);
void revvideo(uint8_t on);
void gotoxy(uint8_t y, uint8_t x);
void window(uint8_t y, uint8_t x, uint16_t h, uint16_t w);
void main_menu();




#endif /* _30021_IO_H_ */
