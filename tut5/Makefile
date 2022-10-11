# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CC=gcc
GLIBS= `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0`
proc = main

all:
	@echo "Compiling..."
	$(CC) ${proc}.c -o ${proc} $(GLIBS)

clean:
	@echo "Cleaning up..."
	rm -rf ${proc}
