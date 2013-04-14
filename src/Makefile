OBJECTS = bivector.o stack.o queue.o sortedlist.o
HEADDIR = ../headers/
CFLAGS = -fPIC -I../headers -Wall

all : $(OBJECTS)

bivector.o : $(HEADDIR)bivector.h

stack.o : $(HEADDIR)stack.h

queue.o : $(HEADDIR)queue.h

sortedlist.o : $(HEADDIR)sortedlist.h

.PHONY : clean
clean :
	-rm *~
	-rm $(OBJECTS)
