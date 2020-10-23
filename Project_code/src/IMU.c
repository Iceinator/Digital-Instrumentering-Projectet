
#include "IMU.h"

//Sets the CS low for the given Chip
void CS_Start(uint8_t CS){
    if(CS == 1){
        GPIO_WriteBit(GPIOC,GPIO_Pin_5,0);
    }
    else if(CS == 2){
        GPIO_WriteBit(GPIOC,GPIO_Pin_6,0);
    }
    else{
        printf("No SC has been selected")
    }

}

//Sets the CS high for the given Chip
void CS_End(uint8_t CS){
    if(CS == 1){
        GPIO_WriteBit(GPIOC,GPIO_Pin_5,1);
    }
    else if(CS == 2){
        GPIO_WriteBit(GPIOC,GPIO_Pin_6,1);
    }
    else{
        printf("No SC has been selected")
    }
}

//Rights To a given register with CS
void IMU_write(uint8_t address,uint8_t data,uint8_t CS){
    //Seting CS=0

    CS_Start(CS);

      while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, address);
    SPI_SendData8(SPI3, data);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }

    CS_End(CS);
     // End Transmission
}

//Read register on the address given the CS
uint16_t IMU_readInit(uint8_t address,uint8_t CS){
    uint16_t Temp = 0;
    uint16_t Temp21 = 0;
    //Sends the reading command
    address |= 0x80;


    //Check what CS has been chosen - 1=AG - 2=Mag
    CS_Start(CS);

    //Runs the communication
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, address);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    Temp21 = SPI_ReceiveData8(SPI3);
    //for(uint32_t i = 0; i<4000;i++);
    SPI_SendData8(SPI3, 0x00);
    //for(uint32_t i = 0; i<4000;i++);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    //for(uint32_t i = 0; i<4000;i++);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){ }

    Temp = SPI_ReceiveData8(SPI3);

    CS_End(CS);

    return Temp;
}

//Read register on the address given the CS
uint16_t IMU_read(uint8_t address,uint8_t CS){
    uint16_t Temp = 0;
    uint16_t Temp21 = 0;
    //Sends the reading command
    address |= 0x80;

    CS_Start(CS)

    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, address);
    //while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    Temp21 = SPI_ReceiveData8(SPI3);
    //for(uint32_t i = 0; i<4000;i++);
    SPI_SendData8(SPI3, 0x00);
    //for(uint32_t i = 0; i<4000;i++);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    //for(uint32_t i = 0; i<4000;i++);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){ }

    Temp = SPI_ReceiveData8(SPI3);

    //Resets the SC
    CS_End(CS);

    return Temp;
}

//This function Reads the diffent sensor values
void IMU_G_xyz(struct IMU *IMU1,uint8_t SS){

    if(SS&0x01==Gyro_Select){
        //Read the values for the Gyro
        IMU1->xGyro = (IMU_read(OUT_X_H_G));
        IMU1->x |= (IMU_read(OUT_X_L_G));

        IMU1->yGyro = (IMU_read(OUT_Y_H_G));
        IMU1->y |= (IMU_read(OUT_Y_L_G));

        IMU1->zGyro = (IMU_read(OUT_Z_H_G));
        Gyro1->z |= (IMU_read(OUT_Z_L_G));
    }

    if(SS&0x02==XL_Select){
        //Read the values of the Accelerometer
        IMU1->xAccel = (IMU_read(OUT_X_H_XL));
        IMU1->xAccel |= (IMU_read(OUT_X_L_XL));

        IMU1->yAccel = (IMU_read(OUT_Y_H_XL));
        IMU1->yAccel |= (IMU_read(OUT_Y_L_XL));

        IMU1->zAccel = (IMU_read(OUT_Z_H_XL));
        IMU1->zAccel |= (IMU_read(OUT_Z_L_XL));
    }
    if(SS&0x04==Mag_Select){
        //Read the values of the  Magnetic sensor
        IMU1->xMag = (IMU_read(OUT_X_H_M));
        IMU1->xMag |= (IMU_read(OUT_X_L_M));

        IMU1->yMag = (IMU_read(OUT_Y_H_M));
        IMU1->yMag |= (IMU_read(OUT_Y_L_M));

        IMU1->zMag = (IMU_read(OUT_Z_H_M));
        IMU1->zMag |= (IMU_read(OUT_Z_L_M));
    }

};

