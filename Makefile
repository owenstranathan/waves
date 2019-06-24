
all: cmake build Makefile
	cd build && make
	cp build/waves ./
	

cmake: CMakeLists.txt src/CMakeLists.txt
	mkdir -p build && cd build && cmake ..

.PHONY: cmake all
