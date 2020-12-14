#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"       // Input/output library for this course
                            //Init code for timers, GPIO and EXTI
#include "Servo.h"
#include "ScanOp.h"
#include "IMU.h"
#include "SD_Driver.h"
#include "Timer.h"


///////////////////////////////////////////////////////////////////////
// ------------------------Global Variables--------------------------//
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// -------------------------- functions ----------------------------//
///////////////////////////////////////////////////////////////////////

void setup(void)
{
    init_usb_uart( 9600 ); // Initialize USB serial emulation at 9600 baud
    InitSDcard();
    //printf("\n\n Initializing all hardware components\n");
    initTimer();
    GPIO_INIT_Servo();
    TIM15_INIT_Servo();
    init_spi_IMU();
    IMU_reset();
//    TIM17_INIT_Servo();
    printf("\n\n Initializing all hardware components\n");
}

int main(void)
{
    setup();
    struct IMU IMU1;
    struct DATA DATA1;
    uint32_t jf = 6;
    jf = t1.mus;


    run_Scan(&IMU1,&DATA1);

    while(1)
    {
    IMU_xyz(&IMU1,Gyro_Read_Select);
    IMU_print(&IMU1,Gyro_Read_Select);
    }
}

