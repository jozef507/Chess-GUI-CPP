cmake_minimum_required(VERSION 3.10)
project(ICP)

set(CMAKE_CXX_STANDARD 17)

add_executable(ICP main.cpp Figure.h FigurePawn.cpp FigurePawn.h Field.cpp Field.h Board.cpp Board.h)