//
// Created by Jozef on 4/25/2019.
//

#include "FigureQueen.h"
#include "cmath"

FigureQueen::FigureQueen(bool isWhite)
{
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


bool FigureQueen::isWhiteF()
{
    return this->isWhite;
}

Field *FigureQueen::getActualField()
{
    return this->actField;
}

void FigureQueen::setActualPosition(Field *field)
{
    this->actField = field;
}

void FigureQueen::nulActualPosition()
{
    this->actField = nullptr;
}


int FigureQueen::move(Field *moveTo)
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

bool FigureQueen::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    Field::Direction dir;
    if(colDiff != 0 && colDiff == rowDiff)
    {
        if(actRow < movetoRow && actCol < movetoCol)
        {
            dir = Field::Direction::RU;
        }
        else if(actRow < movetoRow && actCol > movetoCol)
        {
            dir = Field::Direction::LU;
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
    }
    else if((colDiff == 0 && rowDiff !=0) || (colDiff != 0 && rowDiff ==0))
    {
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

bool FigureQueen::checkDirection(Field::Direction dir, int diff)
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