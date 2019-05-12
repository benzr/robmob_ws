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
#include "../libioi2c/i2c.h"

// rear wheels encoders and  direction
// battery level

int dartv2i2c_open(const char* devFile) {
  int i2c_fd = -1;
  i2c_fd = i2c_init(devFile);
  return (i2c_fd);
}

int dartv2i2c_close(int file) {
  i2c_close(file);
  return (0);
}
