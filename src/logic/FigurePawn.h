//
// Created by Jozef on 4/21/2019.
//

#ifndef ICP_FIGUREPAWN_H
#define ICP_FIGUREPAWN_H

#include "Figure.h"
#include "Field.h"


class FigurePawn: public Figure {

private:
    int ID;
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;
    bool firstMovementDone;
    std::vector<Field*> fieldsInDanger;


    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);
    bool checkDirWithoutRemove(Field::Direction dir, int diff);
    bool isOnTheLastField();

public:
    FigurePawn(bool isWhite);
    ~FigurePawn() = default;
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


#endif //ICP_FIGUREPAWN_H
