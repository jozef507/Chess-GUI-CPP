/**
 * guiinterface.h
 *
 * Rozhraní pro aktualizaci GUI z logiky hry
 *
 * Autor: Jan Holásek (xholas09)
 */

#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <vector>

#include "chesstypes.h"

class GuiInterface
{
public:
    virtual ~GuiInterface() = default;

    /**
     * @brief Získá typ nové figury
     * @return Typ vybrané figury
     */
    virtual FigureType getNewFigureType() = 0;

    /**
     * @brief Přesunutí figury
     * @param Zdrojový sloupec
     * @param Zdrojový řádek
     * @param Cílový sloupec
     * @param Cílový řádek
     */
    virtual void updateFigurePosition(int srcX, int srcY, int dstX, int dstY) = 0;
    /**
     * @brief Změna typu figury
     * @param Typ
     * @param Barva
     * @param Sloupec
     * @param Řádek
     */
    virtual void changeFigureType(FigureType newType, TeamColor color, int posX, int posY)     = 0;
    /**
     * @brief Obnoví obsah pole
     * @param Sloupec
     * @param Řádek
     */
    virtual void updatePosition(int posX, int posY) = 0;
    /**
     * @brief Obnoví obsah šachovnice
     */
    virtual void updateBoard() = 0;
    /**
     * @brief Obnoví notaci
     * @param Vektor řádků notace
     * @param Aktuální řádek notace
     * @param Byla notace změněna
     */
    virtual void updateNotation(std::vector<std::string> notation, int index, bool changed = false) = 0;
};

#endif // GUIINTERFACE_H
