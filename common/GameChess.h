//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_CHESSGAME_H
#define ICP_CHESSGAME_H

#include "Board.h"
#include "Game.h"
#include "Notation.h"
#include "MovementManager.h"

#include "FigurePawn.h"
#include "FigureRook.h"
#include "FigureBishop.h"
#include "FigureQueen.h"
#include "FigureKnight.h"
#include "FigureKing.h"

class Field;

class GameChess: public Game
{

private:
    Board *board;
    MovementManager *movementManager;
    Notation *notation;

    //List<Figure> activeWhiteFigures;
    //List<Figure> activeBlackFigures;

    void putPawnOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);
    void putRookOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);
    void putKnightOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);
    void putBishopOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);
    void putQueenOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);
    void putKingOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);


public:
    GameChess();
    ~GameChess();
    virtual void nullMovementManager();
    virtual bool setMovement(int col, int row);
    virtual int performMovement();
    virtual void changePlayer();
    virtual bool isWhiteOnTheMove();
    virtual void setCanPlayerPlay(bool canPlayerPlay);
    virtual Field *getGoalField();

    //TODO - delete this function
    virtual Field *getField(int col, int row);

    //virtual ImageView getImageOfMovFigure();
    //virtual ImageView getImageOfGoalFieldFigure();

    //virtual List<String> getGameNotation();


};


#endif //ICP_CHESSGAME_H
