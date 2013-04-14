TESTS = th_stack.test
OBJDIR = ../obj/
HEADDIR = ../headers/
CFLAGS = -fPIC -Wall -I$(HEADDIR) `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0`

all : $(TESTS)

th_stack.test : th_stack.c
	gcc $(CFLAGS) th_stack.c $(OBJDIR)stack.o -o th_stack.test

.PHONY : src pack doc clean

clean :
	-rm *.test
	find . -name "*~" -exec rm -f {} \;
