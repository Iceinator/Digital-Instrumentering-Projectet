#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h" // Input/output library for this course
#include "SDMU.h"

void EXTI_INIT()
{
    //Enable CYSCFG APB clock to gain write access to SYSCFG_EXTICRx registers
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

    //Select external interrupt pin source
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);

    //Create pre-defined struct with EXTI settings
    EXTI_InitTypeDef EXTI_InitStructure;

    //Initialize EXTI struct with default values
    EXTI_StructInit(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line6; // line 5 see [RM p. 215]
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;

    //Apply EXTI settings
    EXTI_Init(&EXTI_InitStructure);

    // setup NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
}

void GPIO_INIT_SDMU(void)
{
    //Enable clock for GPIO Port A,B,C
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    //Create pre-defined struct with GPIO settings
    GPIO_InitTypeDef GPIO_InitStruct;

    //Initialize GPIO struct with default values
    GPIO_StructInit(&GPIO_InitStruct);

//****TIM2 Output******//
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //Alternate function mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; //PA5
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    //Configure specific AF Mode for PA5 - TIM2 OC1 (CH1)
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1); //Refer to page 43 [DS]

//****TIM16 Output******//
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //Alternate function mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12; //PA12
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    //Configure specific AF Mode for PA12 - TIM16 OC1 (CH1)
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_1); //Refer to page 44 [DS]

//****EXTI9_5 PA6 interrupt input****//
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //Input mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6; //PA6
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; //PA6
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TIM2_INIT_SDMU(void)
{
    //Enable peripheral clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //Create pre-defined struct with time base settings
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    //Initialize time base struct with default values
    TIM_TimeBaseStructInit(&TIM_InitStructure);

    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 4500000;
    TIM_InitStructure.TIM_Prescaler = 1;

    //Apply time base settings to timer
    TIM_TimeBaseInit(TIM2,&TIM_InitStructure);

    //Create pre-defined struct with OC settings
    TIM_OCInitTypeDef TIM_OCInitStruct;
    //Initialize OC struct with default values
    TIM_OCStructInit(&TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;

    //Apply OC settings to OC1/TIM2
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);

    //*****************************************************
    //Mentioned as mandatory on page 452 [SPL] when in PWM mode - whats the purpose?
    //TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); //Seemingly works without
    //*****************************************************

    //Set compare match value
    TIM_SetCompare1(TIM2, 10000);

//In case interrupt is needed for debugging reasons
/*
    //Configuring Interrupt for timer:
    //Create pre-defined struct with interrupt settings
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //Picking interrupt source
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //CHECK****
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //CHECK****

    //Apply Interrupt settings
    NVIC_Init(&NVIC_InitStructure);

    //Apply timer interrupt settings
    TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
*/

    //*****************************************************
    //Enable TIM main outputs - page 494 [SPL]
    //TIM_CtrlPWMOutputs(TIM2, DISABLE); //Has no effect! seems to work either way
    //*****************************************************

    //Start the timer
    TIM_Cmd(TIM2, ENABLE);
}

void TIM16_INIT_SDMU(void)
{
    //Enable peripheral clock for TIM3
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);

    //Create pre-defined struct with time base settings
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    //Initialize time base struct with default values
    TIM_TimeBaseStructInit(&TIM_InitStructure);

    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 480;
    TIM_InitStructure.TIM_Prescaler = 1;

    //Apply time base settings to timer
    TIM_TimeBaseInit(TIM16,&TIM_InitStructure);

    //Create pre-defined struct with OC settings
    TIM_OCInitTypeDef TIM_OCInitStruct;
    //Initialize OC struct with default values
    TIM_OCStructInit(&TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;

    //Apply OC settings to OC1/TIM16
    TIM_OC1Init(TIM16, &TIM_OCInitStruct);

    //*****************************************************
    //Mentioned as mandatory on page 452 [SPL] when in PWM mode - whats the purpose?
    //TIM_OC1PreloadConfig(TIM16, TIM_OCPreload_Enable); //Seemingly works without
    //*****************************************************

    //Set compare match value
    TIM_SetCompare1(TIM16, 240);

    //Configuring Interrupt for timer:
    //Create pre-defined struct with interrupt settings
    NVIC_InitTypeDef NVIC_InitStructure;

    //Initialize struct with default values
    //NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM16_IRQn; //Picking interrupt source
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //CHECK****
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //CHECK****
    //Apply timer interrupt settings
    NVIC_Init(&NVIC_InitStructure);

    //Apply timer interrupt settings
    TIM_ITConfig(TIM16, TIM_IT_CC1, ENABLE);

    //*****************************************************
    //Enable TIM main outputs - page 494 [SPL]
    TIM_CtrlPWMOutputs(TIM16, ENABLE); //HAS AN EFFECT IN THIS CASE! - IMPORTANT
    //*****************************************************

    //TIM_Cmd(TIM16, ENABLE); //Start counting ECHO pulse width - enabled in EXTI!
}
