#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"       // Input/output library for this course
#include "SDMU.h"           //Init code for timers, GPIO and EXTI

///////////////////////////////////////////////////////////////////////
// ------------------------Global Variables--------------------------//
///////////////////////////////////////////////////////////////////////
volatile uint16_t ticks = 0;
volatile uint8_t Calc_Pulse_Flag = 0;

///////////////////////////////////////////////////////////////////////
// -------------------------- functions ----------------------------//
///////////////////////////////////////////////////////////////////////
void EXTI9_5_IRQHandler(void)
{
    uint8_t PA6_LEVEL = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);

    if(PA6_LEVEL == 1)  //Rising Edge - Echo went HIGH
    {
        TIM_Cmd(TIM16, ENABLE); //Start counting ECHO pulse width
    }
    else                //Falling Edge - Echo went LOW
    {
        TIM_Cmd(TIM16, DISABLE); //Stop counting ECHO pulse width
        Calc_Pulse_Flag = 1;
        TIM_SetCounter(TIM16, 0xFFFFFFFF);
    }
    //Clear interrupt pending bit - prevents re-firing
    EXTI_ClearITPendingBit(EXTI_Line6);
    //EXTI_ClearFlag(EXTI_Line6); //Does the same as above
}

void TIM1_UP_TIM16_IRQHandler(void)
{
    ticks++;
    TIM_ClearITPendingBit(TIM16, TIM_IT_CC1) ;
}

void setup(void)
{
    init_usb_uart( 9600 ); // Initialize USB serial emulation at 9600 baud
    printf("\n\n Initializing all hardware components\n");
}

int main(void)
{
    float       Dist = 0;
    uint16_t    PulseWidth = 0;
    setup();
    GPIO_INIT_SDMU();
    EXTI_INIT();
    TIM16_INIT_SDMU();
    TIM2_INIT_SDMU();
    while(1)
    {
        if(Calc_Pulse_Flag == 1)
        {
            PulseWidth = ticks * 15;    //TIM16 CC occurs with 15uS period
            Dist = PulseWidth / 58.0;   //Calculating distance in cm, as given in datasheets
            printf("\n Pulse Width: %u [us] --> %f [cm]", PulseWidth, Dist);
            Calc_Pulse_Flag = 0;
            ticks = 0;
        }
        else
        {
            //Do nothing
        }
    }
}
