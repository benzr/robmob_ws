#ifndef u8
typedef unsigned char u8;
#endif

int i2c_init(const char* i2c_fname);
void i2c_close(int i2c_fd);
int i2c_write(int i2c_fd,u8 slave_addr, u8 reg, u8 data);
int i2c_write_block (int i2c_fd, u8 slave_addr, u8 reg, u8* reg_data, u8 size);
int i2c_read(int i2c_fd, u8 slave_addr, u8 reg, u8 *result);
int i2c_read_block(int i2c_fd,u8 slave_addr, u8 reg,  u8 *reg_data, u8 size);
int i2c_read_block_zero(int i2c_fd,u8 slave_addr, u8 *reg_data, u8 size);
int i2c_write_block_zero (int i2c_fd, u8 slave_addr, u8* reg_data, u8 size);


