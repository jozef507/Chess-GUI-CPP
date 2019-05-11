//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_CHESSGAME_H
#define ICP_CHESSGAME_H

#include "Game.h"
#include <string>
#include <vector>

class MovementManager;
class Notation;
class Field;
class Board;
class FiguresManager;

class GameChess: public Game
{

private:
    Board *board;
    MovementManager *movementManager;
    FiguresManager *figuresManager;
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
    GameChess(std::string path);
    ~GameChess();
    virtual int getFigureIDOnField(int col, int row);
    virtual bool getIsWhiteFigureOnField(int col, int row);
    virtual bool getIsFieldEmpty(int col, int row);
    virtual int getStartFieldCol();
    virtual int getStartFieldRow();
    virtual int getGoalFieldCol();
    virtual int getGoalFieldRow();
    virtual Field *getGoalField();
    virtual void changePlayer();
    virtual void setCanPlayerPlay(bool canPlayerPlay);
    virtual void nullMovementManager();

    virtual bool setPlayerMovement(int col, int row);
    virtual bool setPlaybackMovement();
    virtual bool performPlayerMovement();
    virtual bool performPlaybackMovement();
    virtual bool setPlaybackUndoMovement();
    virtual bool performPlaybackUndoMovement();

    virtual bool isWhiteOnTheMove();
    //getImageOfMovFigure;
    //getImageOfGoalFieldFigure;
    virtual std::vector<std::string> getGameNotation();
    virtual int getIndexOfGameNotation();
    virtual bool isMovementCompletlySet();
    virtual bool isRemovingFigure();
    virtual bool getChess();
    virtual bool getChessMat();
    virtual bool getIsChangingFigure ();
    virtual bool createNewFigure(/*ImageView image, */int id);

    virtual void setChangedFigureField();
    virtual void addPlayerNotationMovement();
    virtual bool saveNotation() ;
    virtual bool saveNotationToAnotherFile(std::string path) ;
    virtual int getChangingFigureID();
    virtual void incrementIndexOfNotationLines();
    virtual void decrementIndexOfNotationLines();
    virtual bool isFirstIndexOfNotation() ;
    virtual bool isLastIndexOfNotation();
    virtual void completeNotationMovement();
    virtual MovementManager *getMovementManager();
    virtual bool isNotationRight();


    //TODO - delete this function
    virtual Field *getField(int col, int row);


};


#endif //ICP_CHESSGAME_H
