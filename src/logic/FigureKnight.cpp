//
// Created by Jozef on 4/25/2019.
//

#include "FigureKnight.h"
#include "FiguresManager.h"
#include "Field.h"
#include "cmath"


/**
 * Inicializacia kráľa.
 * @param isWhite Informacia o farbe.
 * @param image Obrázok figúrky používaný v grafickom rozhraní.
 */
FigureKnight::FigureKnight(bool isWhite)
{
    this->ID = 3;
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


/**
 * Vracia informáciu o tom či je figúrka biela. Ak nie je čierna.
 * @return Pravdivostna hodnota.
 */
bool FigureKnight::isWhiteF()
{
    return this->isWhite;
}


/**
 * Vráti pozíciu aktualnej pozície figúrky.
 * @return Odkaz na políčko.
 */
Field *FigureKnight::getActualField()
{
    return this->actField;
}


/**
 * Nastaví aktuálnu pozíciu figúrky.
 * @param field Políčko pozície na ktorú sa má figurka nastaviť.
 */
void FigureKnight::setActualPosition(Field *field)
{
    this->actField = field;
}


/**
 * Vynulovanie/zrušenie aktualnej pozície figúrky.
 */
void FigureKnight::nulActualPosition()
{
    this->actField = nullptr;
}


/**
 * Vykonáva ťah figúrky a zároveń testuje či je ťah možný.
 * @param moveTo Cieľove políčko ťahu.
 * @param figuresManager Manažer aktívnych figúrok.
 * @return Stav úspešnosti ťahu.
 */
int FigureKnight::move(Field *moveTo, FiguresManager *figuresManager)
{
    if(this->actField == nullptr)
        return -1;

    int actCol = this->actField->getColPos();
    int actRow = this->actField->getRowPos();
    int movetoCol = moveTo->getColPos();
    int movetoRow = moveTo->getRowPos();

    if(actCol == movetoCol && actRow == movetoRow)
        return -1;

    if(!isMovementPossible(actCol, actRow, moveTo, movetoCol, movetoRow))
        return -1;

    int flag = 1;
    Figure *movetoFigure = nullptr;
    Field *prevField = this->actField;

    if(this->isRemovingFigure)
    {
        movetoFigure = moveTo->get();
        moveTo->remove(movetoFigure);
        this->isRemovingFigure = false;
        flag = 2;
    }
    this->actField->remove(this);
    moveTo->put(this);

    if(!figuresManager->updateFigures(this->isWhiteF(), this, movetoFigure))
    {
        moveTo->remove(this);
        prevField->put(this);
        if (flag == 2)
        {
            moveTo->put(movetoFigure);
        }
        flag = -1;
    }

    return flag;
}

/**
 * Testuje či je ťah na cieľove políčko možný.
 * @param actCol Stlpec aktuálneho polička.
 * @param actRow Riadok aktualneho políčka.
 * @param moveTo Cieľové políčko.
 * @param movetoCol Stlpec aktuálneho polička.
 * @param movetoRow Riadok aktualneho políčka.
 * @return Pravdivostná hodnota.
 */
bool FigureKnight::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    if(!((colDiff == 2 && rowDiff == 1) || (colDiff == 1 && rowDiff == 2)))
        return false;

    if(!moveTo->isEmpty())
    {
        Figure *movetoFigure = moveTo->get();
        if(movetoFigure->isWhiteF() == this->isWhiteF())
            return false;

        if(movetoFigure->getID() == 0)
            return false;

        this->isRemovingFigure = true;
    }

    return true;
}


/**
 * Nastaví pre figúrku všetky políčka ktoré táto figúrka ohrozuej.
 */
void FigureKnight::setFieldsInDanger()
{
    this->fieldsInDanger.clear();

    Field *tmpField, *nextField;

    nextField = this->actField->nextField(Field::Direction::U);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::U);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::L);
            nextField = nextField->nextField(Field::Direction::R);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }

    nextField = this->actField->nextField(Field::Direction::L);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::L);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::U);
            nextField = nextField->nextField(Field::Direction::D);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }
    nextField = this->actField->nextField(Field::Direction::D);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::D);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::L);
            nextField = nextField->nextField(Field::Direction::R);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }
    nextField = this->actField->nextField(Field::Direction::R);
    if(nextField != nullptr)
    {
        nextField = nextField->nextField(Field::Direction::R);
        if(nextField != nullptr)
        {
            tmpField = nextField->nextField(Field::Direction::U);
            nextField = nextField->nextField(Field::Direction::D);

            if (tmpField != nullptr)
                this->fieldsInDanger.push_back(tmpField);
            if (nextField != nullptr)
                this->fieldsInDanger.push_back(nextField);
        }
    }
}


/**
 * Vracia štruktúru políčok ktoré figúrka ohrozuje.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureKnight::getFieldsInDanger()
{
    return this->fieldsInDanger;
}


/**
 * Vracia id figúrky.
 * @return ID figúrky.
 */
int FigureKnight::getID()
{
    return this->ID;
}


/**
 * Vráti štruktúru všetkych políčok smerujúcich k danému fieldu v parametri.
 * @param field Odkaz na field.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureKnight::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    std::vector<Field*> fieldsOfDirToField;
    fieldsOfDirToField.push_back(this->actField);

    return fieldsOfDirToField;
}


/**
 * Vracia štruktúru všetkých políčok ktorými môže ohrozovať súperoveho kráľa.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureKnight::getFieldsForPossMov()
{
    return this->fieldsInDanger;
}


/**
 * Vracia štruktúru všetkých políčok ktorými môže figúrka vytvárať šachmat.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureKnight::getFieldsInDangerChesMat()
{
    return this->fieldsInDanger;
}
