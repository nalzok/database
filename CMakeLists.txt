cmake_minimum_required(VERSION 3.10)
project(database C)

set(CMAKE_C_STANDARD 11)

add_executable(database main.c repl.c repl.h compiler.c compiler.h vm.c vm.h)