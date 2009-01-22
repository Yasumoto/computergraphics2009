# Makefile for Computer Graphics
# Interterm 2009
# Assignment 5
# Joe Smith
# 0949140
# 01/21/09

CC=gcc 
CFLAGS=-Wall -lglut
.PHONY: clean

JoeSmith5: JoeSmith5.c

clean:
	rm -f JoeSmith5
