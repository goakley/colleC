OBJECTS = bivector.o stack.o queue.o sortedlist.o
HEADDIR = ../headers/
LIBNAME = libcollec
CFLAGS = -fPIC -I../headers -Wall

all : $(OBJECTS)

pack : all
	gcc -fPIC -shared -Wl,-soname,$(LIBNAME).so.0 -o $(LIBNAME).so.0.1 $(OBJECTS) -lc

bivector.o : $(HEADDIR)bivector.h

stack.o : $(HEADDIR)stack.h

queue.o : $(HEADDIR)queue.h

sortedlist.o : $(HEADDIR)sortedlist.h

.PHONY : clean
clean :
	-rm *~
	-rm $(OBJECTS)
	-rm $(LIBNAME).so.0.1
