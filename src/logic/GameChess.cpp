//
// Created by Jozef on 4/24/2019.
//

#include "GameChess.h"
#include "MovementManager.h"
#include "FiguresManager.h"
#include "Notation.h"
#include "NotationMovement.h"
#include "FigurePawn.h"
#include "FigureKing.h"
#include "FigureBishop.h"
#include "FigureQueen.h"
#include "FigureKnight.h"
#include "FigureRook.h"
#include "Board.h"




GameChess::GameChess(std::string path/*,ImageView[] whiteFigureImages, ImageView[] blackFigureImages*/)
{
    this->board = new Board(8);
    this->movementManager = new MovementManager();
    this->figuresManager = new FiguresManager();
    this->notation = new Notation(path/*GuiGameFactory.stringFilepathArray[GuiGameFactory.counter++]*/);

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
    this->putKingOnBoard(5, 1, true/*, whiteFigureImages[15]*/);


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
    this->putBishopOnBoard(3, 8, false/*, blackFigureImages[12]*/);
    this->putBishopOnBoard(6, 8, false/*, blackFigureImages[13]*/);
    this->putQueenOnBoard(4, 8, false/*, blackFigureImages[14]*/);
    this->putKingOnBoard(5, 8, false/*, blackFigureImages[15]*/);

    this->figuresManager->setWhiteFieldsInDanger();
    this->figuresManager->setBlackFieldsInDanger();
}

GameChess::~GameChess()
{
    delete this->notation;
    delete this->figuresManager;
    delete this->movementManager;
    delete this->board;
}

void GameChess::putPawnOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigurePawn *pawn = new FigurePawn(isPawnWhite/*, image*/);
        field->put(pawn);
        this->figuresManager->addActiveFigure(pawn);
    }
}

void GameChess::putRookOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureRook *rook = new FigureRook(isPawnWhite/*, image*/);
        field->put(rook);
        this->figuresManager->addActiveFigure(rook);

    }
}

void GameChess::putKnightOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureKnight *knight = new FigureKnight(isPawnWhite/*, image*/);
        field->put(knight);
        this->figuresManager->addActiveFigure(knight);

    }
}

void GameChess::putBishopOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureBishop *bishop = new FigureBishop(isPawnWhite/*, image*/);
        field->put(bishop);
        this->figuresManager->addActiveFigure(bishop);
    }
}

void GameChess::putQueenOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureQueen *queen = new FigureQueen(isPawnWhite/*, image*/);
        field->put(queen);
        this->figuresManager->addActiveFigure(queen);

    }
}


void GameChess::putKingOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureKing *king = new FigureKing(isPawnWhite/*, image*/);
        field->put(king);
        this->figuresManager->addActiveFigure(king);
        this->figuresManager->setKing(king);
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

bool GameChess::setPlayerMovement(int col, int row)
{
    return this->movementManager->setPlayerMovement(col, row, this->board);
}

bool GameChess::setPlaybackMovement()
{
    return this->movementManager->setPlaybackMovement(this->board, this->notation, this->figuresManager);
}

bool GameChess::performPlayerMovement()
{
    return this->movementManager->performMovement(this->figuresManager);
}

bool GameChess::performPlaybackMovement()
{
    bool flag = this->movementManager->performMovement(this->figuresManager);
    if (!flag)
        return false;

    if(this->movementManager->getIsRemovingFigure() != this->notation->getActualNotMov()->getIsFigureRemoving())
        return false;

    if((this->movementManager->getIsChangingFigure()))
    {
        if(this->notation->getActualNotMov()->getChangingFigureID() == -1)
            return false;
    }
    else
    {
        if(this->notation->getActualNotMov()->getChangingFigureID() != -1)
            return false;
    }

    if(this->figuresManager->getChessMat() != this->notation->getActualNotMov()->getIsChessMat())
        if(this->figuresManager->getChess() != this->notation->getActualNotMov()->getIsChess())
            return false;

    return true;
}

