//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_MOVEMENTMANAGER_H
#define ICP_MOVEMENTMANAGER_H


class Field;
class Figure;
class FiguresManager;
class Board;
class Notation;
class NotationMovement;

class MovementManager
{
private:
    bool canPlayerPlay;
    bool isWhiteOnTheMove;
    bool isMovementCompletlySet;
    bool isRemovingFigure;
    bool isChangingFigure;
    //private boolean isFigureChoosen;
    Field *startField;
    Figure *movementFigure;
    Field *goalField;
    Figure *goalFieldFigure;
    Figure *changingFigure;

public:
    MovementManager();
    ~MovementManager() = default;
    Field *getStartField();
    Field *getGoalField();
    void changePlayer();
    void setCanPlayerPlay(bool canPlayerPlay);
    void nullMovementManager();
    bool setPlayerMovement(int col, int row, Board *board);
    bool performMovement(FiguresManager *figuresManager);
    bool setPlaybackMovement(Board *board, Notation *notation, FiguresManager *figuresManager);
    bool setPlaybackUndoMovement(NotationMovement *mov, Board *board, FiguresManager *figuresManager);
    bool performPlaybackUndoMovement(NotationMovement *mov, FiguresManager *figuresManager);

    Figure *getChangingFigure();
    Figure *getMovementFigure();
    Figure *getGoalFieldFigure();
    bool getIsWhiteOnTheMove();
    bool getIsMovementCompletlySet();
    bool getIsRemovingFigure();
    bool getIsChangingFigure();
};


#endif //ICP_MOVEMENTMANAGER_H
