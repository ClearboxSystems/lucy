SHELL := /bin/bash
RM    := rm -fr

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile:
	@ (mkdir build >/dev/null 2>&1; cd build >/dev/null 2>&1 && cmake ..)

install:
	@ $(MAKE) -C build install

clean:
	@- $(RM) ./build


