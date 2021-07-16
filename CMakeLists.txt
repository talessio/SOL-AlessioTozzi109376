cmake_minimum_required(VERSION 3.19)
project(SOL_bvernan_structs C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(AlessioTozzi109376
        main.c
        bvernan.c
        bvernan.h)
