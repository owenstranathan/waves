cmake_minimum_required(VERSION 3.0)
project(waves)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")
find_library (SFML REQUIRED sfml-window)

link_directories(/usr/local/lib/)
if(NOT SFML)
#   message(FATAL_ERROR "sfml library not found")
endif()

add_subdirectory(src)
target_compile_definitions(wavesSources PRIVATE SFML_STATIC)
include_directories(${SFML_INCLUDE_DIR})

add_executable(waves src/main.cpp)

target_compile_definitions(waves PRIVATE SFML_STATIC)
target_link_libraries(waves wavesSources sfml-window sfml-system sfml-graphics)
