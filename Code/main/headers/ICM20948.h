#ifndef ICM20948_H
#define ICM20948_H
//Couldn't find a breakout board for the ICM42688-P, will instead use the 20948 to get familiar with SPI.
//The breakoutboard from Adafruit has the IMU axes printed on the board, however, they are wrong. Consult the datasheet for the ICM20948 instead. Yes, same problem as with the MMC5603

#include "headers/Logging.h"
#include "headers/LinAlg.h"
#include "hardware/spi.h"
#include "pico/binary_info.h"
//10 11 12 13 used by receiver.
//18 19 20 21 used by servo
//8 9 used by i2c0
//2 3 4 5 are free to use for spi0
#define ICM20948_MOSI 3
#define ICM20948_MISO 4
#define ICM20948_SCK 2
#define ICM20948_CS 5

void ICM20948_init();

void ICM20948_read_from_register(uint8_t dev_register, uint8_t* tx_buf, uint8_t* rx_buf, uint8_t n_bytes, uint8_t cs_pin);

void ICM20948_write_to_register(uint8_t dev_register, uint8_t* tx_buf, uint8_t* rx_buf, uint8_t n_bytes, uint8_t cs_pin);

void ICM20948_get_imu_data(double acc[3], double gyr[3]);

//Register map

#define ICM20948_WHO_AM_I 0

#define ICM20948_PWR_MGMT_1 0x6

#define ICM20948_ACCEL_XOUT_H 0x2D

#define ICM20948_TEMP_OUT_H 0x39
#define ICM20948_TEMP_OUT_L 0x3A

//Bit maps
#define SET_SPI_READ 0x80
#define SET_SPI_WRITE 0x0

#define ICM20948_SLEEP 6 //Chip seems to have this bit set, need to clear it at startup
#define ICM20948_DEVICE_RESET 7

#endif
