/**
 * QtGame.cpp
 *
 * Rozhraní pro zjednodušení logiky hry a komunikaci s GUI
 *
 * Autor: Jan Holásek (xholas09)
 */

#include "QtGame.h"

#include <QString>
#include <iostream>

QtGame::QtGame(GuiInterface* newGui, QString fileName)
{
    gui = newGui;
    gameLogic = new GameChess(fileName.toUtf8().constData());

    // Initialization cannot access gui
    /*
    gui->updateBoard();

    std::vector<std::string> notation = gameLogic->getGameNotation();
    int notationIndex = gameLogic->getIndexOfGameNotation() + 1; // Proc +1 ??

    gui->updateNotation(notation, notationIndex);
    */
}

QtGame::~QtGame()
{
    delete gameLogic;
}


/**
 * @brief Získá typ figury z id
 * @param Id figury
 * @return Typ figury
 */
FigureType QtGame::typeFromId(int id)
{
    /*
     * 0 - king
     * 1 - queen
     * 2 - bishop
     * 3 - knight
     * 4 - rook
     * 5 - pawn
     */
    switch (id) {
        case 0:
            return  FigureType::king;
        case 1:
            return FigureType::queen;
        case 2:
            return  FigureType::bishop;
        case 3:
            return FigureType::knight;
        case 4:
            return FigureType::rook;
        case 5:
            return FigureType::pawn;
        default:
            return FigureType::invalid;
    }
}

/**
 * @brief Kontrola zda je notace v pořádku
 * @return Vrací true pokud notace obsahuje validní šachovou partii, jinak false
 */
bool QtGame::isNotationCorrect()
{
    return gameLogic->isNotationRight();
}

/**
 * @brief Obnoví zobrazení notace
 * @param Zda je notace změněna
 */
void QtGame::updateNotation(bool changed)
{
    std::vector<std::string> notation = gameLogic->getGameNotation();
    int notationIndex = gameLogic->getIndexOfGameNotation() + 1;

    gui->updateNotation(notation, notationIndex, changed);
}

/**
 * @brief Uloží notaci do souboru
 * @param Jméno souboru
 * @return True pokud proběhlo v pořádku, jinak false
 */
bool QtGame::saveFile(std::string fileName)
{
    if (fileName == "")
    {
        return gameLogic->saveNotation();
    }

    return gameLogic->saveNotationToAnotherFile(fileName);
}

/**
 * @brief Získá barvu hráče, který je aktuálně na tahu
 * @return Barva hráče na tahu
 */
TeamColor QtGame::getActivePlayer()
{
    return gameLogic->isWhiteOnTheMove() == true ? TeamColor::white : TeamColor::black;
}

/**
 * @brief Je partie ve výchozí pozici?
 * @return True pokud jsou figury ve výchozí pozici (před 1. tahem)
 */
bool QtGame::isInitialPosition()
{
    return gameLogic->isFirstIndexOfNotation();
}

/**
 * @brief Je pole prázdné
 * @param Sloupec
 * @param Řádek
 * @return True pokud je pole prázdné, false pokud je na něm figura
 */
bool QtGame::isFieldEmpty(int posX, int posY)
{
    // Chessboard indexing correction
    posX += 1;
    posY += 1;

    return gameLogic->getIsFieldEmpty(posX, posY);
}

/**
 * @brief Získá typ figury na daném poli
 * @param Sloupec
 * @param Řádek
 * @return Typ figury
 */
FigureType QtGame::getFigureType(int posX, int posY)
{
    // Chessboard indexing correction
    posX += 1;
    posY += 1;

    return typeFromId(gameLogic->getFigureIDOnField(posX, posY));
}

/**
 * @brief Získá barvu figury na daném poli
 * @param Sloupec
 * @param Řádek
 * @return Barva figury
 */
TeamColor QtGame::getFigureColor(int posX, int posY)
{
    // Chessboard indexing correction
    posX += 1;
    posY += 1;

    return gameLogic->getIsWhiteFigureOnField(posX, posY) ? TeamColor::white : TeamColor::black;
}


/**
 * @brief Nastaví partii do pozice podle indexu tahu a hráče na tahu
 * @param Řádek notace
 * @param Hráč na tahu
 * @return True pokud proběhne úspěšně, false pokud selže
 */
bool QtGame::setPosition(int index, TeamColor player)
{
    while (previousPosition());
    nextPosition();
    while (gameLogic->getIndexOfGameNotation() != index) {
        nextPosition();
    }
    if (player == TeamColor::black)
    {
        nextPosition();
    }

    return true;
}

/**
 * @brief Nastaví partii o tah dále
 * @return True pokud proběhne úspěšně, false pokud selže
 */
