# Set the CMake minimum version
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(2-ListaSequencial)

# Set the current compiler flags (C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")

# Set the include directory (.h files mostly)
include_directories(src/)

# "Store" all of the .c source files on SOURCES
file(GLOB SOURCES "src/*.c")

# Create the build with the source files
add_executable(build ${SOURCES})
