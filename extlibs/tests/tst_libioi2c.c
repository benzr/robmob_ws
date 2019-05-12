#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c.h"

void delay(float dt) {
  unsigned int idt;
  idt = ( unsigned int) (dt*1000000.0);
  usleep(idt);
}

int main(int argc, char *argv[]) {
  
  // init i2c
  int i2c_fd = -1;  // file descriptor
  const char *i2c_fname = "/dev/i2c-2";  // device name
  i2c_fd = i2c_init(i2c_fname);

  // close i2c (not mandatory)
  i2c_close(i2c_fd);

}
