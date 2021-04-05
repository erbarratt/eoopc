cmake_minimum_required(VERSION 3.16)
project(oop C)

set(CMAKE_C_STANDARD 99)

ADD_DEFINITIONS(-Wall -Wextra -Wconversion -pedantic -c -g -O3 -std=gnu99)

add_executable(oop example.c eOOPc.h class.c class.h)
