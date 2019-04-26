//
// Created by Jozef on 4/25/2019.
//

#ifndef ICP_FIGUREQUEEN_H
#define ICP_FIGUREQUEEN_H

#include "Figure.h"

class FigureQueen: public Figure
{

private:
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;

    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);
    bool checkDirection(Field::Direction dir, int diff);


public:
    FigureQueen(bool isWhite);
    ~FigureQueen() = default;
    //virtual Figure::~Figure();
    virtual int move(Field *moveTo);
    virtual bool isWhiteF();
    virtual void setActualPosition(Field *field);
    virtual void nulActualPosition();
    virtual Field *getActualField();

};


#endif //ICP_FIGUREQUEEN_H
