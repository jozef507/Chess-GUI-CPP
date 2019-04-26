//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_FIGUREROOK_H
#define ICP_FIGUREROOK_H

#include "Figure.h"

class FigureRook: public Figure {

private:
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;

    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);
    bool checkDirection(Field::Direction dir, int diff);


public:
    FigureRook(bool isWhite);
    ~FigureRook() = default;
    //virtual Figure::~Figure();
    virtual int move(Field *moveTo);
    virtual bool isWhiteF();
    virtual void setActualPosition(Field *field);
    virtual void nulActualPosition();
    virtual Field *getActualField();
};


#endif //ICP_FIGUREROOK_H