bool QtGame::nextPosition()
{
    if (gameLogic->isLastIndexOfNotation())
    {
        return false;
    }

    gameLogic->nullMovementManager();

    if (!gameLogic->setPlaybackMovement())
    {
        return false;
    }

    if (!gameLogic->performPlaybackMovement())
    {
        return false;
    }

    // gui uses 0-based indexing
    gui->updateFigurePosition(gameLogic->getStartFieldCol() - 1, gameLogic->getStartFieldRow() - 1,
                              gameLogic->getGoalFieldCol() - 1, gameLogic->getGoalFieldRow() - 1);

    if(gameLogic->getIsChangingFigure())
    {
        int typeId = gameLogic->getChangingFigureID();

        gameLogic->createNewFigure(typeId);


        int col = gameLogic->getGoalFieldCol();
        int row = gameLogic->getGoalFieldRow();

        FigureType figureType = typeFromId(typeId);
        TeamColor figureColor = gameLogic->getIsWhiteFigureOnField(col, row) ? TeamColor::white : TeamColor::black;

        gui->changeFigureType(figureType, figureColor, col - 1, row - 1);
    }

    gameLogic->incrementIndexOfNotationLines();
    gameLogic->completeNotationMovement();
    gameLogic->changePlayer();

    updateNotation();

    return true;
}

/**
 * @brief Vrátí pozici o tah zpět
 * @return True pokud proběhne úspěšně, false pokud selže
 */
bool QtGame::previousPosition()
{
    if (gameLogic->isFirstIndexOfNotation())
    {
        return false;
    }

    gameLogic->nullMovementManager();

    if (!gameLogic->setPlaybackUndoMovement())
    {
        return false;
    }

    if (!gameLogic->performPlaybackUndoMovement())
    {
        return false;
    }

    // gui uses 0-based indexing
    gui->updateFigurePosition(gameLogic->getGoalFieldCol() - 1, gameLogic->getGoalFieldRow() - 1,
                              gameLogic->getStartFieldCol() - 1, gameLogic->getStartFieldRow() - 1 );

    // If figure was a pawn, change back to pawn
    if (gameLogic->getIsChangingFigure())
    {
        gui->updatePosition(gameLogic->getStartFieldCol() - 1, gameLogic->getStartFieldRow() - 1);
    }

    // Recreate removed figure
    if (gameLogic->isRemovingFigure())
    {
        gui->updatePosition(gameLogic->getGoalFieldCol() - 1, gameLogic->getGoalFieldRow() - 1);
    }

    gameLogic->decrementIndexOfNotationLines();

    updateNotation();

    return true;
}

/**
 * @brief Přidá uživatelem zadaný tah
 * @param Zdrojový sloupec
 * @param Zdrojový řádek
 * @param Cílový sloupec
 * @param Cílový řádek
 * @return True pokud proběhne úspěšně, false pokud selže
 */
bool QtGame::addMove(int srcX, int srcY, int dstX, int dstY)
{
    // Chessboard indexing correction
    srcX += 1;
    srcY += 1;
    dstX += 1;
    dstY += 1;

    gameLogic->nullMovementManager();

    if (!gameLogic->setPlayerMovement(srcX, srcY))
    {
        return false;
    }
    if (!gameLogic->setPlayerMovement(dstX, dstY))
    {
        return false;
    }
    if (!gameLogic->isMovementCompletlySet())
    {
        return false;
    }

    if (!gameLogic->performPlayerMovement())
    {
        return false;
    }

    // gui uses 0-based indexing
    gui->updateFigurePosition(srcX - 1, srcY - 1, dstX - 1, dstY - 1);

    // Figure change
    if (gameLogic->getIsChangingFigure())
    {
        FigureType newFigureType = gui->getNewFigureType();

        int newFigureId;
        switch (newFigureType) {
        case FigureType::knight:
            newFigureId = 3;
            break;
        case FigureType::bishop:
            newFigureId = 2;
            break;
        case FigureType::rook:
            newFigureId = 4;
            break;
        case FigureType::queen:
            newFigureId = 1;
            break;
        default:
            newFigureId = -1;
            break;
        }

        if (!gameLogic->createNewFigure(newFigureId))
        {
            return false;
        }
        // gui uses 0-based indexing
        gui->changeFigureType(typeFromId(newFigureId), gameLogic->isWhiteOnTheMove() ? TeamColor::white : TeamColor::black, dstX - 1, dstY - 1);
    }

    gameLogic->addPlayerNotationMovement();
    gameLogic->completeNotationMovement();
    gameLogic->changePlayer();

    updateNotation(true);

    return true;
}
