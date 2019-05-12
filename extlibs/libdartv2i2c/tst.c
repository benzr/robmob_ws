#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dartv2i2c.h"
#include "../libsimioi2c/i2c.h"
//#include "../libioi2c/i2c.h"

void delay(float dt) {
  unsigned int idt;
  idt = ( unsigned int) (dt*1000000.0);
  usleep(idt);
}

int main(int argc, char *argv[]) {
  int leftEnc, rightEnc;
  int status;
  float batlvl;
  float distFront, distBack, distLeft, distRight;
  
  // init i2c
  int i2c_fd = -1;  // file descriptor
  const char *i2c_fname = "/dev/i2c-2";  // device name
  i2c_fd = i2c_init(i2c_fname);

  int mode = 1;
  status =  dartv2i2c_sonars_set_mode_cardinal(i2c_fd, mode, mode, mode, mode);
  delay (0.25);

  float dmax = 2.0;
  status =  dartv2i2c_sonars_set_dmax_cardinal(i2c_fd, dmax, dmax, dmax, dmax, dmax);
  delay (0.25);

  status =  dartv2i2c_sonars_get_cardinal (i2c_fd, &distFront, &distBack, &distLeft, &distRight);
  printf ("dist f=%.2f b=%.2f, l=%.2f, r=%.2f\n",distFront, distBack, distLeft, distRight);
  delay (0.25);
  
  status = dartv2i2c_trex_get_front_encoders (i2c_fd,&leftEnc, &rightEnc);
  printf ("front encoders l=%5d, r=%5d\n",leftEnc,rightEnc);
  delay (0.25);

  status = dartv2i2c_get_rear_encoders (i2c_fd,&leftEnc, &rightEnc);
  printf ("rear encoders l=%5d, r=%5d\n",leftEnc,rightEnc);
  delay (0.25);

  status = dartv2i2c_trex_cmd_motors (i2c_fd,80,80);
  delay (0.25);
  status = dartv2i2c_trex_cmd_motors (i2c_fd,0,0);
  delay (0.25);

  status = dartv2i2c_trex_get_front_encoders (i2c_fd,&leftEnc, &rightEnc);
  printf ("encoders l=%5d, r=%5d\n",leftEnc,rightEnc);
  delay (0.25);

  status = dartv2i2c_get_rear_encoders (i2c_fd,&leftEnc, &rightEnc);
  printf ("rear encoders l=%5d, r=%5d\n",leftEnc,rightEnc);
  delay (0.25);

  status = dartv2i2c_get_battery_level (i2c_fd,&batlvl);
  printf ("Battery level is %.2f V\n",batlvl);

  // close i2c (not mandatory)
  i2c_close(i2c_fd);

}
