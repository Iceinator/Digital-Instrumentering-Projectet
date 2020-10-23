#include "SD_Driver.h"
#include "30021_io.h"


void InitSDcard(){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource4,GPIO_AF_7);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_7);

    GPIO_InitTypeDef GPIO_InitStructAll; // Define typedef struct for setting pins

    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

    //
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;// Set to push pull
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_4; // Set so the configuration is on pin 4
    GPIO_Init(GPIOC, &GPIO_InitStructAll);

    GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

    //
    GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF; // Set as input
    GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
    GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_10; // Set so the configuration is on pin 4
    GPIO_Init(GPIOA, &GPIO_InitStructAll);


    USART_InitTypeDef USART_InitStructAll;
    USART_StructInit(&USART_InitStructAll);

    //Init of USART transmit
    USART_InitStructAll.USART_BaudRate = 9600*2;
    USART_InitStructAll.USART_WordLength = 8;
    USART_InitStructAll.USART_StopBits = 1;
    USART_InitStructAll.USART_Parity= USART_Parity_No;

    USART_InitStructAll.USART_Mode = USART_Mode_Tx;
    USART_InitStructAll.USART_Mode = USART_Mode_Rx;

    USART_InitStructAll.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(GPIOA,&USART_InitStructAll);


    //Init of the clocks
    USART_ClockInitTypeDef USART_ClockStructAll;
    USART_ClockStructInit(&USART_ClockStructAll);

    USART_ClockStructAll.USART_Clock = USART_Clock_Enable;
    USART_ClockStructAll.USART_CPOL = USART_CPOL_Low;
    USART_ClockStructAll.USART_CPHA = USART_CPHA_1Edge;
    USART_ClockStructAll.USART_LastBit = USART_LastBit_Enable;
    USART_ClockInit(USART1,&USART_ClockStructAll);

    USART_Cmd(USART1,ENABLE);

}

void uart_putc_SD(uint8_t c) {
    USART_SendData(USART1, (uint8_t)c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)  == RESET){}
}

uint8_t uart_SD_read() {
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){};
    uint8_t c = (uint8_t)USART_ReceiveData(USART1);

    return c;
}
/*
uint8_t uart_Putty_SD_write() {
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){};
    uint8_t c = (uint8_t)USART_ReceiveData(USART1);

    if (c != 0x0D) { uart_putc_SD(c); }

    return c;
}
*/
