// I2C_input_packet is nothing more than a pack of int we shouldn't have alignment issues with sizeof
// try to make this as portable as possible without messing up with struct alignments
#include <stdint.h>

#ifndef __I2C_STRUCT_TREX__
#define __I2C_STRUCT_TREX__

typedef struct I2C_input_packet_trex
{
  int16_t left_motor_speed;
  int16_t right_motor_speed;
  int8_t use_pid;
  uint8_t crc;
} I2C_input_packet_trex;

typedef struct I2C_output_packet_trex
{
  uint16_t left_encoder_front;
  uint16_t right_encoder_front;
  uint8_t __dont_use_this_padding_byte;
  uint8_t crc;
} I2C_output_packet_trex;

typedef struct I2C_output_packet_encoders
{
  uint16_t left_encoder_rear;
  uint16_t right_encoder_rear;
} I2C_output_packet_encoders;

typedef struct I2C_output_packet_batlvl
{
  uint16_t battery_level;
} I2C_output_packet_batlvl;

typedef struct I2C_input_packet_sonars_setup_dmax
{
    int16_t dmax_front;
    int16_t dmax_back;
    int16_t dmax_left;
    int16_t dmax_right;
    int16_t dmax;
} I2C_input_packet_sonars_setup_dmax;

typedef struct I2C_input_packet_sonars_setup_mode
{
    uint8_t mode_front;
    uint8_t mode_back;
    uint8_t mode_left;
    uint8_t mode_right;
} I2C_input_packet_sonars_setup_mode;

typedef struct I2C_output_packet_sonars_state
{
    uint8_t state_front;
    uint8_t state_back;
    uint8_t state_left;
    uint8_t state_right;
} I2C_output_packet_sonars_state;

typedef struct I2C_output_packet_sonars_version
{
  uint8_t version;
} I2C_output_packet_sonars_version;

typedef struct I2C_output_packet_sonars_dist
{
    int16_t dist_front;
    int16_t dist_back;
    int16_t dist_left;
    int16_t dist_right;
    int8_t change;
} I2C_output_packet_sonars_dist;

#endif

int dartv2i2c_trex_get_front_encoders (int fd, int *enc_l, int *enc_r);
int dartv2i2c_trex_cmd_motors (int fd, int mot_l, int mot_r);

#ifndef __CRC__
#define __CRC__
uint8_t crc8(unsigned char* data, int len, uint8_t crc);
#endif

int dartv2i2c_get_rear_encoders (int fd, int *enc_l, int *enc_r);
int dartv2i2c_get_battery_level (int fd, float *lvl);

int dartv2i2c_sonars_get_cardinal (int fd, float *dist_front, float *dist_back, float *dist_left, float *dist_right);
int dartv2i2c_sonars_set_mode_cardinal (int fd, int mode_front, int mode_back, int mode_left, int mode_right);
int dartv2i2c_sonars_set_dmax_cardinal (int fd, float dmax_front, float dmax_back, float dmax_left, float dmax_right, float dmax);
int dartv2i2c_sonars_get_diagonal (int fd, float *dist_left, float *dist_right);
int dartv2i2c_sonars_setup_diagonal (int fd);
