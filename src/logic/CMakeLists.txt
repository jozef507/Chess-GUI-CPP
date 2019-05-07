cmake_minimum_required(VERSION 3.10)
project(ICP)

set(CMAKE_CXX_STANDARD 17)

add_executable(ICP main.cpp Figure.h FigurePawn.cpp FigurePawn.h Field.cpp Field.h Board.cpp Board.h Game.h GameChess.cpp GameChess.h Notation.cpp Notation.h MovementManager.cpp MovementManager.h FigureRook.cpp FigureRook.h FigureBishop.cpp FigureBishop.h FigureQueen.cpp FigureQueen.h FigureKnight.cpp FigureKnight.h FigureKing.cpp FigureKing.h FiguresManager.cpp FiguresManager.h NotationMovement.cpp NotationMovement.h)