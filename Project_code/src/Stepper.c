#include "Stepper.h"



void serialcom(){
    int8_t A[2]={0}; // Defines an array of two zeros
    char temp;
    // Initiate a loop, until break by while statement
    do {
        temp = uart_getc(); // Saves the last character input from keyboard. 0 if nothing is pressed.

        if(temp !=0 ){
                A[0]=temp;}// Saves the last input from keyboard at the first position in A.
        else {}
    }
    while ((A[0]!=49) && (A[0]!=50) && (A[0]!=51) && (A[0]!=57) && A[0]!=27);
}


void StepperControle(){
    int8_t A[2]={0};
    int8_t d = 0; // Defines an array of two zeros
    char temp;
    uint32_t POSITIONS[4] = { 0b0101, 0b1001, 0b1010, 0b0110 };
    // Initiate a loop, until break by while statement
    do {
        temp = uart_getc(); // Saves the last character input from keyboard. 0 if nothing is pressed.

        if(temp !=0 ){
                A[0]=temp;}// Saves the last input from keyboard at the first position in A.
        else {}
    }
    while ((A[0]!=49) && (A[0]!=50) && (A[0]!=51) && (A[0]!=57) && A[0]!=27);

    if(A[0]==49){
        for(int i = 0; i < 201; i++ ){
                d = POSITIONS[i&3];
                GPIO_WriteBit(GPIOC, GPIO_Pin_9 , d&1);
                GPIO_WriteBit(GPIOC, GPIO_Pin_5 , (d&2)>>1);
                GPIO_WriteBit(GPIOC, GPIO_Pin_8 , (d&4)>>2);
                GPIO_WriteBit(GPIOC, GPIO_Pin_6 , (d&8)>>3);
                for(uint32_t i = 0; i<400000;i++);
        }


    }

}

void setupStepper(){
    // Init GPIO used for LEDs - Set to output

    // Green - PC7
    // Blue  - PA9
    // Red   - PB4
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE); // Enable clock for GPIO Port C
     GPIO_InitTypeDef GPIO_InitStructAll; // Define typedef struct for setting pins

     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

    // Initialise Green LED
     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_8; // Set so the configuration is on pin 4
     GPIO_Init(GPIOC, &GPIO_InitStructAll);
    // Things to initialise is
    // PC0 - needed for right movement of the joystick
    // PA4 - Needed for up movement
    // PB5 - Needed for center push
    // PC1 - Needed for left movement
    // PB0 - Needed for down movement

     // Initialise Blue LED
     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_6; // Set so the configuration is on pin 4
     GPIO_Init(GPIOC, &GPIO_InitStructAll);

     // Initialise RED LED
     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_5; // Set so the configuration is on pin 4
     GPIO_Init(GPIOC, &GPIO_InitStructAll);

     GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct

     GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
     GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP;// Set to push pull
     GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_9; // Set so the configuration is on pin 4
     GPIO_Init(GPIOC, &GPIO_InitStructAll);



}