//Prints out the value xyz for the chosen sensor
void IMU_print(struct IMU *IMU1,uint8_t SS){

    if(SS&0x01==Gyro_Select){
    printf("%c[%d;%d%c", ESC, 2,  2, 0x66);
    printf("Gyro: x=%d_y=%d_z=%d",IMU1->xGyro,IMU1->yGyro,IMU1->zGyro);
    }
    if(SS&0x02==Gyro_Select){
    printf("%c[%d;%d%c", ESC, 2,  4, 0x66);
    printf("Gyro: x=%d_y=%d_z=%d",IMU1->xAccel,IMU1->yAccel,IMU1->zAccel);
    }
    if(SS&0x04==Gyro_Select){
    printf("%c[%d;%d%c", ESC, 2,  6, 0x66);
    printf("Gyro: x=%d_y=%d_z=%d",IMU1->xMag,IMU1->yMag,IMU1->zMag);
    }
}

void init_spi_IMU(){
    // Enable Clocks
        // Enable Clock for GPIO Banks C
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,ENABLE);                // Enable Clock for SPI3
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);


    // Connect pins to SPI2
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_6);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_6);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_6);

    // Configure pins PC10 CL and PC11 MISO for 10 MHz alternate function
    GPIO_InitTypeDef GPIO_InitStructAll; // Define typedef struct for setting pins
    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_10; // Set so the configuration is on pin 4
    GPIO_Init(GPIOC, &GPIO_InitStructAll);

     // Define typedef struct for setting pins
    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_11; // Set so the configuration is on pin 4
    GPIO_Init(GPIOC, &GPIO_InitStructAll);




    /**Configure pin PC_12 and PB4 to MoSI**/

    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_12; // Set so the configuration is on pin 4
    GPIO_Init(GPIOC, &GPIO_InitStructAll);

    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_12; // Set so the configuration is on pin 4
    GPIO_Init(GPIOC, &GPIO_InitStructAll);



    /**Confiure pin PC5 as CS_AG and PC6 as CS_M **/
     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_5; // Set so the configuration is on pin 4
     GPIO_Init(GPIOC, &GPIO_InitStructAll);

     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_6; // Set so the configuration is on pin 4
     GPIO_Init(GPIOC, &GPIO_InitStructAll);

    // Configure SPI3
    SPI3->CR1 &= 0x3040; // Clear CR1 Register
    SPI3->CR1 |= 0x0000; // Configure direction (0x0000 - 2 Lines Full Duplex, 0x0400 - 2 Lines RX Only, 0x8000 - 1 Line RX, 0xC000 - 1 Line TX)
    SPI3->CR1 |= 0x0104; // Configure mode (0x0000 - Slave, 0x0104 - Master)
    SPI3->CR1 |= 0x0002; // Configure clock polarity (0x0000 - Low, 0x0002 - High)
    SPI3->CR1 |= 0x0001; // Configure clock phase (0x0000 - 1 Edge, 0x0001 - 2 Edge)
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

    //Gyro_reset();
}

//Checks for connection and powers on the sensors
void IMU_reset(){
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,1);
    GPIO_WriteBit(GPIOC,GPIO_Pin_6,1);
    // Configure Gyro //

    //check if connection has been established
    uint8_t temp = 0;
    temp = IMU_readInit(WHO_AM_I,CS_AG);
    if(temp==0xD3){
        IMU_write(CTRL_REG4,0b00111000);
        printf("n/Gyro power on");
        IMU_write(CTRL_REG5_XL,0b10111000);
        printf("n/XL power on");
    }
    else{
            printf("No connection to AG");
    }
    temp = 0;
    temp = IMU_readInit(WHO_AM_I,CS_M);
    if(temp==0xD3){
        IMU_write(CTRL_REG1_M,0b01000000);
        printf("n/Mag power on");
    }
    else{
            printf("No connection to MAG");
    }


}
