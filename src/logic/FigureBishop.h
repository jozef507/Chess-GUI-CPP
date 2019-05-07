//
// Created by Jozef on 4/25/2019.
//

#ifndef ICP_FIGUREBISHOP_H
#define ICP_FIGUREBISHOP_H


#include "Figure.h"
#include "Field.h"

class FigureBishop: public Figure {

private:
    int ID;
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;
    //image
    std::vector<Field*> fieldsInDanger;

    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);
    bool checkDirection(Field::Direction dir, int diff);
    void appendFieldsInDanger(Field::Direction dir);
    std::vector<Field*> appendFieldsInDangerChessMat(Field::Direction dir);


public:
    FigureBishop(bool isWhite);
    ~FigureBishop() = default;
    //virtual Figure::~Figure();
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
};


#endif //ICP_FIGUREBISHOP_H
