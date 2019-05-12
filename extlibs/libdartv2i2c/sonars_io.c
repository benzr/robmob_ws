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

// setup cardinal sonars : dmax and mode
// get distance from cardinal sonars

// setup diagonal sonars
// get distance from diagonal sonars

// todo use sonar patterns e.g. front and left
// full 6 sonars


int dartv2i2c_sonars_get_cardinal (int file, float *dist_front, float *dist_back, float *dist_left, float *dist_right) {
  int addr = 0x21;
  int reg = 0x00;
  I2C_output_packet_sonars_dist recv;
  i2c_read_block (file,addr, reg, (u8*)&recv, sizeof(recv));
  *dist_front = (float)recv.dist_front/100.0;
  *dist_back = (float)recv.dist_back/100.0;
  *dist_left = (float)recv.dist_left/100.0;
  *dist_right = (float)recv.dist_right/100.0;
}

int dartv2i2c_sonars_set_mode_cardinal (int file, int mode_front, int mode_back, int mode_left, int mode_right) {
  int addr = 0x21;
  int reg = 0x0b0;
  I2C_input_packet_sonars_setup_mode snd;
  snd.mode_front = mode_front;
  snd.mode_back = mode_back;
  snd.mode_left = mode_left;
  snd.mode_right = mode_right;
  i2c_write_block (file,addr, reg,(u8*)&snd, sizeof(snd));
}

int dartv2i2c_sonars_set_dmax_cardinal (int file, float dmax_front, float dmax_back, float dmax_left, float dmax_right, float dmax) {
  int addr = 0x21;
  int reg = 0x0b0;
  I2C_input_packet_sonars_setup_dmax snd;
  snd.dmax_front = (int)(dmax_front*100.0);
  snd.dmax_back = (int)(dmax_back*100.0);
  snd.dmax_left = (int)(dmax_left*100.0);
  snd.dmax_right = (int)(dmax_right*100.0);
  snd.dmax = (int)(dmax*100.0);
  i2c_write_block (file,addr, reg,(u8*)&snd, sizeof(snd));
}

int dartv2i2c_sonars_get_diagonal (int file, float *dist_left, float *dist_right) {
}

int dartv2i2c_sonars_setup_diagonal (int file) {
}
