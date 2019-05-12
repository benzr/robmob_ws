#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "i2c.h"


// Returns a new file descriptor for communicating with the I2C bus:
int i2c_init(const char *i2c_fname) {
  int i2c_fd;
  if ((i2c_fd = open(i2c_fname, O_RDWR)) < 0) {
    char err[200];
    sprintf(err, "open('%s') in i2c_init", i2c_fname);
    perror(err);
    return -1;
  }
    // NOTE we do not call ioctl with I2C_SLAVE here because we always use the I2C_RDWR ioctl operation to do
    // writes, reads, and combined write-reads. I2C_SLAVE would be used to set the I2C slave address to communicate
    // with. With I2C_RDWR operation, you specify the slave address every time. There is no need to use normal write()
    // or read() syscalls with an I2C device which does not support SMBUS protocol. I2C_RDWR is much better especially
    // for reading device registers which requires a write first before reading the response.

  return i2c_fd;
}

void i2c_close(int i2c_fd) {
    close(i2c_fd);
}

// Write one byte to an I2C slave device's register:
int i2c_write(int i2c_fd, u8 slave_addr, u8 reg, u8 data) {
    int retval;
    u8 outbuf[2];

    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    outbuf[0] = reg;
    outbuf[1] = data;

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = 2;
    msgs[0].buf = outbuf;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_write");
        return -1;
    }

    return 0;
}
// Write a data block to an I2C slave device's register:
int i2c_write_block (int i2c_fd, u8 slave_addr, u8 reg, u8* reg_data, u8 size) {
    int retval;
    u8* outbuf;
    outbuf = (u8*) malloc(1+size);
    outbuf[0] = reg;
    for (int i=0; i<size; i++) {
      outbuf[1+i] = reg_data[i];
    }      
    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = size+1;
    msgs[0].buf = outbuf;
    //for (int i=0; i< msgs[0].len; i++) {
    //  printf ("wr %2d %2.2x\n",i,msgs[0].buf[i]);
    //}
    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_write");
        return -1;
    }
    free (outbuf);
    return 0;
}

// Read a byte on the given I2C slave device's register and return the read value in `*result`:
int i2c_read(int i2c_fd, u8 slave_addr, u8 reg, u8 *result) {
    int retval;
    u8 outbuf[1], inbuf[1];
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = outbuf;
    msgs[1].addr = slave_addr;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = 1;
    msgs[1].buf = inbuf;
    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 2;
    outbuf[0] = reg;
    inbuf[0] = 0;

    *result = 0;
    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_read");
        return -1;
    }

    *result = inbuf[0];
    return 0;
}

// Read a date block on the given I2C slave device's register and return the read value in `*result`:
int i2c_read_block(int i2c_fd, u8 slave_addr, u8 reg,  u8 *reg_data, u8 size) {
    int retval;
    u8 outbuf[1], inbuf[1];
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = outbuf;

    msgs[1].addr = slave_addr;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = size;
    msgs[1].buf = reg_data;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 2;

    outbuf[0] = reg;

    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_read");
        return -1;
    }
    return 0;
}

// Read a date block on the given I2C slave device's register and return the read value in `*result`:
int i2c_read_block_zero(int i2c_fd, u8 slave_addr, u8 *reg_data, u8 size) {
    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_addr;
    //msgs[0].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[0].flags = I2C_M_RD;
    msgs[0].len = size;
    msgs[0].buf = reg_data;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_read");
        return -1;
    }
    return 0;
}
// Write a data block to an I2C slave device's register:
int i2c_write_block_zero (int i2c_fd, u8 slave_addr, u8* reg_data, u8 size) {
    int retval;
    u8* outbuf;
    outbuf = (u8*) malloc(0+size);
    outbuf[0] = 0;
    for (int i=0; i<size; i++) {
      outbuf[0+i] = reg_data[i];
    }      
    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_addr;
    msgs[0].flags = I2C_M_NOSTART;
    msgs[0].len = size+0;
    msgs[0].buf = outbuf;
    //for (int i=0; i< msgs[0].len; i++) {
    //  printf ("wr %2d %2.2x\n",i,msgs[0].buf[i]);
    //}
    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_write");
        return -1;
    }
    free (outbuf);
    return 0;
}
