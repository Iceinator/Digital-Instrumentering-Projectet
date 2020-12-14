#include "Servo.h"


void GPIO_INIT_Servo(void)
{
    //Enable clock for GPIO Port ,B,A
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    //Create pre-defined struct with GPIO settings
    GPIO_InitTypeDef GPIO_InitStruct;

    //Initialize GPIO struct with default values
    GPIO_StructInit(&GPIO_InitStruct);

//****TIM15 Output******//
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //Alternate function mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7; //PB15
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    //Configure specific AF Mode for PA
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1);

//****TIM15 Output******//
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //Alternate function mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14; //PB14
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    //Configure specific AF Mode for PB14 -
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_1);



}
void TIM15_INIT_Servo(void)
{
    //Enable peripheral clock for TIM15
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);

    //Create pre-defined struct with time base settings
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    //Initialize time base struct with default values
    TIM_TimeBaseStructInit(&TIM_InitStructure);
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 64000; //Period set to 20ms
    TIM_InitStructure.TIM_Prescaler = 19;
    TIM_TimeBaseInit(TIM15,&TIM_InitStructure);

    //TIM_ITConfig(TIM15,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM15,ENABLE);

    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1Init(TIM15, &TIM_OCInitStruct);


    TIM_OC1PreloadConfig(TIM15, TIM_OCPreload_Enable);
    TIM_CtrlPWMOutputs(TIM15, ENABLE);
    TIM_Cmd(TIM15,ENABLE);
    TIM_SetCompare1(TIM15,(90*18+3200));



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //Enable peripheral clock for TIM3
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);

    //Create pre-defined struct with time base settings
    //TIM_TimeBaseInitTypeDef TIM_InitStructure;
    //Initialize time base struct with default values
    TIM_TimeBaseStructInit(&TIM_InitStructure);
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 64000; //Period set to 20ms
    TIM_InitStructure.TIM_Prescaler = 19;
    TIM_TimeBaseInit(TIM17,&TIM_InitStructure);

    //TIM_ITConfig(TIM17,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM17,ENABLE);

    //TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1Init(TIM17, &TIM_OCInitStruct);


    TIM_OC1PreloadConfig(TIM17, TIM_OCPreload_Enable);
    TIM_CtrlPWMOutputs(TIM17, ENABLE);
    TIM_Cmd(TIM17,ENABLE);
    TIM_SetCompare1(TIM17,(90*18+3200));
    //TIM_SetCompare2(TIM15, (60*18+3200));
}


void Posistion_Select(uint8_t xDeg, uint8_t yDeg){

    TIM_SetCompare1(TIM15, (xDeg*18+3200));
    TIM_SetCompare1(TIM17, (yDeg*18+3200));
}


