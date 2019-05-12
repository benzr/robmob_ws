libdartv2i2c.a: trex_io.o encoders_io.o sonars_io.o i2c_dev.o
	ar rcs libdartv2i2c.a trex_io.o encoders_io.o sonars_io.o i2c_dev.o

trex_io.o: trex_io.c dartv2i2c.h
	gcc -c trex_io.c

encoders_io.o: encoders_io.c dartv2i2c.h 
	gcc -c encoders_io.c

sonars_io.o: sonars_io.c dartv2i2c.h
	gcc -c sonars_io.c

i2c_dev.o: i2c_dev.c dartv2i2c.h
	gcc -c i2c_dev.c


