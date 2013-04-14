LIBNAME = libcollec
CFLAGS = -fPIC -I./headers/ -Wall

.PHONY : src pack doc clean

src :
	cd src; make all
	mv src/*.o obj/

pack : src
	cd obj; make pack
	mv obj/*.so* ./

doc : ./doc/Doxyfile
	doxygen ./doc/Doxyfile

clean :
	cd src; make clean
	cd obj; make clean
	cd tests; make clean
	-rm *.so*
	find . -name "*~" -exec rm -f {} \;
