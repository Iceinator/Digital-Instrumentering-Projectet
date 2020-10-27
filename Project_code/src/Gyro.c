
#include "Gyro.h"
/*
void Gyro_write(uint8_t address,uint8_t data){
    //Seting CS=0
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,0);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    SPI_SendData8(SPI3, address);
    SPI_SendData8(SPI3, data);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) != SET) { }
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,1); // CS = 1 - End Transmission
}

uint16_t Gyro_readInit(uint8_t address){
    uint16_t Temp = 0;
    uint16_t Temp21 = 0;
    //Sends the reading command
    address |= 0x80;

    GPIO_WriteBit(GPIOC,GPIO_Pin_5,0);
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


    GPIO_WriteBit(GPIOC,GPIO_Pin_5,1);

    return Temp;
}

uint16_t Gyro_read(uint8_t address){
    uint16_t Temp = 0;
    uint16_t Temp21 = 0;
    //Sends the reading command
    address |= 0x80;

    GPIO_WriteBit(GPIOC,GPIO_Pin_5,0);
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


    GPIO_WriteBit(GPIOC,GPIO_Pin_5,1);

    return Temp;
}



void Gyro_xyz(struct Gyroxyz *Gyro1){
    Gyro1->x = (Gyro_read(OUT_X_H));
    //Gyro1->x |= (Gyro_read(OUT_X_L));

    Gyro1->y = (Gyro_read(OUT_Y_H));
    //Gyro1->y |= (Gyro_read(OUT_Y_L));

    Gyro1->z = (Gyro_read(OUT_Z_H));
    //Gyro1->z |= (Gyro_read(OUT_Z_L));
};

void Gyro_print(struct Gyroxyz *Gyro1){
    uint16_t x1 = Gyro1->x;
    uint16_t y1 = Gyro1->y;
    uint16_t z1 = Gyro1->z;


    //printf("%c[%d%c", ESC, 2, 0x4a);
    printf("%c[%d;%d%c", ESC, 2,  2, 0x66);
    printf("\nx=%d_y=%d_z=%d",x1,y1,z1);

}

void init_spi_Gyro(){
    // Enable Clocks
        // Enable Clock for GPIO Banks C
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,ENABLE);                // Enable Clock for SPI3
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
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




    //Configure pin PC_12 to MoSI
     // Define typedef struct for setting pins

    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
    //
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_12; // Set so the configuration is on pin 4
    GPIO_Init(GPIOC, &GPIO_InitStructAll);

    //Confiure pin PC8 as CS

     // Initialise RED LED
     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_5; // Set so the configuration is on pin 4
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


void Gyro_reset(){
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,1);

    // Configure Gyro //

    //check if connection has been established
    uint8_t temp = 0;
    temp = Gyro_readInit(WHO_AM_I);
    if(temp==0xD3){
        Gyro_write(CTRL_REG1,0b00001111);
        printf("n/Gyro power on");
    }
    else{
            printf("No connection to Gyro");
    }



}
*/
