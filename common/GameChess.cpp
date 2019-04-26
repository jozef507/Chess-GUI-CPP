//
// Created by Jozef on 4/24/2019.
//

#include "GameChess.h"


GameChess::GameChess(/*ImageView[] whiteFigureImages, ImageView[] blackFigureImages*/)
{
    this->board = new Board(8);
    this->movementManager = new MovementManager(this->board);
    this->notation = new Notation(/*GuiGameFactory.stringFilepathArray[GuiGameFactory.counter++]*/);

    //this.activeWhiteFigures = new ArrayList<Figure>();
    //this.activeBlackFigures = new ArrayList<Figure>();

    this->putPawnOnBoard(1, 2, true/*, whiteFigureImages[0]*/);
    this->putPawnOnBoard(2, 2, true/*, whiteFigureImages[1]*/);
    this->putPawnOnBoard(3, 2, true/*, whiteFigureImages[2]*/);
    this->putPawnOnBoard(4, 2, true/*, whiteFigureImages[3]*/);
    this->putPawnOnBoard(5, 2, true/*, whiteFigureImages[4]*/);
    this->putPawnOnBoard(6, 2, true/*, whiteFigureImages[5]*/);
    this->putPawnOnBoard(7, 2, true/*, whiteFigureImages[6]*/);
    this->putPawnOnBoard(8, 2, true/*, whiteFigureImages[7]*/);

    this->putRookOnBoard(1, 1, true/*, whiteFigureImages[8]*/);
    this->putRookOnBoard(8, 1, true/*, whiteFigureImages[9]*/);

    this->putKnightOnBoard(2, 1, true/*, whiteFigureImages[10]*/);
    this->putKnightOnBoard(7, 1, true/*, whiteFigureImages[11]*/);

    this->putBishopOnBoard(3, 1, true/*, whiteFigureImages[12]*/);
    this->putBishopOnBoard(6, 1, true/*, whiteFigureImages[13]*/);

    this->putQueenOnBoard(4, 1, true/*, whiteFigureImages[14]*/);

    this->putBishopOnBoard(5, 1, true/*, whiteFigureImages[15]*/);


    this->putPawnOnBoard(1, 7, false/*, blackFigureImages[0]*/);
    this->putPawnOnBoard(2, 7, false/*, blackFigureImages[1]*/);
    this->putPawnOnBoard(3, 7, false/*, blackFigureImages[2]*/);
    this->putPawnOnBoard(4, 7, false/*, blackFigureImages[3]*/);
    this->putPawnOnBoard(5, 7, false/*, blackFigureImages[4]*/);
    this->putPawnOnBoard(6, 7, false/*, blackFigureImages[5]*/);
    this->putPawnOnBoard(7, 7, false/*, blackFigureImages[6]*/);
    this->putPawnOnBoard(8, 7, false/*, blackFigureImages[7]*/);

    this->putRookOnBoard(1, 8, false/*, blackFigureImages[8]*/);
    this->putRookOnBoard(8, 8, false/*, blackFigureImages[9]*/);

    this->putKnightOnBoard(2, 8, false/*, blackFigureImages[10]*/);
    this->putKnightOnBoard(7, 8, false/*, blackFigureImages[11]*/);

    this->putRookOnBoard(3, 8, false/*, blackFigureImages[12]*/);
    this->putRookOnBoard(6, 8, false/*, blackFigureImages[13]*/);

    this->putQueenOnBoard(4, 8, false/*, blackFigureImages[14]*/);

    this->putKingOnBoard(5, 8, false/*, blackFigureImages[15]*/);
}

GameChess::~GameChess()
{
    delete this->movementManager;
    delete this->notation;
    delete this->board;
}

void GameChess::putPawnOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigurePawn *pawn = new FigurePawn(isPawnWhite/*, image*/);
        field->put(pawn);
    }
}

void GameChess::putRookOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureRook *rook = new FigureRook(isPawnWhite/*, image*/);
        field->put(rook);
    }
}

void GameChess::putKnightOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureKnight *knight = new FigureKnight(isPawnWhite/*, image*/);
        field->put(knight);
    }
}

void GameChess::putBishopOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureBishop *bishop = new FigureBishop(isPawnWhite/*, image*/);
        field->put(bishop);
    }
}

void GameChess::putQueenOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureQueen *queen = new FigureQueen(isPawnWhite/*, image*/);
        field->put(queen);
    }
}


void GameChess::putKingOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureKing *king = new FigureKing(isPawnWhite/*, image*/);
        field->put(king);
    }
}

Field *GameChess::getGoalField() {
    return this->movementManager->getGoalField();
}

void GameChess::changePlayer() { this->movementManager->changePlayer(); }

void GameChess::setCanPlayerPlay(bool canPlayerPlay) {
    this->movementManager->setCanPlayerPlay(canPlayerPlay);
}

void GameChess::nullMovementManager() { this->movementManager->nullMovementManager(); }

bool GameChess::setMovement(int col, int row) { return this->movementManager->setMovement(col, row); }

int GameChess::performMovement() { return this->movementManager->performMovement();}

bool GameChess::isWhiteOnTheMove() {
    return this->movementManager->isWhiteOnTheMoveF();
}

/*ImageView getImageOfMovFigure()
{
    return this.movementManager.getMovementFigure().getImage();
}

ImageView getImageOfGoalFieldFigure() {
    return this.movementManager.getGoalFieldFigure().getImage();
}*/



/*List<String> getGameNotation()
{
    return this.notation.getGameNotationLines();
}*/

//TODO - delete this function
Field *GameChess::getField(int col, int row) { return this->board->getField(col, row);}