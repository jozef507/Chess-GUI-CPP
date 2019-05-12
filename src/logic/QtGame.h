/**
 * QtGame.h
 *
 * Rozhraní pro zjednodušení logiky hry a komunikaci s GUI
 *
 * Autor: Jan Holásek (xholas09)
 */

#ifndef QTGAME_H
#define QTGAME_H

#include <QString>

#include "Game.h"
#include "GameChess.h"

#include "chesstypes.h"
#include "guiinterface.h"

class QtGame
{
    // Vnitřní logika hry
    Game* gameLogic;
    // Grafické rozhraní
    GuiInterface* gui;

    /**
     * @brief Získá typ figury z id
     * @param Id figury
     * @return Typ figury
     */
    FigureType typeFromId(int id);

public:
    QtGame(GuiInterface* gui, QString fileName = nullptr);
    ~QtGame();

    /**
     * @brief Kontrola zda je notace v pořádku
     * @return Vrací true pokud notace obsahuje validní šachovou partii, jinak false
     */
    bool isNotationCorrect();
    /**
     * @brief Obnoví zobrazení notace
     * @param Zda je notace změněna
     */
    void updateNotation(bool changed = false);
    /**
     * @brief Uloží notaci do souboru
     * @param Jméno souboru
     * @return True pokud proběhlo v pořádku, jinak false
     */
    bool saveFile(std::string fileName = "");

    /**
     * @brief Získá barvu hráče, který je aktuálně na tahu
     * @return Barva hráče na tahu
     */
    TeamColor getActivePlayer();
    /**
     * @brief Je partie ve výchozí pozici?
     * @return True pokud jsou figury ve výchozí pozici (před 1. tahem)
     */
    bool isInitialPosition();

    /**
     * @brief Je pole prázdné
     * @param Sloupec
     * @param Řádek
     * @return True pokud je pole prázdné, false pokud je na něm figura
     */
    bool isFieldEmpty(int posX, int posY);
    /**
     * @brief Získá typ figury na daném poli
     * @param Sloupec
     * @param Řádek
     * @return Typ figury
     */
    FigureType getFigureType(int posX, int posY);
    /**
     * @brief Získá barvu figury na daném poli
     * @param Sloupec
     * @param Řádek
     * @return Barva figury
     */
    TeamColor getFigureColor(int posX, int posY);

    /**
     * @brief Nastaví partii do pozice podle indexu tahu a hráče na tahu
     * @param Řádek notace
     * @param Hráč na tahu
     * @return True pokud proběhne úspěšně, false pokud selže
     */
    bool setPosition(int index, TeamColor player);
    /**
     * @brief Nastaví partii o tah dále
     * @return True pokud proběhne úspěšně, false pokud selže
     */
    bool nextPosition();
    /**
     * @brief Vrátí pozici o tah zpět
     * @return True pokud proběhne úspěšně, false pokud selže
     */
    bool previousPosition();

    /**
     * @brief Přidá uživatelem zadaný tah
     * @param Zdrojový sloupec
     * @param Zdrojový řádek
     * @param Cílový sloupec
     * @param Cílový řádek
     * @return True pokud proběhne úspěšně, false pokud selže
     */
    bool addMove(int srcX, int srcY, int dstX, int dstY);
};

#endif // QTGAME_H
