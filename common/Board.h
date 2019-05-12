/**
 * Trieda obsahuje reprezentáciu šachovnice
 * @author Jozef Ondria
 * @author Jan Holásek
 */
#ifndef ICP_BOARD_H
#define ICP_BOARD_H

#include "Field.h"

/**
 * Trieda reprezentujúca šachovnicu. Šachovnica je reprezentovaná
 * dvojrozmerným poľom inštancii triedy/rozhrania Field.
 */
class Board
{
private:
    Field ***board;

    /**
     * Vracia odkaz na susedné políčko políčka určeného jeho pozíciou.
     * @param dirs Smer susedného políčka.
     * @param col Stlpec pozície aktuálneho políčka.
     * @param row Riadok pozície aktuálneho políčka.
     * @param size Veľkosť šachovnice.
     * @return Odkaz na susedné políčko (Field).
     */
    Field *chooseNextField(Field::Direction dirs, int col, int row, int size);

    /**
     * Vráti susedný stlpec na šachovnici.
     * @param dirs Smer na šachovnici.
     * @return Celočíselnu hodnotu o úspechu.
     */
    int getNextCol(Field::Direction dirs);

    /**
     * Vráti susedný riadok na šachovnici.
     * @param dirs Smer na šachovnici.
     * @return Celočíselnu hodnotu o úspechu.
     */
    int getNextRow (Field::Direction dirs);
public:

    /**
     * Inicializuje šachovnicu.
     * @param size Počet riadov/stlpcov poličok šachovnice.
     */
    Board(int size);

    /**
     * Deštruktor.
     */
    ~Board();

    /**
     * Vracia veľkosť šachovnice.
     * @return Veľkosť šachovnice.
     */
    int getSize();

    /**
     * Vracia odkaz na poličko (Field) na základe jeho pozície.
     * @param col Stlpec pozície políčka.
     * @param row Riadok pozície políčka.
     * @return Odkaz na políčko(Field).
     */
    Field *getField(int col, int row);

};


#endif //ICP_BOARD_H
