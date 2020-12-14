////////////////////////////////////////////////////////////////////////////////
//****************************** Timer ****************************************//
////////////////////////////////////////////////////////////////////////////////
/*
* This file holds the diver for the timer
* the STM32f302r8 Mikrocontroller.
* This file is part of the course project for Digital Instrumentation - 30021
* Author: Christoffer Frost- s183813
*/
#include "stm32f30x_conf.h"
#include "30021_io.h"
#include "GPIO.h"
#include "Timer.h"
extern uint8_t joyStickStateLocal;
//Timer set to 100Hz at highest priority
void initTimer_TIM3(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_InitStructure;
 TIM_TimeBaseStructInit(&TIM_InitStructure);
 TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
 TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_InitStructure.TIM_Period = 6138;
 TIM_InitStructure.TIM_Prescaler = 100;
 TIM_TimeBaseInit(TIM3,&TIM_InitStructure);
 // NVIC for timer
 NVIC_InitTypeDef NVIC_InitStructure;
 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 NVIC_Init(&NVIC_InitStructure);
 TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
 TIM_Cmd(TIM3,ENABLE);
}
/*
void TIM3_IRQnHandler(void) {
    time1.mus +=10;

    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
*/

void initTimer(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_TimeBaseStructInit(&TIM_InitStructure);
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 63; // Double check this
    TIM_InitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM2,&TIM_InitStructure);
    // NVIC for timer
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2,ENABLE);



}
/*
void initTimer(){
     RCC->APB1ENR |= RCC_APB1Periph_TIM2;// Enable clock line to timer 2;
     TIM2->CR1 |= 0x0001;// Configure timer 2
     TIM2->ARR = 639999; // Set reload value
     TIM2->PSC = 0;// Set prescale value


      TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
      NVIC_SetPriority(TIM2_IRQn, 1); // Set interrupt priority
      NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt

}
*/
void TIM2_IRQHandler(void) {
    t1.mus += 10;
 //ICValue1 = TIM_GetCapture1(TIM2); // Period
 //ICValue2 = TIM_GetCapture2(TIM2); // Duty/Width
 //ICValid = 1;
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

// - Uncomment old Timer IRQ for the stop watch.



void timer16_clock_init(){

    RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM16,ENABLE);
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_TimeBaseStructInit(&TIM_InitStructure);
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 254; // Double check this
    TIM_InitStructure.TIM_Prescaler = 24;
    TIM_TimeBaseInit(TIM16,&TIM_InitStructure);
    // NVIC for timer
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState=TIM_OSSRState_Enable;
    TIM_OC1Init(TIM16,&TIM_OCInitStruct);


    TIM_OC1PreloadConfig(TIM16,TIM_OCPreload_Enable);
    TIM_CtrlPWMOutputs(TIM16, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM16,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM16,ENABLE);

    IM_SetCompare1(TIM16,256);
    TIM_CtrlPWMOutputs(TIM16, ENABLE);

}
/*
 void initstopwatch(){
    time1.hs = 0;
    time1.s = 0;
    time1.m = 0;
    time1.h = 0;
}

void PrintWatch(){
        printf("\n%d",time1.h);
        printf(":%d",time1.m);
        printf(":%d",time1.s);
        printf(":%d",time1.hs);
}
*/
void PrintStopwatch(uint8_t joyStickStateLocal){

    if(joyStickStateLocal == 16){
        printf("joyStick is Pressed Center\n");
        PrintWatch();
        if(stopState == 1){
            stopState = 0;
        }
        else if(stopState == 0){
            stopState = 1;
        }
        printf("joyStick is Pressed Center\n");
    }

    else if(joyStickStateLocal == 4){
        if(stopState == 0){
            PrintWatch();
        }
    }
    else if(joyStickStateLocal == 8){
        if(stopState == 0){
            PrintWatch();
        }
    }
    else if(joyStickStateLocal == 2){
        //printf("%c[%d%c", 0x1B,2, 0x4a);
        initstopwatch();
        stopState = 1;
    }
    else{
        //printf("%c[%d;%d%c", 0x1B, 1,  1, 0x66);
        if(stopState == 0){
            PrintWatch();
        }

    }
}









