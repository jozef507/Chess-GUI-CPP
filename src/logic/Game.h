//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_GAME_H
#define ICP_GAME_H

#include <string>
#include <vector>

class MovementManager;
class Field;
class Game
{
public:
    virtual ~Game()= default;
    virtual Field *getGoalField() = 0;
    virtual void changePlayer() = 0;
    virtual void setCanPlayerPlay(bool canPlayerPlay) = 0;
    virtual void nullMovementManager() = 0;

    virtual bool setPlayerMovement(int col, int row) = 0;
    virtual bool setPlaybackMovement() = 0;
    virtual bool performPlayerMovement() = 0;
    virtual bool performPlaybackMovement() = 0;
    virtual bool setPlaybackUndoMovement() = 0;
    virtual bool performPlaybackUndoMovement() = 0;


    virtual bool isWhiteOnTheMove() = 0;
    //getImageOfMovFigure;
    //getImageOfGoalFieldFigure;
    virtual std::vector<std::string> getGameNotation() = 0;
    virtual int getIndexOfGameNotation() = 0;
    virtual bool isMovementCompletlySet() = 0;
    virtual bool isRemovingFigure() = 0;
    virtual bool getChess() = 0;
    virtual bool getChessMat() = 0;
    virtual bool getIsChangingFigure () = 0;
    virtual bool createNewFigure(/*ImageView image, */int id) = 0;

    virtual void setChangedFigureField() = 0;
    virtual void addPlayerNotationMovement() = 0;
    virtual bool saveNotation() = 0 ;
    virtual int getChangingFigureID() = 0;
    virtual void incrementIndexOfNotationLines() = 0;
    virtual void decrementIndexOfNotationLines() = 0;
    virtual bool isFirstIndexOfNotation() = 0 ;
    virtual bool isLastIndexOfNotation() = 0;
    virtual void completeNotationMovement() = 0;
    virtual MovementManager *getMovementManager() = 0;
    virtual bool isNotationRight() = 0;

    //TODO - delete this function
    virtual Field *getField(int col, int row) = 0;

};


#endif //ICP_GAME_H
