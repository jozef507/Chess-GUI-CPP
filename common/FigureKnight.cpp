//
// Created by Jozef on 4/25/2019.
//

#include "FigureKnight.h"
#include "cmath"

FigureKnight::FigureKnight(bool isWhite)
{
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


bool FigureKnight::isWhiteF()
{
    return this->isWhite;
}

Field *FigureKnight::getActualField()
{
    return this->actField;
}

void FigureKnight::setActualPosition(Field *field)
{
    this->actField = field;
}

void FigureKnight::nulActualPosition()
{
    this->actField = nullptr;
}


int FigureKnight::move(Field *moveTo)
{
    if(this->actField == nullptr)
        return -1;

    int actCol = this->actField->getColPos();
    int actRow = this->actField->getRowPos();
    int movetoCol = moveTo->getColPos();
    int movetoRow = moveTo->getRowPos();

    if(actCol == movetoCol && actRow == movetoRow)
        return -1;

    if(!isMovementPossible(actCol, actRow, moveTo, movetoCol, movetoRow))
        return -1;

    int flag = 1;
    if(this->isRemovingFigure)
    {
        Figure *movetoFigure = moveTo->get();
        moveTo->remove(movetoFigure);
        this->isRemovingFigure = false;
        flag = 2;
    }

    this->actField->remove(this);
    moveTo->put(this);

    return flag;
}

bool FigureKnight::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    if(!((colDiff == 2 && rowDiff == 1) || (colDiff == 1 && rowDiff == 2)))
        return false;

    if(!moveTo->isEmpty())
    {
        Figure *movetoFigure = moveTo->get();
        if(movetoFigure->isWhiteF() == this->isWhiteF())
            return false;

        /*if(movetoFigure instanceof King)
        return false;*/

        this->isRemovingFigure = true;
    }

    return true;
}

bool FigureKnight::checkDirection(Field::Direction dir, int diff)
{
    Field *nextField=this->actField;
    for (int i = 0; i < diff-1; i++)
    {
        nextField = nextField->nextField(dir);
        if(!(nextField->isEmpty()))
            return false;
    }
    return true;
}