//
// Created by Jozef on 4/25/2019.
//

#include "FigureBishop.h"
#include <cmath>




FigureBishop::FigureBishop(bool isWhite)
{
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


bool FigureBishop::isWhiteF()
{
    return this->isWhite;
}

Field *FigureBishop::getActualField()
{
    return this->actField;
}

void FigureBishop::setActualPosition(Field *field)
{
    this->actField = field;
}

void FigureBishop::nulActualPosition()
{
    this->actField = nullptr;
}


int FigureBishop::move(Field *moveTo)
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

bool FigureBishop::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    if(colDiff != rowDiff)
    {
        return false;
    }

    Field::Direction dir;
    if(actRow < movetoRow && actCol < movetoCol)
    {
        dir = Field::Direction::RU;
    }
    else if(actRow < movetoRow && actCol > movetoCol)
    {
        dir = Field::Direction::LD;
    }
    else if (actRow > movetoRow && actCol < movetoCol)
    {
        dir = Field::Direction::RD;
    }
    else if (actRow > movetoRow && actCol > movetoCol)
    {
        dir = Field::Direction::LD;
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

bool FigureBishop::checkDirection(Field::Direction dir, int diff)
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