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

    bool isNotationCorrect();
    void updateNotation();
    bool saveFile(std::string fileName = "");

    TeamColor getActivePlayer();
    bool isInitialPosition();

    bool isFieldEmpty(int posX, int posY);
    FigureType getFigureType(int posX, int posY);
    TeamColor getFigureColor(int posX, int posY);

    bool setPosition(int index, TeamColor player);
    bool nextPosition();
    bool previousPosition();

    bool addMove(int srcX, int srcY, int dstX, int dstY);
};

#endif // QTGAME_H
