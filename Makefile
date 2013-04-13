.PHONY : src doc clean

src :
	cd src; make

pack :
	cd src; make pack
	mv src/*.so* ./

doc : ./doc/Doxyfile
	doxygen ./doc/Doxyfile

clean :
	cd src; make clean
	find . -name "*~" -exec rm -f {} \;
