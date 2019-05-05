//
// Created by Jozef on 4/19/2019.
//

#ifndef ICP_FIGURE_H
#define ICP_FIGURE_H

#include <algorithm>
#include <vector>


class FiguresManager;
class Field;
class Figure
{
public:
    virtual ~Figure()= default;
    virtual int move (Field *moveTo, FiguresManager *figuresManager) = 0;
    virtual bool isWhiteF()=0;
    virtual void setActualPosition(Field *field)=0;
    virtual void nulActualPosition()=0;
    virtual Field *getActualField()=0;
    //getImage

    virtual void setFieldsInDanger() = 0;
    virtual std::vector<Field*> getFieldsInDanger() = 0;
    virtual std::vector<Field*> getFieldsForPossMov() = 0;
    virtual std::vector<Field*> getFieldsInDangerChesMat() = 0;
    virtual std::vector<Field*> getFieldsOfDirectionToField(Field *field) = 0;
    virtual int getID() = 0;

};



#endif //ICP_FIGURE_H
