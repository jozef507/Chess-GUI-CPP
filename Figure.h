//
// Created by Jozef on 4/19/2019.
//

#ifndef ICP_FIGURE_H
#define ICP_FIGURE_H

#include "Field.h"

class Field;
class Figure
{
    public:
        virtual ~Figure()= default;
        virtual int move (Field *moveTo)=0;
        virtual bool isWhiteF()=0;
        virtual void setActualPosition(Field *field)=0;
        virtual void nulActualPosition()=0;
        virtual Field *getActualField()=0;
        //getImage
};



#endif //ICP_FIGURE_H
