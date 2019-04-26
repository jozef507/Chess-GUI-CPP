//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_MOVEMENTMANAGER_H
#define ICP_MOVEMENTMANAGER_H

#include "Board.h"

class MovementManager
{
private:
    Board *board;
    bool canPlayerPlay;
    bool isWhiteOnTheMove;
    //private boolean isFigureChoosen;
    Field *startField;
    Figure *movementFigure;
    Field *goalField;
    Figure *goalFieldFigure;
public:
    MovementManager(Board *board);
    ~MovementManager() = default;
    Field *getGoalField();
    void changePlayer();
    void setCanPlayerPlay(bool canPlayerPlay);
    void nullMovementManager();
    bool setMovement(int col, int row);
    int performMovement();
    Figure *getMovementFigure();
    Figure *getGoalFieldFigure();
    bool isWhiteOnTheMoveF();
};


#endif //ICP_MOVEMENTMANAGER_H
