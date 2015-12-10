cmake_minimum_required(VERSION 3.3)
project(scanner)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -std=c99 -static-libgcc -static-libstdc++")

set(SOURCE_FILES main.c src/scanner.c src/scanner.h)
add_executable(scanner ${SOURCE_FILES})