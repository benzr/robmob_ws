tst: tst.c libioi2c.a
	gcc -o tst tst.c -L. -lioi2c

libioi2c.a: i2c.o 
	ar rcs libioi2c.a i2c.o 

i2c.o: i2c.c i2c.h
	gcc -c i2c.c
