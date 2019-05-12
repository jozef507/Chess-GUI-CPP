/**
 * Trieda reprezentuje figúrku jazdca.
 * @author Jozef Ondria
 * @author Jan Holásek
 */

#ifndef ICP_FIGUREKING_H
#define ICP_FIGUREKING_H

#include "Figure.h"
#include "Field.h"

/**
 * Trieda reprezentujúca figúrku kráľa.
 * Implementuje rozhranie Figure.
 */
class FigureKing: public Figure {
private:
    int ID;
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;
    //image
    std::vector<Field*> fieldsInDanger;
    bool inChess;
    Figure *chessBy;

    /**
     * Testuje či je ťah na cieľove políčko možný.
     * @param actCol Stlpec aktuálneho polička.
     * @param actRow Riadok aktualneho políčka.
     * @param moveTo Cieľové políčko.
     * @param movetoCol Stlpec aktuálneho polička.
     * @param movetoRow Riadok aktualneho políčka.
     * @return Pravdivostná hodnota.
     */
    bool isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow);

    /**
     * Pridá polička v danom smere.
     * @param dir Smer na šachovnici.
     */
    void appendFieldsInDanger(Field::Direction dir);


public:

    /**
     * Inicializacia kráľa.
     * @param isWhite Informacia o farbe.
     * @param image Obrázok figúrky používaný v grafickom rozhraní.
     */
    FigureKing(bool isWhite);

    /**
     * Deštruktor.
     */
    ~FigureKing() = default;

    /**
     * Vykonáva ťah figúrky a zároveń testuje či je ťah možný.
     * @param moveTo Cieľove políčko ťahu.
     * @param figuresManager Manažer aktívnych figúrok.
     * @return Stav úspešnosti ťahu.
     */
    virtual int move(Field *moveTo, FiguresManager *figuresManager);

    /**
     * Vracia informáciu o tom či je figúrka biela. Ak nie je čierna.
     * @return Pravdivostna hodnota.
     */
    virtual bool isWhiteF();

    /**
     * Nastaví aktuálnu pozíciu figúrky.
     * @param field Políčko pozície na ktorú sa má figurka nastaviť.
     */
    virtual void setActualPosition(Field *field);

    /**
     * Vynulovanie/zrušenie aktualnej pozície figúrky.
     */
    virtual void nulActualPosition();

    /**
     * Vráti pozíciu aktualnej pozície figúrky.
     * @return Odkaz na políčko.
     */
    virtual Field *getActualField();

    /**
     * Nastaví pre figúrku všetky políčka ktoré táto figúrka ohrozuej.
     */
    virtual void setFieldsInDanger();

    /**
     * Vracia štruktúru políčok ktoré figúrka ohrozuje.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsInDanger();

    /**
     * Vracia štruktúru všetkých políčok ktorými môže ohrozovať súperoveho kráľa.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsForPossMov();

    /**
     * Vracia štruktúru všetkých políčok ktorými môže figúrka vytvárať šachmat.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsInDangerChesMat();

    /**
     * Vráti štruktúru všetkych políčok smerujúcich k danému fieldu v parametri.
     * @param field Odkaz na field.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsOfDirectionToField(Field *field);

    /**
     * Vracia id figúrky.
     * @return ID figúrky.
     */
    virtual int getID();


    /**
     * Testuje pri šachu či sa tento kráľ môže niekam pohnúť.
     * @param fieldsInDangerOut Ohrozené políčka.
     * @return Výsledok testu.
     */
    virtual bool canMove(std::vector<Field*> fieldsInDanger);

    /**
     * Nastaví informáciu, či je kraľ v šachu.
     * @param inChess
     */
    virtual void setInChess(bool inChess);

    /**
     * Vráti informáciu či je kráľ v šachu.
     * @return Pravdivostná hodnota.
     */
    virtual bool getInChess();

    /**
     * Nastaví informáciu že je kráľ v šachu danou figúrkou.
     * @param figure hodnota.
     */
    virtual void setChessBy(Figure *figure);

    /**
     * Vráti figúrku ktorou je tento kraľ v šachu.
     * @return
     */
    virtual Figure *getChessBy();

};



#endif //ICP_FIGUREKING_H
