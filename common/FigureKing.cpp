//
// Created by Jozef on 4/25/2019.
//

#include "FigureKing.h"
#include "cmath"

FigureKing::FigureKing(bool isWhite)
{
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


bool FigureKing::isWhiteF()
{
    return this->isWhite;
}

Field *FigureKing::getActualField()
{
    return this->actField;
}

void FigureKing::setActualPosition(Field *field)
{
    this->actField = field;
}

void FigureKing::nulActualPosition()
{
    this->actField = nullptr;
}


int FigureKing::move(Field *moveTo)
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

bool FigureKing::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    if(colDiff > 1 || rowDiff > 1)
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
