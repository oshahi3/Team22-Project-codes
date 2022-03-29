#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>

#define I2C_BUS "/dev/i2c-0"

int initBus(void)
{
    int i2cBus = open(I2C_BUS, O_RDWR);
    if (i2cBus < 0)
    {
        fprintf(stderr, "Error oppening i2c bus : %s\n", I2C_BUS);
        exit(EXIT_FAILURE);
    }
    return i2cBus;
}

void setSlave(int i2cBus, __u8 slaveAddress)
{
    //Set the slave address to communicate with
    if(ioctl(i2cBus, I2C_SLAVE, slaveAddress) < 0)
    {
        fprintf(stderr, "Slave unreachable : %x\n", slaveAddress);
        exit(EXIT_FAILURE);
    }
}

uint8_t readByte(int i2cBus, __u8 slaveAddress, __u8 regAddress)
{
    setSlave(i2cBus, slaveAddress);
    int value = i2c_smbus_read_byte_data(i2cBus, regAddress);
    if(value < 0)
    {
        fprintf(stderr, "Error reading register %x\n", regAddress);
        exit(EXIT_FAILURE);
    }
    return value;
}

void writeByte(int i2cBus, __u8 slaveAddress, __u8 regAddress, __u8 byte)
{
    setSlave(i2cBus, slaveAddress);

    int value = i2c_smbus_write_byte_data(i2cBus, regAddress, byte);
    if(value < 0)
    {
        fprintf(stderr, "Error writing register %x\n", regAddress);
        exit(EXIT_FAILURE);
    }
}