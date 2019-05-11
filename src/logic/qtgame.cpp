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

bool QtGame::saveFile(std::string fileName)
{
    if (fileName == "")
    {
        return gameLogic->saveNotation();
    }

    return gameLogic->saveNotationToAnotherFile(fileName);
}

TeamColor QtGame::getActivePlayer()
{
    return gameLogic->isWhiteOnTheMove() == true ? TeamColor::white : TeamColor::black;
}

bool QtGame::isInitialPosition()
{
    return gameLogic->isFirstIndexOfNotation();
}

bool QtGame::isFieldEmpty(int posX, int posY)
{
    // Chessboard indexing correction
    posX += 1;
    posY += 1;

    return gameLogic->getIsFieldEmpty(posX, posY);
}

FigureType QtGame::getFigureType(int posX, int posY)
{
    // Chessboard indexing correction
    posX += 1;
    posY += 1;

    return typeFromId(gameLogic->getFigureIDOnField(posX, posY));
}

TeamColor QtGame::getFigureColor(int posX, int posY)
{
    // Chessboard indexing correction
    posX += 1;
    posY += 1;

    return gameLogic->getIsWhiteFigureOnField(posX, posY) ? TeamColor::white : TeamColor::black;
}


bool QtGame::setPosition(int index)
{
    while (gameLogic->getIndexOfGameNotation() != index) {
        if (gameLogic->getIndexOfGameNotation() < index)
        {
            if (!nextPosition())
            {
                return false;
            }
        }
        else
        {
            if (!previousPosition())
            {
                return false;
            }
        }
    }

    return true;
}

/*
-game.setPlaybackMovement()
-ak funkcia vratila true (znamena že nastavenie prebehlo úspešne... tuna už nekontorluješ isMovementCompletlySet!!!):
    -game.performPlaybackMovement();
    -ak funkcia vratila true:
        -tvoje grafické úkony
        -v prípade že pri ťahu došlo k zámene pešiaka za novu figúrku (zistíš pomocou funkcie game.getIsCHangingFigure()):
            -keďže sa figurka vymenila podľa notacie už je vymenena za novú. To o akú novú figúrku ide zistíš pomocou funkcie
             game.getChangingFigureID(), ktorá ti vráti ID figúrky (1-queen, 2-bishop, 3-knight, 4-rook), farbu figurky pomocou
             game.isWhiteOnTheMove(ak true->biela ak nie čierna)
        -game.incrementIndexOfNotationLines();
        -teraz môžeš vypýtať notaciu aby si ju vypísal (game.getGameNotation(), game.getIndexOfGameNotation()+1//poradie riadka na vyznačenie)
        -game.completeNotationMovement();
            -game.nullMovementManager();
            -game.changePlayer();
    -ak false:
        -game.nullMovementManager();
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
        int col = gameLogic->getGoalFieldCol();
        int row = gameLogic->getGoalFieldRow();

        int typeId = gameLogic->getFigureIDOnField(col, row);
        FigureType figureType = typeFromId(typeId);

        TeamColor figureColor = gameLogic->getIsWhiteFigureOnField(col, row) ? TeamColor::white : TeamColor::black;

        gui->changeFigureType(figureType, figureColor, col, row);
    }

    gameLogic->incrementIndexOfNotationLines();
    gameLogic->completeNotationMovement();
    gameLogic->changePlayer();

    std::vector<std::string> notation = gameLogic->getGameNotation();
    int notationIndex = gameLogic->getIndexOfGameNotation() + 1;

    gui->updateNotation(notation, notationIndex);

    return true;
}

/*
-game.setPlaybackUndoMovement();
-ak funkcia vratila true (znamena že nastavenie prebehlo úspešne... tuna už nekontorluješ isMovementCompletlySet!!!):
    -game.performPlaybackUndoMovement();
    -ak funkcia vratila true:
        -tvoje grafické úkony<
        -game.decrementIndexOfNotationLines();
        -teraz môžeš vypýtať notaciu aby si ju vypísal (game.getGameNotation(), game.getIndexOfGameNotation()+1//poradie riadka na vyznačenie)
        -game.nullMovementManager();
    -ak false:
        -game.nullMovementManager();
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

    gui->updatePosition(gameLogic->getGoalFieldCol() - 1, gameLogic->getGoalFieldRow() - 1);

    gameLogic->decrementIndexOfNotationLines();

    std::vector<std::string> notation = gameLogic->getGameNotation();
    int notationIndex = gameLogic->getIndexOfGameNotation() + 1;

    gui->updateNotation(notation, notationIndex);

    return true;
}

/*
    Navod:

    -game.setPlayerMovement()
    -ak funkcia vratila true (znamena že nastavenie prebehlo úspešne... tuna už potrebuješ kontrolovať či je MovementManager kompletne nastaveny pomocou isMovementCompletlySet() -> ak true možeš vojsť do podmienky):
        -game.performPlayerMovement();
        -ak funkcia vratila true:
            -tvoje grafické úkony
            -v prípade že pri ťahu došlo k zámene pešiaka za novu figúrku (zistíš pomocou funkcie game.getIsCHangingFigure()):
                -musí užívateľ vybrať figúrku, po tom ju treba v logike vytvoriť pomocou game.createNewFigure(ID_figúrky)
            -game.addPlayerNotationMovement();
            -teraz môžeš vypýtať notaciu aby si ju vypísal (game.getGameNotation(), game.getIndexOfGameNotation()+1//poradie riadka na vyznačenie)
            -game.completeNotationMovement();
                -game.nullMovementManager();
                -game.changePlayer();
        -ak false:
            -game.nullMovementManager();
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
        int newFigureId = gui->getNewFigureId();
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

    std::vector<std::string> notation = gameLogic->getGameNotation();
    int notationIndex = gameLogic->getIndexOfGameNotation() + 1; // Proc +1 ??

    gui->updateNotation(notation, notationIndex, true);

    return true;
}

/*
 * 0 - king
 * 1 - queen
 * 2 - bishop
 * 3 - knight
 * 4 - rook
 * 5 - pawn
 */
FigureType QtGame::typeFromId(int id)
{
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
