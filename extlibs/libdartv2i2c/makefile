tst: tst.c libdartv2i2c.a
	gcc -o tst tst.c -L../libsimioi2c -lsimioi2c -L. -ldartv2i2c

libdartv2i2c.a: trex_io.o encoders_io.o sonars_io.o
	ar rcs libdartv2i2c.a trex_io.o encoders_io.o sonars_io.o

trex_io.o: trex_io.c dartv2i2c.h
	gcc -c trex_io.c

encoders_io.o: encoders_io.c dartv2i2c.h 
	gcc -c encoders_io.c

sonars_io.o: sonars_io.c dartv2i2c.h
	gcc -c sonars_io.c

