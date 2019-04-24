//
// Created by Jozef on 4/21/2019.
//

#ifndef ICP_BOARD_H
#define ICP_BOARD_H

#include "Figure.h"
#include "Field.h"

class Board
{
private:
    Field ***board;
    Field *chooseNextField(Field::Direction dirs, int col, int row, int size);
    int getNextCol(Field::Direction dirs);
    int getNextRow (Field::Direction dirs);
public:
    Board(int size);
    ~Board();
    int getSize();
    Field *getField(int col, int row);

};


#endif //ICP_BOARD_H
