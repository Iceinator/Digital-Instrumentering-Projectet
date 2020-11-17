#include "Servo.h"
#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"

void GPIO_INIT_Servo(void)
{
    //Enable clock for GPIO Port ,B
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    //Create pre-defined struct with GPIO settings
    GPIO_InitTypeDef GPIO_InitStruct;

    //Initialize GPIO struct with default values
    GPIO_StructInit(&GPIO_InitStruct);

//****TIM15 Output******//
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //Alternate function mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15; //PB15
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    //Configure specific AF Mode for PB15 - TIM15 OC2 (CH2)
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_1); //Refer to page 43 [DS]

//****TIM15 Output******//
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //Alternate function mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14; //PB14
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    //Configure specific AF Mode for PB14 - TIM15 OC1 (CH1)
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_1); //Refer to page 43 [DS]



}
void TIM15_INIT_Servo(void)
{
    //Enable peripheral clock for TIM3
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);

    //Create pre-defined struct with time base settings
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    //Initialize time base struct with default values
    TIM_TimeBaseStructInit(&TIM_InitStructure);

    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 64000; //Period set to 20ms
    TIM_InitStructure.TIM_Prescaler = 19;

    //Apply time base settings to timer
    TIM_TimeBaseInit(TIM15,&TIM_InitStructure);

    //Create pre-defined struct with OC settings
    TIM_OCInitTypeDef TIM_OCInitStruct;
    //Initialize OC struct with default values
    TIM_OCStructInit(&TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;

    //Apply OC settings to OC1/TIM16
    TIM_OC1Init(TIM15, &TIM_OCInitStruct);
    TIM_OC2Init(TIM15, &TIM_OCInitStruct);

    //*****************************************************
    //Mentioned as mandatory on page 452 [SPL] when in PWM mode - whats the purpose?
    //TIM_OC1PreloadConfig(TIM16, TIM_OCPreload_Enable); //Seemingly works without
    //*****************************************************
    TIM_SetCompare1(TIM15, (0*18+3200));
    TIM_SetCompare2(TIM15, (0*18+3200));
    //Configuring Interrupt for timer:
    //Create pre-defined struct with interrupt settings
    NVIC_InitTypeDef NVIC_InitStructure;

    //Initialize struct with default values
    //NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM15_IRQn; //Picking interrupt source
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //CHECK****
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //CHECK****
    //Apply timer interrupt settings
    NVIC_Init(&NVIC_InitStructure);

    //Apply timer interrupt settings
    TIM_ITConfig(TIM15, TIM_IT_CC2, ENABLE);
    TIM_ITConfig(TIM15, TIM_IT_CC1, ENABLE);

    //*****************************************************
    //Enable TIM main outputs - page 494 [SPL]
    TIM_CtrlPWMOutputs(TIM15, ENABLE); //HAS AN EFFECT IN THIS CASE! - IMPORTANT
    //*****************************************************

    TIM_Cmd(TIM15, ENABLE); //Start counting ECHO pulse width - enabled in EXTI!


}

void Posistion_Select(uint8_t xDeg, uint8_t yDeg){

    TIM_SetCompare1(TIM15, (xDeg*18+3200));
    TIM_SetCompare2(TIM15, (yDeg*18+3200));
}
