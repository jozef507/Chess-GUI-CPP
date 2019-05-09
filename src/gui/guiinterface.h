#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <vector>

#include "chesstypes.h"

class GuiInterface
{
public:
    virtual ~GuiInterface() = default;

    virtual int getNewFigureId() = 0;

    virtual void updateFigurePosition(int srcX, int srcY, int dstX, int dstY) = 0;
    virtual void changeFigureType(FigureType newType, TeamColor color, int posX, int posY)     = 0;
    virtual void updateNotation(std::vector<std::string> notation, int index) = 0;
};

#endif // GUIINTERFACE_H
