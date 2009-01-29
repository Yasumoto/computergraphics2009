# Makefile for Computer Graphics
# Interterm 2009
# Final Project
# Jets
# Joe Smith
# 0949140
# 01/26/09

CC=gcc 
CFLAGS=-Wall -lglut
.PHONY: clean

jets: init.o missile.o jet.o
	gcc -o jets -Wall -lglut init.o missile.o jet.o

init.o: init.c JoeSmith.h
	gcc -c init.c

missile.o: missile.c JoeSmith.h
	gcc -c missile.c

jet.o: jet.c JoeSmith.h
	gcc -c jet.c

clean:
	rm -f jets *.o
