cmake_minimum_required(VERSION 3.14)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(chess main.cpp subject.cpp subject.h observer.h Piece.h Board.cpp Board.h strategy.h Human.cpp Human.h Level1.cpp Level1.h Level2.cpp Level2.h Level3.cpp Level3.h strategy.cpp)