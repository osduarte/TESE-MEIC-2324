cmake_minimum_required(VERSION 3.19)
project(MagicW C)

set(CMAKE_C_STANDARD 99)

add_executable(MagicW main.c utils.c utils.h model_functions.c model_functions.h parameters.h file.c file.h)