tst: tst.c libsimioi2c.a
	gcc -o tst tst.c -L. -lsimioi2c

libsimioi2c.a: i2c.o 
	ar rcs libsimioi2c.a i2c.o 

i2c.o: i2c.c i2c.h
	gcc -c i2c.c
