//
// Created by Jozef on 4/24/2019.
//

#include <cmath>
#include "FigureRook.h"
#include "FiguresManager.h"



FigureRook::FigureRook(bool isWhite)
{
    this->ID  = 4;
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


int FigureRook::move(Field *moveTo, FiguresManager *figuresManager)
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

        if(movetoFigure->getID() == 0)
            return false;

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


void FigureRook::setFieldsInDanger()
{
    this->fieldsInDanger.clear();
    this->appendFieldsInDanger(Field::Direction::U);
    this->appendFieldsInDanger(Field::Direction::D);
    this->appendFieldsInDanger(Field::Direction::R);
    this->appendFieldsInDanger(Field::Direction::L);
}

void FigureRook::appendFieldsInDanger(Field::Direction dir)
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

std::vector<Field*> FigureRook::getFieldsInDanger()
{
    return this->fieldsInDanger;
}

int FigureRook::getID()
{
    return this->ID;
}

std::vector<Field*> FigureRook::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    int colDiff = field->getColPos() - this->actField->getColPos();
    int rowDiff = field->getRowPos() - this->actField->getRowPos();


    Field::Direction dir;
    if (colDiff>0 && rowDiff>0)
        dir = Field::Direction::R;
    else if (colDiff>0 && rowDiff<0)
        dir = Field::Direction::L;
    else if (colDiff<0 && rowDiff>0)
        dir = Field::Direction::U;
    else if (colDiff<0 && rowDiff<0)
        dir = Field::Direction::D;
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

std::vector<Field*> FigureRook::getFieldsForPossMov()
{
    return this->fieldsInDanger;
}

std::vector<Field*> FigureRook::getFieldsInDangerChesMat()
{
    std::vector<Field*> tmp;
    std::vector<Field*> tmp1;

    tmp1 = appendFieldsInDangerChessMat(Field::Direction::U);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::D);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::R);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::L);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));

    return tmp;
}

std::vector<Field*> FigureRook::appendFieldsInDangerChessMat(Field::Direction dir)
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
