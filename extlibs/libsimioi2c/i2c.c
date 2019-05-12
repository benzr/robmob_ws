#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <sys/ioctl.h>
#//include <linux/i2c-dev.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "i2c.h"


// Returns a new file descriptor for communicating with the I2C bus:
int i2c_init(const char *i2c_fname) {
  int i2c_fd;
  return i2c_fd;
}

void i2c_close(int i2c_fd) {
    close(i2c_fd);
}

// Write one byte to an I2C slave device's register:
int i2c_write(int i2c_fd, u8 slave_addr, u8 reg, u8 data) {
    return 0;
}

// Write a data block to an I2C slave device's register:
int i2c_write_block (int i2c_fd, u8 slave_addr, u8 reg, u8* reg_data, u8 size) {
    return 0;
}

// Read a byte on the given I2C slave device's register and return the read value in `*result`:
int i2c_read(int i2c_fd, u8 slave_addr, u8 reg, u8 *result) {
    return 0;
}

// Read a date block on the given I2C slave device's register and return the read value in `*result`:
int i2c_read_block(int i2c_fd, u8 slave_addr, u8 reg,  u8 *reg_data, u8 size) {
    return 0;
}

// Read a date block on the given I2C slave device's register and return the read value in `*result`:
int i2c_read_block_zero(int i2c_fd, u8 slave_addr, u8 *reg_data, u8 size) {
    return 0;
}

// Write a data block to an I2C slave device's register:
int i2c_write_block_zero (int i2c_fd, u8 slave_addr, u8* reg_data, u8 size) {
    return 0;
}

