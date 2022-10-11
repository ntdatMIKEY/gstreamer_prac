# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CC=gcc
CFLAGS= -c -Wall
GLIBS= `pkg-config --cflags --libs gstreamer-1.0`



all: prog

prog: main.o basic4.o
	$(CC) main.o basic4.o -o main $(GLIBS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o $(GLIBS)

basic4.o: basic4.c
	$(CC) -o basic4.o $(CFLAGS) basic4.c $(GLIBS)


.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -rf main *.o 
