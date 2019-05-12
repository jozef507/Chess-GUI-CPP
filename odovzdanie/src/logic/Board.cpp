/**
 * Trieda obsahuje reprezentáciu šachovnice
 * @author Jozef Ondria
 */

#include "Board.h"
#include "Figure.h"


/**
 * Inicializuje šachovnicu.
 * @param size Počet riadov/stlpcov poličok šachovnice.
 */
Board::Board(int size)
{
    this->board = new Field**[size];
    for (int i = 0; i < size; ++i) {
        this->board[i] = new Field*[size];
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            Field *f= new Field(i+1,j+1);
            board[i][j] = f;
        }
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            Field *tmp;
            Field::Direction *dir = Field::myValues();
            for (int k = 0; k<DIRECTIONCOUNT; k++)
            {
                Field::Direction f = dir[k];
                tmp = chooseNextField(f, i, j, size);
                board[i][j]->addNextField(dir[k], tmp);
            }
        }
    }
}


/**
 * Deštruktor.
 */
Board::~Board()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Field *field=  this->board[i][j];
            /*if (!field->isEmpty())
            {
                Figure *figure = field->get();
                delete figure;
            }*/
            delete field;
        }
    }

    for (int k = 0; k < 8; ++k) {
        delete[] this->board[k];
    }

    delete[] this->board;
}


/**
 * Vracia veľkosť šachovnice.
 * @return Veľkosť šachovnice.
 */
int Board::getSize ()
{

    int rows =  sizeof this->board / sizeof this->board[0];
    int cols = sizeof this->board[0] / sizeof(Field);

    if(rows == cols)
    {
        return rows;
    }
    else
    {
        return 0;
    }
}


/**
 * Vracia odkaz na poličko (Field) na základe jeho pozície.
 * @param col Stlpec pozície políčka.
 * @param row Riadok pozície políčka.
 * @return Odkaz na políčko(Field).
 */
Field *Board::getField(int col, int row)
{
    Field *field = board[col-1][row-1];
    return field;
}


/**
 * Vracia odkaz na susedné políčko políčka určeného jeho pozíciou.
 * @param dirs Smer susedného políčka.
 * @param col Stlpec pozície aktuálneho políčka.
 * @param row Riadok pozície aktuálneho políčka.
 * @param size Veľkosť šachovnice.
 * @return Odkaz na susedné políčko (Field).
 */
Field *Board::chooseNextField(Field::Direction dirs, int col, int row, int size)
{
    int nextCol, nextRow;

    nextCol = getNextCol(dirs);
    nextRow = getNextRow(dirs);
    nextCol = col + nextCol;
    nextRow = row + nextRow;

    Field *tmp;
    if(nextCol >= 0  &&  nextCol < size  &&  nextRow >=0  &&  nextRow < size)
    {
        tmp = this->board[nextCol][nextRow];
    }
    else
    {
        tmp = nullptr;
    }

    return tmp;
}


/**
 * Vráti susedný stlpec na šachovnici.
 * @param dirs Smer na šachovnici.
 * @return Celočíselnu hodnotu o úspechu.
 */
int Board::getNextCol (Field::Direction dirs)
{
    int newCol;
    switch (dirs)
    {
        case Field::Direction::D:
            newCol = 0;
            break;
        case Field::Direction::L:
            newCol = -1;
            break;
        case Field::Direction::U:
            newCol = 0;
            break;
        case Field::Direction::R:
            newCol = 1;
            break;
        case Field::Direction::LD:
            newCol = -1;
            break;
        case Field::Direction::LU:
            newCol = -1;
            break;
        case Field::Direction::RD:
            newCol = 1;
            break;
        case Field::Direction::RU:
            newCol = 1;
            break;
        default:
            newCol = 2;
            break;
    }
    return newCol;
}


/**
 * Vráti susedný riadok na šachovnici.
 * @param dirs Smer na šachovnici.
 * @return Celočíselnu hodnotu o úspechu.
 */
int Board::getNextRow (Field::Direction dirs)
{
    int newRow;
    switch (dirs)
    {
        case Field::Direction::D:
            newRow = -1;
            break;
        case Field::Direction::L:
            newRow = 0;
            break;
        case Field::Direction::U:
            newRow = 1;
            break;
        case Field::Direction::R:
            newRow = 0;
            break;
        case Field::Direction::LD:
            newRow = -1;
            break;
        case Field::Direction::LU:
            newRow = 1;
            break;
        case Field::Direction::RD:
            newRow = -1;
            break;
        case Field::Direction::RU:
            newRow = 1;
            break;
        default:
            newRow = 0;
            break;
    }
    return newRow;
}
