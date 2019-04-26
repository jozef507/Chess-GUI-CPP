//
// Created by Jozef on 4/25/2019.
//

#ifndef ICP_FIGUREKNIGHT_H
#define ICP_FIGUREKNIGHT_H

#include "Figure.h"

class FigureKnight: public Figure
{
private:
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;

    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);
    bool checkDirection(Field::Direction dir, int diff);


public:
    FigureKnight(bool isWhite);
    ~FigureKnight() = default;
    //virtual Figure::~Figure();
    virtual int move(Field *moveTo);
    virtual bool isWhiteF();
    virtual void setActualPosition(Field *field);
    virtual void nulActualPosition();
    virtual Field *getActualField();

};


#endif //ICP_FIGUREKNIGHT_H
