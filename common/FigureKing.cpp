//
// Created by Jozef on 4/25/2019.
//

#include "FigureKing.h"
#include "FiguresManager.h"
#include "cmath"

FigureKing::FigureKing(bool isWhite)
{
    this->ID = 0;
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
    this->inChess = false;
    //image
    this->chessBy = nullptr;
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


int FigureKing::move(Field *moveTo, FiguresManager *figuresManager)
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

        if(movetoFigure->getID() == 0)
            return false;

        this->isRemovingFigure = true;
    }

    return true;
}



void FigureKing::setFieldsInDanger()
{
    this->fieldsInDanger.clear();
    this->appendFieldsInDanger(Field::Direction::RU);
    this->appendFieldsInDanger(Field::Direction::LU);
    this->appendFieldsInDanger(Field::Direction::RD);
    this->appendFieldsInDanger(Field::Direction::LD);
    this->appendFieldsInDanger(Field::Direction::R);
    this->appendFieldsInDanger(Field::Direction::L);
    this->appendFieldsInDanger(Field::Direction::U);
    this->appendFieldsInDanger(Field::Direction::D);

}

void FigureKing::appendFieldsInDanger(Field::Direction dir)
{
    Field *nextField=this->actField->nextField(dir);
    if (nextField != nullptr)
        this->fieldsInDanger.push_back(nextField);

}

std::vector<Field*> FigureKing::getFieldsInDanger()
{
    return this->fieldsInDanger;
}


bool FigureKing::canMove(std::vector<Field*> fieldsInDangerOut)
{
    Field *nextField;

    nextField = this->actField->nextField(Field::Direction::U);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }


    nextField = this->actField->nextField(Field::Direction::RU);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }

    nextField = this->actField->nextField(Field::Direction::R);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }

    nextField = this->actField->nextField(Field::Direction::RD);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }

    nextField = this->actField->nextField(Field::Direction::D);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }

    nextField = this->actField->nextField(Field::Direction::LD);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }

    nextField = this->actField->nextField(Field::Direction::L);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }
    nextField = this->actField->nextField(Field::Direction::LU);
    if(nextField != nullptr && !(std::find(fieldsInDangerOut.begin(), fieldsInDangerOut.end(), nextField) != fieldsInDangerOut.end()))
    {
        if(nextField->isEmpty())
        {
            return true;
        }
        else
        {
            Figure *tmp = nextField->get();
            if(tmp->isWhiteF() != this->isWhiteF())
                return true;
        }
    }

    return false;
}


bool FigureKing::getInChess()
{
    return this->inChess;
}

void FigureKing::setInChess(bool inChess)
{
    this->inChess = inChess;
}

void FigureKing::setChessBy(Figure *figure)
{
    this->chessBy = figure;
}

Figure *FigureKing::getChessBy ()
{
    return this->chessBy;
}


int FigureKing::getID()
{
    return this->ID;
}

std::vector<Field*> FigureKing::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    std::vector<Field*> fieldsOfDirToField;
    fieldsOfDirToField.push_back(this->actField);

    return fieldsOfDirToField;
}

std::vector<Field*> FigureKing::getFieldsForPossMov()
{
    return this->fieldsInDanger;
}

std::vector<Field*> FigureKing::getFieldsInDangerChesMat()
{
    return this->fieldsInDanger;
}


