#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"       // Input/output library for this course
#include "SDMU.h"           //Init code for timers, GPIO and EXTI

#include "Servo.h"
#include "RangeFinder.h"
///////////////////////////////////////////////////////////////////////
// ------------------------Global Variables--------------------------//
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// -------------------------- functions ----------------------------//
///////////////////////////////////////////////////////////////////////
void EXTI9_5_IRQnHandler(void)
{
    printf("Joystick down interrupt called! \n");  // SET Calibration Flag - Checked by main
    //RF1.DATA = RF_measure_Read();
    EXTI_ClearITPendingBit(EXTI_Line6);  //Clear the interrupt pending bit
}


void setup(void)
{
    init_usb_uart( 9600 ); // Initialize USB serial emulation at 9600 baud
    init_spi_RF();
    //init_interrupt2();
    //GPIO_INIT_Servo();
    //TIM15_INIT_Servo();
    printf("\n\n Initializing all hardware components\n");
}

int main(void)
{
    setup();
    uint32_t afstand = 0;
    RF_measure_Write();
    while(1)
    {
    //Posistion_Select(90,90);
    RDY_Check();
    printf("shafha");
    RF_measure_Read();
    RF_measure_Write();
    //RF_measure_Read();
    //afstand = RF1.DATA;
    //printf("\n\n DATAred\n");
    //Posistion_Select(180,180);
    //for(uint32_t i=1;i=100000;i++);
    //Posistion_Select(0,0);
    }
    }

