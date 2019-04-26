//
// Created by Jozef on 4/21/2019.
//

#ifndef ICP_FIELD_H
#define ICP_FIELD_H

#include "Figure.h"


#define DIRECTIONCOUNT 8
class Figure;
class Field
{
private:
    int row;
    int col;
    Figure *figure;
    Field **nextFields;

public:
    enum Direction {D, L, LD, LU, R, RD, RU, U, NONE};
    static Direction *myValues()
    {
        static Direction directions[] = {D, L, LD, LU, R, RD, RU, U};
        return  directions;
    }

    Field(int col, int row);
    ~Field();
    int getColPos();
    int getRowPos();
    void addNextField(Direction dirs, Field *field);
    Figure *get();
    bool isEmpty();
    Field *nextField(Direction dirs);
    bool put(Figure *figure);
    bool remove(Figure *figure);
};


#endif //ICP_FIELD_H
