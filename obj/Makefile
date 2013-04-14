LIBNAME = libcollec

.PHONY : pack clean

pack :
	gcc -Wall -fPIC -shared -Wl,-soname,$(LIBNAME).so.0 -o $(LIBNAME).so.0.1 *.o -lc

clean :
	-rm *.o*
	-rm *.so*
