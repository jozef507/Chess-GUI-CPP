//
// Created by Jozef on 5/3/2019.
//

#ifndef ICP_NOTATIONMOVEMENT_H
#define ICP_NOTATIONMOVEMENT_H

#include <string>
#include <vector>
class MovementManager;
class FiguresManager;
class Figure;
class Field;
class NotationMovement
{
private:
    bool isLongNotation;

    int startFieldCol;
    int startFieldRow;
    int movementFigureID;
    int goalFieldCol;
    int goalFieldRow;
    int changingFigureID;

    bool isFigureRemoving;
    bool isChess;
    bool isChessMat;

    int getFigureID(std::string s);
    std::string getStrFigureID(int id);
    int getIntFieldColumn(std::string s);
    std::string  getStrFieldColumn(int i);

public:
    NotationMovement();
    ~NotationMovement() = default;

    void setNotationMovementFromUserMov(bool isLongNotation, FiguresManager *figuresManager, MovementManager *movementManager);
    bool setNotationMovementFromString(std::string s);

    bool getIsLongNotation();
    std::string getGeneratedStrOfNotMov(std::vector<Figure*> activeFigures, Figure *movementFigure, Field *startFieldOfMovementFig);
    int getStartFieldCol();
    int getStartFieldRow();
    int getGoalFieldCol();
    int getGoalFieldRow();
    int getMovementFigureID();
    int getChangingFigureID();
    bool getIsFigureRemoving();
    bool getIsChess();
    bool getIsChessMat();
    void completeNotationMovement(MovementManager *movementManager);

};


#endif //ICP_NOTATIONMOVEMENT_H
