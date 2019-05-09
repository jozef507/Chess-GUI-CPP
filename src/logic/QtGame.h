#ifndef QTGAME_H
#define QTGAME_H

#include <QString>

#include "Game.h"
#include "GameChess.h"

#include "chesstypes.h"
#include "guiinterface.h"

class QtGame
{
    Game* gameLogic;
    GuiInterface* gui;

    FigureType typeFromId(int id);

public:
    QtGame(GuiInterface* gui, QString fileName = nullptr);
    ~QtGame();

    bool setFile(QString fileName);
    QString getFile();
    bool saveFile();

    bool setPosition(int index);
    bool nextPosition();
    bool previousPosition();

    bool addMove(int srcX, int srcY, int dstX, int dstY);
};

#endif // QTGAME_H
