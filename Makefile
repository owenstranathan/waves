
all: cmake build Makefile
	cd build && make
	cp build/waves ./
	

cmake: CMakeLists.txt src/CMakeLists.txt
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..

.PHONY: cmake all
