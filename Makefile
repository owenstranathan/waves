
all: cmake build Makefile
	make debug

debug:
	CMAKE_ARGS="-DCMAKE_BUILD_TYPE=Debug" make cmake
	make dobuild

release:
	CMAKE_ARGS="-DCMAKE_BUILD_TYPE=Release" make cmake
	make dobuild

dobuild:
	cd build && make
	cp build/waves ./

cmake: CMakeLists.txt src/CMakeLists.txt
	mkdir -p build && cd build && cmake $(CMAKE_ARGS) ..

.PHONY: cmake all
