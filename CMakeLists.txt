cmake_minimum_required(VERSION 3.14)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(chess main.cpp subject.cpp subject.h observer.cpp observer.h)