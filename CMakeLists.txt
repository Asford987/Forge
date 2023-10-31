cmake_minimum_required(VERSION 3.27.7)

project(forge)

add_executable(forge main.cpp)
install(TARGETS forge DESTINATION bin)