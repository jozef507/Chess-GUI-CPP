//
// Created by Jozef on 4/25/2019.
//

#ifndef ICP_FIGUREKING_H
#define ICP_FIGUREKING_H

#include "Figure.h"

class FigureKing: public Figure
{
private:
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;

    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);


public:
    FigureKing(bool isWhite);
    ~FigureKing() = default;
    //virtual Figure::~Figure();
    virtual int move(Field *moveTo);
    virtual bool isWhiteF();
    virtual void setActualPosition(Field *field);
    virtual void nulActualPosition();
    virtual Field *getActualField();

};


#endif //ICP_FIGUREKING_H
