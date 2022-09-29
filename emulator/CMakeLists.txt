cmake_minimum_required(VERSION 3.10)

project(y8664_emulator)

add_library(${PROJECT_NAME} emulator.cpp computer.h computer.cpp)
