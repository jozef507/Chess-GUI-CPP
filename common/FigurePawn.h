//
// Created by Jozef on 4/21/2019.
//

#ifndef ICP_FIGUREPAWN_H
#define ICP_FIGUREPAWN_H

#include "Figure.h"


class FigurePawn: public Figure {

private:
bool isWhite;
bool isRemovingFigure;
Field *actField;

bool firstMovementDone;
bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);
bool checkDirWithoutRemove(Field::Direction dir, int diff);


public:
FigurePawn(bool isWhite);
~FigurePawn() = default;
//virtual Figure::~Figure();
virtual int move(Field *moveTo);
virtual bool isWhiteF();
virtual void setActualPosition(Field *field);
virtual void nulActualPosition();
virtual Field *getActualField();

};


#endif //ICP_FIGUREPAWN_H
