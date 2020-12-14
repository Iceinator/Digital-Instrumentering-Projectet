////////////////////////////////////////////////////////////////////////////////
//****************************** TIMER ****************************************//
////////////////////////////////////////////////////////////////////////////////


#ifndef _TIMER_H_
#define _TIMER_H_
///////////////incleds/////////////////////////////////
#include "stm32f30x_conf.h"
#include "30021_io.h"
extern uint8_t stopState;
/////////////////// Exported Struct ////////////////////

struct time {
    uint32_t mus;
};
struct time time1;
struct time_SDMU {
    uint16_t mus;
    uint16_t ms;
};
struct time_SDMU T_SDMU1;
struct Timer{ //Used for the integrator
    uint32_t mus;


};
struct Timer t1;

/////////////////////////////////////////////////////////////
///////////////// function declaration //////////////////////
/////////////////////////////////////////////////////////////
void initTimer();
void initstopwatch();
void PrintWatch();
void PrintStopwatch(uint8_t joyStickStateLocal);
void timer16_clock_init();
void initTimer_TIM3();
void TIM2_IRQHandler(void);



#endif


