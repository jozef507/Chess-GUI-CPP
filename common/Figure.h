//
// Created by Jozef on 4/19/2019.
//

#ifndef ICP_FIGURE_H
#define ICP_FIGURE_H

#include <algorithm>
#include <vector>


class FiguresManager;
class Field;

/**
 * Rozhranie reprezentujúce figúrku.
 */
class Figure
{
public:

    /**
     * Deštruktor.
     */
    virtual ~Figure()= default;

    /**
     * Vykonáva ťah figúrky a zároveń testuje či je ťah možný.
     * @param moveTo Cieľove políčko ťahu.
     * @param figuresManager Manažer aktívnych figúrok.
     * @return Stav úspešnosti ťahu.
     */
    virtual int move (Field *moveTo, FiguresManager *figuresManager) = 0;

    /**
     * Vracia informáciu o tom či je figúrka biela. Ak nie je čierna.
     * @return Pravdivostna hodnota.
     */
    virtual bool isWhiteF()=0;

    /**
     * Nastaví aktuálnu pozíciu figúrky.
     * @param field Políčko pozície na ktorú sa má figurka nastaviť.
     */
    virtual void setActualPosition(Field *field)=0;

    /**
     * Vynulovanie/zrušenie aktualnej pozície figúrky.
     */
    virtual void nulActualPosition()=0;

    /**
     * Vráti pozíciu aktualnej pozície figúrky.
     * @return Odkaz na políčko.
     */
    virtual Field *getActualField()=0;
    //getImage


    /**
     * Nastaví pre figúrku všetky políčka ktoré táto figúrka ohrozuej.
     */
    virtual void setFieldsInDanger() = 0;

    /**
     * Vracia štruktúru políčok ktoré figúrka ohrozuje.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsInDanger() = 0;

    /**
     * Vracia štruktúru všetkých políčok ktorými môže ohrozovať súperoveho kráľa.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsForPossMov() = 0;

    /**
     * Vracia štruktúru všetkých políčok ktorými môže figúrka vytvárať šachmat.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsInDangerChesMat() = 0;

    /**
     * Vráti štruktúru všetkych políčok smerujúcich k danému fieldu v parametri.
     * @param field Odkaz na field.
     * @return Štruktúra políčok.
     */
    virtual std::vector<Field*> getFieldsOfDirectionToField(Field *field) = 0;

    /**
     * Vracia id figúrky.
     * @return ID figúrky.
     */
    virtual int getID() = 0;
};



#endif //ICP_FIGURE_H
