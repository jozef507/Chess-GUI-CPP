//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_FIGUREROOK_H
#define ICP_FIGUREROOK_H

#include "Figure.h"
#include "Field.h"

/**
 * Trieda reprezentujúca figúrku veže.
 * Implementuje rozhranie Figure.
 */
class FigureRook: public Figure {

private:
    int ID;
    bool isWhite;
    bool isRemovingFigure;
    Field *actField;
    //image
    std::vector<Field*> fieldsInDanger;


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
     * Skontroluje polička v danom smere, či sa tam nenachádza iná figúrka.
     * @param dir Smer na šachovnici.
     * @param diff Rozdiel políčok ktorý treba otestovať.
     * @return Pravdivostna hodnota.
     */
    bool checkDirection(Field::Direction dir, int diff);

    /**
      * Pridá polička v danom smere.
      * @param dir Smer na šachovnici.
     */
    void appendFieldsInDanger(Field::Direction dir);

    /**
    * Pridá polička v danom smere.
    * @param dir Smer na šachovnici.
    */
    std::vector<Field*> appendFieldsInDangerChessMat(Field::Direction dir);


public:

    /**
     * Inicializacia veže.
     * @param isWhite Informacia o farbe.
     * @param image Obrázok figúrky používaný v grafickom rozhraní.
     */
    FigureRook(bool isWhite);

    /**
     * Deštruktor.
     */
    ~FigureRook() = default;
    //virtual Figure::~Figure();

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
};


#endif //ICP_FIGUREROOK_H
