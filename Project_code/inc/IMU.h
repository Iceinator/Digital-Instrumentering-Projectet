
#ifndef _IMU_H_
#define _IMU_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x_conf.h"
#include <stdio.h>

/*************************
    L3G4200D Registers for the Accelerometer and Gyro
*************************/
#define WHO_AM_I 0x0F

//Control Regs
#define CTRL_REG1_G 0x10
#define CTRL_REG2_G 0x11
#define CTRL_REG3_G 0x12
#define CTRL_REG4 0x1E
#define CTRL_REG5_XL 0x1F
#define CTRL_REG6_XL 0x20
#define CTRL_REG7_XL 0x21
#define CTRL_REG8 0x22
#define CTRL_REG9 0x23
#define CTRL_REG10 0x24

//Outputs gyro
#define OUT_X_L_G 0x18
#define OUT_X_H_G 0x19
#define OUT_Y_L_G 0x1A
#define OUT_Y_H_G 0x1B
#define OUT_Z_L_G 0x1C
#define OUT_Z_H_G 0x1D

//Outputs Accel
#define OUT_X_L_XL 0x28
#define OUT_X_H_XL 0x29
#define OUT_Y_L_XL 0x2A
#define OUT_Y_H_XL 0x2B
#define OUT_Z_L_XL 0x2C
#define OUT_Z_H_XL 0x2D

/*************************
    L3G4200D Registers for the  Magnetic sensor
*************************/

//Control Regs
#define CTRL_REG1_M 0x20
#define CTRL_REG2_M 0x21
#define CTRL_REG3_M 0x22
#define CTRL_REG4_M 0x23
#define CTRL_REG5_M 0x24

//Outputs gyro
#define OUT_X_L_M 0x28
#define OUT_X_H_M 0x29
#define OUT_Y_L_M 0x2A
#define OUT_Y_H_M 0x2B
#define OUT_Z_L_M 0x2C
#define OUT_Z_H_M 0x2D

/*************************
    Selector for different Sensors,
*************************/

//Used to read specific sensor data, These can be | to select multi read
#define Gyro_Read_Select 0x01
#define XL_Read_Select 0x02
#define Mag_Read_Select 0x04

//Used for CS
#define CS_AG 0x01
#define CS_M 0x02

#define ESC 0x1B

// Structs
struct IMU {

    //x y z for the gyro rates
    uint16_t xGyro;
    uint16_t yGyro;
    uint16_t zGyro;

    //x y z For the accelerometor
    uint16_t xAccel;
    uint16_t yAccel;
    uint16_t zAccel;

    //x y z for the megnet
    uint16_t xMag;
    uint16_t yMag;
    uint16_t zMag;
};



void IMU_write(uint8_t address,uint8_t data);
uint16_t IMU_read(uint8_t address,uint8_t CS);
void IMU_xyz(struct IMU *IMU1,uint8_t SS);
void IMU_print(struct IMU *IMU1);
void init_spi_IMU();
uint16_t IMU_readInit(uint8_t address,uint8_t CS);
void CS_Start(uint8_t CS);
void CS_End(uint8_t CS);

#endif /* _IMU_H_ */
