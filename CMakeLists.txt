cmake_minimum_required(VERSION 3.20)
project(sfs C)

set(CMAKE_C_STANDARD 99)

add_executable(sfs test.c cmd.c utils.c cutils.c gui.c)