bool GameChess::setPlaybackUndoMovement()
{
    return this->movementManager->setPlaybackUndoMovement(this->notation->getPrevNotationMovement(), this->board, this->figuresManager);
}

bool GameChess::performPlaybackUndoMovement()
{
    return this->movementManager->performPlaybackUndoMovement(this->notation->getPrevNotationMovement(), this->figuresManager);
}

bool GameChess::isWhiteOnTheMove()
{
    return this->movementManager->getIsWhiteOnTheMove();
}

/*ImageView getImageOfMovFigure()
{
    return this.movementManager.getMovementFigure().getImage();
}

ImageView getImageOfGoalFieldFigure()
{
    return this.movementManager.getGoalFieldFigure().getImage();
}*/


std::vector<std::string> GameChess::getGameNotation()
{
    return this->notation->getGameNotationLines();
}

int GameChess::getIndexOfGameNotation()
{
    return this->notation->getIndexProcNotMov();
}

bool GameChess::isMovementCompletlySet()
{
    return this->movementManager->getIsMovementCompletlySet();
}

bool GameChess::isRemovingFigure()
{
    return this->movementManager->getIsRemovingFigure();
}

bool GameChess::getChess()
{
    return this->figuresManager->getChess();
}

bool GameChess::getChessMat()
{
    return this->figuresManager->getChessMat();
}

bool GameChess::getIsChangingFigure()
{
    return this->movementManager->getIsChangingFigure();
}

bool GameChess::createNewFigure(/*image,*/ int id)
{
    switch (id)
    {
        case 4:
            setChangedFigureField();
            putRookOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                           this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        case 3:
            setChangedFigureField();
            putKnightOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                             this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        case 2:
            setChangedFigureField();
            putBishopOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                             this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        case 1:
            setChangedFigureField();
            putQueenOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                            this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        default:
            return false;
    }
}

void GameChess::setChangedFigureField()
{
    Field *field = this->movementManager->getGoalField();
    Figure *changedFigure = field->get();
    field->remove(changedFigure);
    this->figuresManager->addChangedFigure(changedFigure);
}

void GameChess::addPlayerNotationMovement()
{
    this->notation->addPlayerNotationMovement(this->figuresManager, this->movementManager);
}

bool GameChess::saveNotation()
{
    return this->notation->saveNotation();
}

int GameChess::getChangingFigureID()
{
    return this->notation->getChangingFigureID();
}

void GameChess::incrementIndexOfNotationLines()
{
    this->notation->incrementIndexOfNotationLines();
}

void GameChess::decrementIndexOfNotationLines()
{
    this->notation->decrementIndexOfNotationLines();
}

bool GameChess::isFirstIndexOfNotation()
{
    return this->notation->isFirstIndex();
}

bool GameChess::isLastIndexOfNotation()
{
    return this->notation->isLastIndex();
}

void GameChess::completeNotationMovement()
{
    this->notation->completeNotationMovement(this->movementManager);
}

MovementManager *GameChess::getMovementManager()
{
    return this->movementManager;
}

bool GameChess::isNotationRight()
{
    return this->notation->getIsRight();
}



//TODO - delete this function
Field *GameChess::getField(int col, int row) { return this->board->getField(col, row);}

bool GameChess::isFieldEmpty(int col, int row)
{
    return board->getField(col, row)->isEmpty();
}

int GameChess::getFigureIDOnField(int col, int row)
{
    return this->board->getField(col, row)->get()->getID();
}

bool GameChess::getIsWhiteFigureOnField(int col, int row)
{
    return this->board->getField(col, row)->get()->isWhiteF();
}

int GameChess::getStartFieldCol()
{
    return this->movementManager->getStartField()->getColPos();
}

int GameChess::getStartFieldRow()
{
    return this->movementManager->getStartField()->getRowPos();
}

int GameChess::getGoalFieldCol()
{
    return this->movementManager->getGoalField()->getColPos();

}

int GameChess::getGoalFieldRow()
{
    return this->movementManager->getGoalField()->getRowPos();

}
