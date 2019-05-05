//
// Created by Jozef on 4/25/2019.
//

#ifndef ICP_FIGUREKING_H
#define ICP_FIGUREKING_H

#include "Figure.h"
#include "Field.h"

class FigureKing: public Figure {
private:
    int ID;
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;
    //image
    std::vector<Field*> fieldsInDanger;
    bool inChess;
    Figure *chessBy;

    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);
    void appendFieldsInDanger(Field::Direction dir);


public:
    FigureKing(bool isWhite);
    ~FigureKing() = default;
    virtual int move(Field *moveTo, FiguresManager *figuresManager);
    virtual bool isWhiteF();
    virtual void setActualPosition(Field *field);
    virtual void nulActualPosition();
    virtual Field *getActualField();

    virtual void setFieldsInDanger();
    virtual std::vector<Field*> getFieldsInDanger();
    virtual std::vector<Field*> getFieldsForPossMov();
    virtual std::vector<Field*> getFieldsInDangerChesMat();
    virtual std::vector<Field*> getFieldsOfDirectionToField(Field *field);
    virtual int getID();

    virtual bool canMove(std::vector<Field*> fieldsInDanger);
    virtual void setInChess(bool inChess);
    virtual bool getInChess();
    virtual void setChessBy(Figure *figure);
    virtual Figure *getChessBy();

};



#endif //ICP_FIGUREKING_H
