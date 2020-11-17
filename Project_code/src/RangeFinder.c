
#include "RangeFinder.h"

void init_spi_RF(){
    // Enable Clocks
    // Enable Clock for GPIO B and the SPI3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    // Connect pins to SPI3
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_6);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_6);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_6);

    /** Configure pins PB3 CL and PB5 MOSI for 10 MHz alternate function**/
    GPIO_InitTypeDef GPIO_InitStructAll; // Define typedef struct for setting pins
    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_3; // Set so the configuration is on pin 4
    GPIO_Init(GPIOB, &GPIO_InitStructAll);

     // Define typedef struct for setting pins
    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_5; // Set so the configuration is on pin 4
    GPIO_Init(GPIOB, &GPIO_InitStructAll);

    /**Configure pin PB4 to MIS0**/
    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_4; // Set so the configuration is on pin 4
    GPIO_Init(GPIOB, &GPIO_InitStructAll);




    /**Confiure pin PBA6 to RDY and PB10 to SS**/
     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_IN; // Set as input
     GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_DOWN;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_6; // Set so the configuration is on pin 4
     GPIO_Init(GPIOA, &GPIO_InitStructAll);

     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_10; // Set so the configuration is on pin 4
     GPIO_Init(GPIOB, &GPIO_InitStructAll);

    // Configure SPI3
    SPI3->CR1 &= 0x3040; // Clear CR1 Register
    SPI3->CR1 |= 0x0000; // Configure direction (0x0000 - 2 Lines Full Duplex, 0x0400 - 2 Lines RX Only, 0x8000 - 1 Line RX, 0xC000 - 1 Line TX)
    SPI3->CR1 |= 0x0104; // Configure mode (0x0000 - Slave, 0x0104 - Master)
    SPI3->CR1 |= 0x0002; // Configure clock polarity (0x0000 - Low, 0x0002 - High)
    SPI3->CR1 |= 0x0000; // Configure clock phase (0x0000 - 1 Edge, 0x0001 - 2 Edge)
    SPI3->CR1 |= 0x0200; // Configure chip select (0x0000 - Hardware based, 0x0200 - Software based)
    SPI3->CR1 |= 0x0008; // Set Baud Rate Prescaler (0x0000 - 2, 0x0008 - 4, 0x0018 - 8, 0x0020 - 16, 0x0028 - 32, 0x0028 - 64, 0x0030 - 128, 0x0038 - 128)
    SPI3->CR1 |= 0x0000; // Set Bit Order (0x0000 - MSB First, 0x0080 - LSB First)
    SPI3->CR2 &= ~0x0F00; // Clear CR2 Register
    SPI3->CR2 |= 0x0700; // Set Number of Bits (0x0300 - 4, 0x0400 - 5, 0x0500 - 6, ...);
    SPI3->I2SCFGR &= ~0x0800; // Disable I2S
    SPI3->CRCPR = 7; // Set CRC polynomial order
    SPI3->CR2 &= ~0x1000;
    SPI3->CR2 |= 0x1000; // Configure RXFIFO return at (0x0000 - Half-full (16 bits), 0x1000 - Quarter-full (8 bits))
    SPI3->CR1 |= 0x0040; // Enable SPI3
    //for(uint32_t i;i<4000000;i++);
    RF_comtest();
    //for(uint32_t i;i<400000;i++);
}

void RDY_Check(){
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0){
        RF1.RDY=0;
        printf("hej");
    }
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==1){
        printf("dag");
        RF1.RDY=1;
    }
}


void RF_measure_Write(){
    if(RF1.RDY == 1){
    //Sends the reading command
    //Runs the communication
        GPIO_WriteBit(GPIOB,GPIO_Pin_10,0);
        while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
        SPI_SendData8(SPI3, 0x80);
        while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
        SPI_SendData8(SPI3, 0x01);
        while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
        while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){ }
        //Checks the RDY pin
        GPIO_WriteBit(GPIOB,GPIO_Pin_10,1);
        //for(uint32_t i=0;i<200000;++i);
        printf("\n go");

        RF1.RDY = 0;
    }

}

uint32_t RF_measure_Read(){
    uint32_t Temp = 0;
    uint16_t Temp21 = 0;

    if(RF1.RDY==1){

    //Sends the reading command
    //Checks the RDY to be done reading out
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,0);
    Temp21 = SPI_ReceiveData8(SPI3);
    SPI_SendData8(SPI3, 0x00);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, 0XFF);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, 0xFF);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, 0XFF);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, 0xFF);
    Temp = (SPI_I2S_ReceiveData16(SPI3)<<8);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, 0XFF);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, 0xFF);
    //Starts the SPI clock to Receive from the IMU
    //Checks if every thing has been send and Received
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){ }


    Temp |= SPI_I2S_ReceiveData16(SPI3);
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,1);

    }
    else{
    Temp = 2;
    printf("\n hf");
    }
    return Temp;
}

void RF_comtest(){
    while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0){}
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,1);
    for(uint32_t i=0;i<400000;i++);
    RF1.RDY = 1;

    //printf("\nRangeFinder communication established");


}

/*void EXTI9_5_IRQnHandler(void)
{
    printf("Joystick down interrupt called! \n");  // SET Calibration Flag - Checked by main
    //RF1.DATA = RF_measure_Read();
    EXTI_ClearITPendingBit(EXTI_Line6);  //Clear the interrupt pending bit
}

void init_interrupt2(void){
    // Setup of interrupt rutines:
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
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;

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
}*/
