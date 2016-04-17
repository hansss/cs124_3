# Default optimization level
O ?= 0

all: partition.c
	gcc -g -std=c99 -Wall -o partition partition.c

clean: 
	$(RM) ms
	
