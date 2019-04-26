//
// Created by Jozef on 4/24/2019.
//

#include <cmath>
#include "FigureRook.h"



FigureRook::FigureRook(bool isWhite)
{
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


bool FigureRook::isWhiteF()
{
    return this->isWhite;
}

Field *FigureRook::getActualField()
{
    return this->actField;
}

void FigureRook::setActualPosition(Field *field)
{
    this->actField = field;
}

void FigureRook::nulActualPosition()
{
    this->actField = nullptr;
}


int FigureRook::move(Field *moveTo)
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

bool FigureRook::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    Field::Direction dir;
    if(actRow < movetoRow && colDiff == 0)
    {
        dir = Field::Direction::U;
    }
    else if(actRow > movetoRow && colDiff == 0)
    {
        dir = Field::Direction::D;
    }
    else if (actCol < movetoCol && rowDiff == 0)
    {
        dir = Field::Direction::R;
    }
    else if (actCol > movetoCol && rowDiff == 0)
    {
        dir = Field::Direction::L;
    }
    else
    {
        return false;
    }

    int diff = (rowDiff == 0 ? colDiff : rowDiff);
    if(!checkDirection(dir, diff))
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

bool FigureRook::checkDirection(Field::Direction dir, int diff)
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
