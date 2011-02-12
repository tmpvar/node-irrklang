# makefile for linux
CPP = g++
OPTS =  -I"../../include" -I"3rdparty" -L"/usr/lib" -L"3rdparty" -DLINUX -lfltklinux -lX11 ../../bin/linux-gcc/libIrrKlang.so -pthread

all:
	$(CPP) main.cpp window.cxx -o player $(OPTS)

clean:
	rm player
