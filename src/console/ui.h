#ifndef UI_H
#define UI_H

#include "../gui/guiinterface.h"
#include "../logic/QtGame.h"

#include "../gui/chesstypes.h"

class UI: public GuiInterface
{
public:
    UI();
    ~UI();

    void run();

private:
    QtGame* game;

    int typeToInt(FigureType type);

    int getNewFigureId();

    void updateFigurePosition(int srcX, int srcY, int dstX, int dstY);
    void changeFigureType(FigureType newType, TeamColor color, int posX, int posY);
    void updateBoard();
    void updateNotation(std::vector<std::string> notation, int index);
};

#endif // UI_H
