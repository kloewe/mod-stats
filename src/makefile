#-----------------------------------------------------------------------------
# File    : makefile
# Contents: build stats module
# Author  : Kristian Loewe
#-----------------------------------------------------------------------------
SHELL   = /bin/bash

CC      = gcc -std=c99 -march=native
CFBASE  = -Wall -Wextra -Wno-unused-parameter -Wconversion -pedantic
CFLAGS  = $(CFBASE) -DNDEBUG -O3

#-----------------------------------------------------------------------------
# Module
#-----------------------------------------------------------------------------
stats.o:  stats.h
stats.o:  stats.c makefile
	$(CC) $(CFLAGS) -c stats.c -o $@

#-----------------------------------------------------------------------------
# Clean up
#-----------------------------------------------------------------------------
clean:
	rm -f *.o *~
