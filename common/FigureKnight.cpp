//
// Created by Jozef on 4/25/2019.
//

#include "FigureKnight.h"
#include "FiguresManager.h"
#include "Field.h"
#include "cmath"

FigureKnight::FigureKnight(bool isWhite)
{
    this->ID = 3;
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


int FigureKnight::move(Field *moveTo, FiguresManager *figuresManager)
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

        if(movetoFigure->getID() == 0)
            return false;

        this->isRemovingFigure = true;
    }

    return true;
}


void FigureKnight::setFieldsInDanger()
{
    this->fieldsInDanger.clear();

    Field *tmpField, *nextField;

    nextField = this->actField->nextField(Field::Direction::U);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::U);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::L);
            nextField = nextField->nextField(Field::Direction::R);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }

    nextField = this->actField->nextField(Field::Direction::L);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::L);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::U);
            nextField = nextField->nextField(Field::Direction::D);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }
    nextField = this->actField->nextField(Field::Direction::D);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::D);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::L);
            nextField = nextField->nextField(Field::Direction::R);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }
    nextField = this->actField->nextField(Field::Direction::R);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::R);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::U);
            nextField = nextField->nextField(Field::Direction::D);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }
}

std::vector<Field*> FigureKnight::getFieldsInDanger()
{
    return this->fieldsInDanger;
}

int FigureKnight::getID()
{
    return this->ID;
}

std::vector<Field*> FigureKnight::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    std::vector<Field*> fieldsOfDirToField;
    fieldsOfDirToField.push_back(this->actField);

    return fieldsOfDirToField;
}

std::vector<Field*> FigureKnight::getFieldsForPossMov()
{
    return this->fieldsInDanger;
}

std::vector<Field*> FigureKnight::getFieldsInDangerChesMat()
{
    return this->fieldsInDanger;
}
