//
// Created by Jozef on 4/21/2019.
//

#include <cmath>
#include "FigurePawn.h"
//#include "Figure.h"

FigurePawn::FigurePawn(bool isWhite)
{
    this->isWhite = isWhite;
    this->firstMovementDone = false;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


bool FigurePawn::isWhiteF()
{
    return this->isWhite;
}

Field *FigurePawn::getActualField()
{
    return this->actField;
}

void FigurePawn::setActualPosition(Field *field)
{
    this->actField = field;
}

void FigurePawn::nulActualPosition()
{
    this->actField = nullptr;
}


int FigurePawn::move(Field *moveTo)
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
    this->firstMovementDone = true;
    return flag;
}

bool FigurePawn::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    if (colDiff == 0)
    {
        if(!this->firstMovementDone)
        {
            if(rowDiff != 1 && rowDiff != 2)
                return false;
        }
        else
        {
            if(rowDiff != 1)
                return false;
        }


        Field::Direction dir;
        if (this->isWhite)
        {
            if (!(actRow < movetoRow))
                return false;
            dir = Field::Direction::U;
        }
        else
        {
            if (!(actRow > movetoRow))
                return false;
            dir = Field::Direction::D;
        }

        if(!checkDirWithoutRemove(dir, rowDiff))
            return false;
    }
    else if(colDiff==1)
    {
        if(rowDiff!=1)
            return false;

        if (this->isWhite)
        {
            if (!(actRow < movetoRow))
                return false;
        }
        else
        {
            if (!(actRow > movetoRow))
                return false;
        }

        if(moveTo->isEmpty())
            return false;

        Figure *movetoFigure = moveTo->get();
        if(movetoFigure->isWhiteF() == this->isWhiteF())
            return false;

        //TODO - king check
        this->isRemovingFigure = true;
    }
    else
    {
        return false;
    }

    return true;
}

bool FigurePawn::checkDirWithoutRemove(Field::Direction dir, int diff)
{
    Field *nextField = this->actField;
    for (int i = 0; i < diff; i++)
    {
        nextField = nextField->nextField(dir);
        if(!(nextField->isEmpty()))
            return false;
    }
    return true;
}
