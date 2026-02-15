#include "headers/ICM20948.h"

void ICM20948_init()
{
    //On the breakout board (slave) from Adafruit, the SPI pins are as follows
    //MISO: SDO (Serial Data Out), this connects to MISO on RP2350
    //MOSI: SDA (Serial Data In), this connects to MOSI on RP2350
    //CS  : CS
    //SCLK: SCL


    //Setup spi at 1 MHz
    int ret = spi_init(spi0, 1000*1000); //Max seems to be 37.5 Mhz
    gpio_set_function(ICM20948_MISO, GPIO_FUNC_SPI);  //RX on master is MISO
    gpio_set_function(ICM20948_SCK, GPIO_FUNC_SPI);
    gpio_set_function(ICM20948_MOSI, GPIO_FUNC_SPI);  //TX on master is MOSI

    gpio_init(ICM20948_CS);
    gpio_set_dir(ICM20948_CS, GPIO_OUT);
    gpio_put(ICM20948_CS,1); //CS is set to high, this is the idle state

    //gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI); //gpio 17
    //Make the SPI pins available to picotool
    bi_decl(bi_4pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI));


    //SPI format: 8 bits
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST); //CPOL: Clock Polarity, CPOL = 0 means active high. CPHA: Clock Phase, this indicates where the data is sampled. CPHA = 0 means the data is sampled/latched on the rising edge

    //Read the a register
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];

    //Need to turn off the sleep mode in power management 1. To do this, first read it, OR it after NOT, then write the new value
    ICM20948_read_from_register(ICM20948_PWR_MGMT_1, tx_buf, rx_buf,2,ICM20948_CS);

    tx_buf[1] = (rx_buf[1] & ~ (1 << ICM20948_SLEEP)); //This modifies only the bit we want to change, leaving the rest intact;

    ICM20948_write_to_register(ICM20948_PWR_MGMT_1,tx_buf,rx_buf,2,ICM20948_CS);

    //Now read it back to see if the write worked as intended
    ICM20948_read_from_register(ICM20948_PWR_MGMT_1, tx_buf, rx_buf,2,ICM20948_CS);

    PRINTNUM("updated pwr mgmn 1 value = %d\n", rx_buf[1]);
}

void ICM20948_get_imu_data(double acc[3], double gyr[3])
{
    //12 bytes of relevant data, the buffers need to be 13 bytes long
    uint8_t tx_buf[13];
    uint8_t rx_buf[13];
    uint8_t cs_pin = ICM20948_CS;

    //Get the data. Comes in two's complement
    ICM20948_read_from_register(ICM20948_ACCEL_XOUT_H, tx_buf, rx_buf,sizeof(tx_buf),cs_pin);
    //Assuming default is +-2g, divide by 16384
    uint16_t MSB_x = rx_buf[1];
    uint16_t LSB_x = rx_buf[2];
    uint16_t MSB_y = rx_buf[3];
    uint16_t LSB_y = rx_buf[4];
    uint16_t MSB_z = rx_buf[5];
    uint16_t LSB_z = rx_buf[6];

    int16_t ACC_x = (MSB_x << 8) | LSB_x;
    int16_t ACC_y = (MSB_y << 8) | LSB_y;
    int16_t ACC_z = (MSB_z << 8) | LSB_z;

    //Note that the frame printed on the Adafruit ICM20498 is wrong!
    //COnvert to NED frame
    acc[0] =   ACC_x/16384.0;
    acc[1] = - ACC_y/16384.0;
    acc[2] = - ACC_z/16384.0;

    MSB_x = rx_buf[7];
    LSB_x = rx_buf[8];
    MSB_y = rx_buf[9];
    LSB_y = rx_buf[10];
    MSB_z = rx_buf[11];
    LSB_z = rx_buf[12];

    int16_t GYR_x = (MSB_x << 8) | LSB_x;
    int16_t GYR_y = (MSB_y << 8) | LSB_y;
    int16_t GYR_z = (MSB_z << 8) | LSB_z;

    double d2r = 3.14159265/180;
    //Assuming default is +-250dps, divide by 131
    //Note that the frame printed on the Adafruit ICM20498 is wrong!
    //Convert to NED frame
    gyr[0] =   GYR_x/131.0*d2r;
    gyr[1] = - GYR_y/131.0*d2r;
    gyr[2] = - GYR_z/131.0*d2r;
}

void ICM20948_read_from_register(uint8_t dev_register, uint8_t* tx_buf, uint8_t* rx_buf, uint8_t n_bytes, uint8_t cs_pin)
{
    tx_buf[0] = dev_register | SET_SPI_READ; //Sets the read bit, bit 7, to 1
    gpio_put(cs_pin,0); //Chip select is active low
    int num = spi_write_read_blocking(spi0, tx_buf, rx_buf, n_bytes);
    gpio_put(cs_pin,1);
    //PRINTNUM("Number of bytes written/read = %d\n", num);
}

void ICM20948_write_to_register(uint8_t dev_register, uint8_t* tx_buf, uint8_t* rx_buf, uint8_t n_bytes, uint8_t cs_pin)
{
    tx_buf[0] = dev_register; //Leaves the read bit at 0
    gpio_put(cs_pin,0); //Chip select is active low
    spi_write_read_blocking(spi0, tx_buf, rx_buf, n_bytes);
    gpio_put(cs_pin,1);
}
