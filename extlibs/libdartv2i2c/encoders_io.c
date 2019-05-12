#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <linux/i2c-dev.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "dartv2i2c.h"
#include "../libsimioi2c/i2c.h"
//#include "../libioi2c/i2c.h"

// rear wheels encoders and  direction
// battery level

int dartv2i2c_get_rear_encoders(int file, int* encLeft, int* encRight) {
  int addr = 0x14;
  int reg = 0x0;
  I2C_output_packet_encoders recv;
  i2c_read_block(file,addr, reg, (u8*)&recv, sizeof(recv));
  *encLeft = recv.left_encoder_rear;
  *encRight = recv.right_encoder_rear;
  return (0);
}

int dartv2i2c_get_battery_level(int file, float* batlvl) {
  int addr = 0x14;
  int reg = 0x06;
  I2C_output_packet_batlvl recv;
  i2c_read_block(file,addr, reg, (u8*)&recv, sizeof(recv));
  *batlvl = 5.0*(float)recv.battery_level/1024.0;
  *batlvl /= 0.23;
  return (0);
}
