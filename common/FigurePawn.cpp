//
// Created by Jozef on 4/21/2019.
//

#include <cmath>
#include "FigurePawn.h"
#include "FiguresManager.h"
//#include "Figure.h"

FigurePawn::FigurePawn(bool isWhite)
{
    this->ID = 5;
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

int FigurePawn::move(Field *moveTo, FiguresManager *figuresManager)
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
    Figure *movetoFigure = nullptr;
    Field *prevField = this->actField;

    if(this->isRemovingFigure)
    {
        movetoFigure = moveTo->get();
        moveTo->remove(movetoFigure);
        this->isRemovingFigure = false;
        flag = 2;
    }
    this->actField->remove(this);
    moveTo->put(this);

    if(!figuresManager->updateFigures(this->isWhiteF(), this, movetoFigure))
    {
        moveTo->remove(this);
        prevField->put(this);
        if (flag == 2)
        {
            moveTo->put(movetoFigure);
        }
        flag = -1;
    }

    if(isOnTheLastField())
    {
        if (flag==1)
            flag = 3;
        else
            flag = 4;
    }

    this->firstMovementDone = true;
    return flag;
}

bool FigurePawn::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    if(this->isWhiteF() && this->actField->getRowPos() == 2)
        this->firstMovementDone = false;
    else if(!this->isWhiteF() && this->actField->getRowPos() == 7)
        this->firstMovementDone = false;

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

        if(movetoFigure->getID() == 0)
            return false;

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



void FigurePawn::setFieldsInDanger()
{
    this->fieldsInDanger.clear();

    if(this->isWhiteF())
    {
        Field *nextField = this->actField->nextField(Field::Direction::LU);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RU);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
    }
    else
    {
        Field *nextField = this->actField->nextField(Field::Direction::LD);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RD);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
    }
}

std::vector<Field*> FigurePawn::getFieldsInDanger()
{
    return this->fieldsInDanger;
}

int FigurePawn::getID()
{
    return this->ID;
}

std::vector<Field*> FigurePawn::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    std::vector<Field*> fieldsOfDirToField;
    fieldsOfDirToField.push_back(this->actField);

    return fieldsOfDirToField;

}

bool FigurePawn::isOnTheLastField()
{
    if(this->isWhiteF())
    {
        if(this->actField->getRowPos()==8)
            return true;
    }
    else
    {
        if(this->actField->getRowPos()==1)
            return true;
    }
    return false;
}

std::vector<Field*> FigurePawn::getFieldsForPossMov()
{
    std::vector<Field*> tmp;
    if (this->isWhiteF()) {
        if (this->firstMovementDone)
        {
            Field *field = this->actField->nextField(Field::Direction::U);
            if (field != nullptr && field->isEmpty())
                tmp.push_back(field);
        }
        else
        {
            Field *field = this->actField->nextField(Field::Direction::U);
            if (field != nullptr && field->isEmpty())
            {
                tmp.push_back(field);
                field = field->nextField(Field::Direction::U);
                if (field != nullptr && field->isEmpty())
                    tmp.push_back(field);
            }
        }
    }
    else
    {
        if (this->firstMovementDone) {
            Field *field = this->actField->nextField(Field::Direction::D);
            if (field != nullptr && field->isEmpty())
                tmp.push_back(field);
        } else {
            Field *field = this->actField->nextField(Field::Direction::D);
            if (field != nullptr && field->isEmpty()) {
                tmp.push_back(field);
                field = field->nextField(Field::Direction::D);
                if (field != nullptr && field->isEmpty())
                    tmp.push_back(field);
            }
        }
    }

    if(this->isWhiteF())
    {
        Field *nextField = this->actField->nextField(Field::Direction::LU);
        if(nextField!= nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RU);
        if(nextField!=nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
    }
    else
    {
        Field *nextField = this->actField->nextField(Field::Direction::LD);
        if(nextField!=nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RD);
        if(nextField!=nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
    }

    return tmp;
}

std::vector<Field*> FigurePawn::getFieldsInDangerChesMat()
{
    return this->fieldsInDanger;
}


