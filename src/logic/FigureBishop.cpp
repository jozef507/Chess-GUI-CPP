//
// Created by Jozef on 4/25/2019.
//

#include "FigureBishop.h"
#include "FiguresManager.h"
#include <cmath>


FigureBishop::FigureBishop(bool isWhite)
{
    this->ID = 2;
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
    //image
    //this->fieldsInDanger =
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


int FigureBishop::move(Field *moveTo, FiguresManager *figuresManager)
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

    int diff = (rowDiff == 0 ? colDiff : rowDiff);
    if(!checkDirection(dir, diff))
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

void FigureBishop::setFieldsInDanger()
{
    this->fieldsInDanger.clear();
    this->appendFieldsInDanger(Field::Direction::RU);
    this->appendFieldsInDanger(Field::Direction::LU);
    this->appendFieldsInDanger(Field::Direction::RD);
    this->appendFieldsInDanger(Field::Direction::LD);
}

void FigureBishop::appendFieldsInDanger(Field::Direction dir)
{
    Field *nextField=this->actField->nextField(dir);
    while (nextField != nullptr)
    {
        this->fieldsInDanger.push_back(nextField);
        if (!nextField->isEmpty())
            break;
        nextField = nextField->nextField(dir);
    }
}

std::vector<Field*> FigureBishop::getFieldsInDanger()
{
    return this->fieldsInDanger;
}

int FigureBishop::getID()
{
    return this->ID;
}

std::vector<Field*> FigureBishop::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    int colDiff = field->getColPos() - this->actField->getColPos();
    int rowDiff = field->getRowPos() - this->actField->getRowPos();

    if(std::abs(colDiff) !=std::abs(rowDiff))
        return {};

    Field::Direction dir;
    if (colDiff>0 && rowDiff>0)
        dir = Field::Direction::RU;
    else if (colDiff>0 && rowDiff<0)
        dir = Field::Direction::RD;
    else if (colDiff<0 && rowDiff>0)
        dir = Field::Direction::LU;
    else if (colDiff<0 && rowDiff<0)
        dir = Field::Direction::LD;
    else
        dir = Field::Direction::NONE;

    if(dir == Field::Direction::NONE)
        return {};

    std::vector<Field*> fieldsOfDirToField;
    Field *nextField = this->actField;
    while (nextField!=field)
    {
        fieldsOfDirToField.push_back(nextField);
        nextField = nextField->nextField(dir);
    }

    return fieldsOfDirToField;
}

std::vector<Field*> FigureBishop::getFieldsForPossMov()
{
    return this->fieldsInDanger;
}

std::vector<Field*> FigureBishop::getFieldsInDangerChesMat()
{
    std::vector<Field*> tmp;
    std::vector<Field*> tmp1;

    tmp1 = appendFieldsInDangerChessMat(Field::Direction::RU);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::RD);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::LU);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::LD);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));

    return tmp;
}

std::vector<Field*> FigureBishop::appendFieldsInDangerChessMat(Field::Direction dir)
{
    std::vector<Field*> tmp;
    Field *nextField = this->actField->nextField(dir);
    while (nextField != nullptr)
    {
        tmp.push_back(nextField);
        if (!nextField->isEmpty())
            if(!(nextField->get()->getID() == 0 && nextField->get()->isWhiteF()!=this->isWhiteF()))
                break;
        nextField = nextField->nextField(dir);
    }
    return tmp;
}

