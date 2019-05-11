//
// Created by Jozef on 4/21/2019.
//

#include "Field.h"
#include "Figure.h"

Field::Field(int col, int row)
{
    this->col = col;
    this->row = row;
    this->figure = nullptr;
    this->nextFields = new Field*[8];
}

Field::~Field()
{
    delete[] this->nextFields;
}

int Field::getColPos()
{
    return this->col;
}

int Field::getRowPos()
{
    return this->row;
}

void Field::addNextField(Direction dirs, Field *field)
{
    this->nextFields[dirs] = field;
}

Field *Field::nextField(Direction dirs)
{
    Field *tmp = nextFields[dirs];
    return tmp;
}


bool Field::isEmpty()
{
    return (this->figure == nullptr);
}

Figure *Field::get()
{
    Figure *figure = this->figure;
    if (this->isEmpty())
    {
        return nullptr;
    }
    else
    {
        return figure;
    }
}

bool Field::put(Figure *figure)
{
    if(this->isEmpty())
    {
        this->figure = figure;
        figure->setActualPosition(this);
        return true;
    }
    else
    {
        return false;
    }
}

bool Field::remove(Figure *figure)
{
    if(this->isEmpty())
    {
        return false;
    }
    else
    {
        if(this->figure == figure)
        {
            this->figure = nullptr;
            figure->nulActualPosition();
            return true;
        }
        else
        {
            return false;
        }
    }
}
