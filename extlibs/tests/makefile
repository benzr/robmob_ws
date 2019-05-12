all: tst_libdartv2i2c tstsim_libdartv2i2c tst_libioi2c tstsim_libioi2c
	echo "build all tests ..."

tstsim_libdartv2i2c: tst_libdartv2i2c.c ../libdartv2i2c/libdartv2i2c.a ../libsimioi2c/libsimioi2c.a
	gcc -o tstsim_libdartv2i2c tst_libdartv2i2c.c -L../libsimioi2c -L../libdartv2i2c -ldartv2i2c -lsimioi2c

tst_libdartv2i2c: tst_libdartv2i2c.c ../libdartv2i2c/libdartv2i2c.a ../libioi2c/libioi2c.a
	gcc -o tst_libdartv2i2c tst_libdartv2i2c.c -L../libioi2c -L../libdartv2i2c -ldartv2i2c -lioi2c

tstsim_libioi2c: tst_libioi2c.c ../libsimioi2c/libsimioi2c.a
	gcc -o tstsim_libioi2c tst_libioi2c.c -L../libsimioi2c -lsimioi2c

tst_libioi2c: tst_libioi2c.c ../libioi2c/libioi2c.a
	gcc -o tst_libioi2c tst_libioi2c.c -L../libioi2c -lioi2c

