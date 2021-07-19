cmake_minimum_required(VERSION 3.19)
project(AlessioTozzi109376 C)

set(CMAKE_C_STANDARD 99
        PROJECT_HEADERS bvernan.h)

include_directories(.)

add_executable(bvernan main.c bvernan.c bvernan.h)
