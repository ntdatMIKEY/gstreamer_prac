# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

proc = basic

all:
	@echo "Compiling..."
	gcc ${proc}.c -o ${proc} `pkg-config --cflags --libs gstreamer-1.0`

clean:
	@echo "Cleaning up..."
	rm -rf ${proc}
