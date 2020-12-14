#include "ScanOp.h"
//This is the main Scan function
void run_Scan(struct IMU *IMU1,struct DATA *DATA1){
    //Sets the start position
    Posistion_Select(Startposy,Startposx);

    //Temps
    uint8_t f = 0;
    uint8_t NPx=Startposx;
    uint8_t NPy=Startposy;
    int16_t W = 0;
    int16_t D = 0;
    uint16_t i = 0;
    uint16_t j = 0;

    //Loop that that sets the positions for the arm to go to
    for(i=0;i<Startposx;i++){
        NPx ++;

        for(j=0;j<Startposy;j++){ //This loop is for horizontal movement anti clockwise
            //Turns the arm to the next pos
            Posistion_Select(NPx,NPy);

            //Whaits for the arm to turn and measures the turn
            Turn_Check_and_data(IMU1,DATA1);
            //Run funktion that makes range measurement
            DATA_load_to_SD(DATA1);
            NPy++;
        }
        NPx++;
        for(j=0;j<Startposy;j++){//This loop is for horizontal movement clockwise
            Posistion_Select(NPx,NPy);
            Turn_Check_and_data(IMU1,DATA1);
            //Run funktion that makes range measurement
            DATA_load_to_SD(DATA1);

            NPy--;
        }

    }

    printf("scann complete");

}

//This is used to check if the servo is done turning, and records measures the degrees that have been turned.
void Turn_Check_and_data(struct IMU *IMU1,struct DATA *DATA1){
    uint8_t TurnFlag = 1; //Flag that is high when the arm is turning
    //temps
    int8_t xDegrees = 0;
    int8_t yDegrees = 0;
    int8_t zDegrees = 0;

    //As there is some amount of rotation going on, when the IMU is at rest, this compensates
    IMU_xyz(IMU1,Gyro_Read_Select);
    int16_t calvalx = IMU1->xGyro;
    int16_t calvaly = IMU1->yGyro;
    int16_t calvalz = IMU1->zGyro;


    //loop that runs while the servo is turning
    while(TurnFlag == 1){

        //Resets the time used for integration

        /***************************************************
        Tiden er styret af TIM2 og skal måske også justeres
        ***************************************************/
        t1.mus = 0;


        IMU_xyz(IMU1,Gyro_Read_Select);
        //First shift <<2 and then multiply with 35.
        IMU1->xGyro = (IMU1->xGyro-calvalx)<<FIX2_SHIFT;
        IMU1->yGyro = (IMU1->yGyro-calvaly)<<FIX2_SHIFT;
        IMU1->zGyro = (IMU1->zGyro-calvalz)<<FIX2_SHIFT;

        //shift >>4 to get it in mDPS, then multiplying with the time
        xDegrees += (FIX2_MULT(IMU1->xGyro,35)>>FIX2_SHIFT)*t1.mus;
        yDegrees += (FIX2_MULT(IMU1->yGyro,35)>>FIX2_SHIFT)*t1.mus;
        zDegrees += (FIX2_MULT(IMU1->zGyro,35)>>FIX2_SHIFT)*t1.mus;

        //Sifts down to to read be used in the turn check
        IMU1->xGyro = IMU1->xGyro>>FIX2_SHIFT;
        IMU1->yGyro = IMU1->yGyro>>FIX2_SHIFT;
        IMU1->zGyro = IMU1->zGyro>>FIX2_SHIFT;

        /***********************************************************
        "Stopval" skal justeres efter hvilke værdier der giver mening
        *************************************************************/

        if(IMU1->xGyro<Stopval && IMU1->xGyro>-Stopval && IMU1->yGyro<Stopval && IMU1->yGyro>-Stopval && IMU1->zGyro<Stopval && IMU1->zGyro>-Stopval){
            TurnFlag = 0;
        }
    }
    DATA1->XDeg = xDegrees;
    DATA1->YDeg = yDegrees;
    DATA1->ZDeg = zDegrees;

}

//Used for sending all the data to the SD card
void DATA_load_to_SD(struct DATA *DATA1){
    //Tap er 9 og enter er 13
    uart_putc_SD(DATA1->XDeg);
    uart_putc_SD(9);
    uart_putc_SD(DATA1->YDeg);
    uart_putc_SD(9);
    uart_putc_SD(DATA1->ZDeg);
    uart_putc_SD(9);
    uart_putc_SD(DATA1->DistRF);
    uart_putc_SD(13);
}

