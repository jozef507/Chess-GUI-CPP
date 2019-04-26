//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_GAME_H
#define ICP_GAME_H

#include "Board.h"

class Field;
class Game
{
public:
    virtual ~Game()= default;
    virtual void nullMovementManager() = 0;
    virtual bool setMovement(int col, int row) = 0;
    virtual int performMovement() = 0;
    virtual void changePlayer() = 0;
    virtual bool isWhiteOnTheMove() = 0;
    virtual void setCanPlayerPlay(bool canPlayerPlay) = 0;
    virtual Field *getGoalField() = 0;

    //TODO - delete this function
    virtual Field *getField(int col, int row) = 0;

    //virtual ImageView getImageOfMovFigure();
    //virtual ImageView getImageOfGoalFieldFigure();


    //virtual List<String> getGameNotation();
};


#endif //ICP_GAME_H
