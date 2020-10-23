
#ifndef _SD_Driver_H_
#define _SD_Driver_H_



#include "stm32f30x_conf.h"
#include "30021_io.h"



void InitSDcard();
void uart_putc_SD(uint8_t c);
uint8_t uart_SD_read();
#endif
