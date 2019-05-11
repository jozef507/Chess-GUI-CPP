//
// Created by Jozef on 4/25/2019.
//

#include "FigureQueen.h"
#include "FiguresManager.h"
#include "cmath"


/**
 * Inicializacia dámy.
 * @param isWhite Informacia o farbe.
 * @param image Obrázok figúrky používaný v grafickom rozhraní.
 */
FigureQueen::FigureQueen(bool isWhite)
{
    this->ID = 1;
    this->isWhite = isWhite;
    this->isRemovingFigure = false;
    this->actField = nullptr;
    //image
}


/**
 * Vracia informáciu o tom či je figúrka biela. Ak nie je čierna.
 * @return Pravdivostna hodnota.
 */
bool FigureQueen::isWhiteF()
{
    return this->isWhite;
}


/**
 * Vráti pozíciu aktualnej pozície figúrky.
 * @return Odkaz na políčko.
 */
Field *FigureQueen::getActualField()
{
    return this->actField;
}


/**
  * Nastaví aktuálnu pozíciu figúrky.
  * @param field Políčko pozície na ktorú sa má figurka nastaviť.
  */
void FigureQueen::setActualPosition(Field *field)
{
    this->actField = field;
}


/**
* Vynulovanie/zrušenie aktualnej pozície figúrky.
*/
void FigureQueen::nulActualPosition()
{
    this->actField = nullptr;
}


/**
* Vykonáva ťah figúrky a zároveń testuje či je ťah možný.
* @param moveTo Cieľove políčko ťahu.
* @param figuresManager Manažer aktívnych figúrok.
* @return Stav úspešnosti ťahu.
*/
int FigureQueen::move(Field *moveTo, FiguresManager *figuresManager)
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
bool FigureQueen::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    Field::Direction dir;
    if(colDiff != 0 && colDiff == rowDiff)
    {
        if(actRow < movetoRow && actCol < movetoCol)
        {
            dir = Field::Direction::RU;
        }
        else if(actRow < movetoRow && actCol > movetoCol)
        {
            dir = Field::Direction::LU;
        }
        else if (actRow > movetoRow && actCol < movetoCol)
        {
            dir = Field::Direction::RD;
        }
        else if (actRow > movetoRow && actCol > movetoCol)
        {
            dir = Field::Direction::LD;
        }
        else
        {
            return false;
        }
    }
    else if((colDiff == 0 && rowDiff !=0) || (colDiff != 0 && rowDiff ==0))
    {
        if(actRow < movetoRow && colDiff == 0)
        {
            dir = Field::Direction::U;
        }
        else if(actRow > movetoRow && colDiff == 0)
        {
            dir = Field::Direction::D;
        }
        else if (actCol < movetoCol && rowDiff == 0)
        {
            dir = Field::Direction::R;
        }
        else if (actCol > movetoCol && rowDiff == 0)
        {
            dir = Field::Direction::L;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    int diff = (rowDiff == 0 ? colDiff : rowDiff);
    if(!checkDirection(dir, diff))
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
 * Skontroluje polička v danom smere, či sa tam nenachádza iná figúrka.
 * @param dir Smer na šachovnici.
 * @param diff Rozdiel políčok ktorý treba otestovať.
 * @return Pravdivostna hodnota.
 */
bool FigureQueen::checkDirection(Field::Direction dir, int diff)
{
    Field *nextField=this->actField;
    for (int i = 0; i < diff-1; i++)
    {
        nextField = nextField->nextField(dir);
        if(!(nextField->isEmpty()))
            return false;
    }
    return true;
}


/**
 * Nastaví pre figúrku všetky políčka ktoré táto figúrka ohrozuej.
 */
void FigureQueen::setFieldsInDanger()
{
    this->fieldsInDanger.clear();
    this->appendFieldsInDanger(Field::Direction::RU);
    this->appendFieldsInDanger(Field::Direction::LU);
    this->appendFieldsInDanger(Field::Direction::RD);
    this->appendFieldsInDanger(Field::Direction::LD);

    this->appendFieldsInDanger(Field::Direction::U);
    this->appendFieldsInDanger(Field::Direction::D);
    this->appendFieldsInDanger(Field::Direction::R);
    this->appendFieldsInDanger(Field::Direction::L);
}


/**
  * Pridá polička v danom smere.
  * @param dir Smer na šachovnici.
 */
void FigureQueen::appendFieldsInDanger(Field::Direction dir)
{
    Field *nextField=this->actField->nextField(dir);
    while (nextField != nullptr)
    {
        this->fieldsInDanger.push_back(nextField);
        if (!nextField->isEmpty())
            break;
        nextField = nextField->nextField(dir);
    }
}


/**
 * Vracia štruktúru políčok ktoré figúrka ohrozuje.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureQueen::getFieldsInDanger()
{
    return this->fieldsInDanger;
}


/**
 * Vracia id figúrky.
 * @return ID figúrky.
 */
int FigureQueen::getID()
{
    return this->ID;
}


/**
 * Vráti štruktúru všetkych políčok smerujúcich k danému fieldu v parametri.
 * @param field Odkaz na field.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureQueen::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    int colDiff = field->getColPos() - this->actField->getColPos();
    int rowDiff = field->getRowPos() - this->actField->getRowPos();

    Field::Direction dir;
    if (colDiff>0 && rowDiff==0)
        dir = Field::Direction::R;
    else if (colDiff<0 && rowDiff==0)
        dir = Field::Direction::L;
    else if (colDiff==0 && rowDiff>0)
        dir = Field::Direction::D;
    else if (colDiff==0 && rowDiff<0)
        dir = Field::Direction::U;
    else if (colDiff>0 && rowDiff>0 && std::abs(colDiff) == std::abs(rowDiff))
        dir = Field::Direction::RU;
    else if (colDiff>0 && rowDiff<0 && std::abs(colDiff) == std::abs(rowDiff))
        dir = Field::Direction::RD;
    else if (colDiff<0 && rowDiff>0 && std::abs(colDiff) == std::abs(rowDiff))
        dir = Field::Direction::LU;
    else if (colDiff<0 && rowDiff<0 && std::abs(colDiff) == std::abs(rowDiff))
        dir = Field::Direction::LD;
    else
        dir = Field::Direction::NONE;

    if(dir == Field::Direction::NONE)
        return {};

    std::vector<Field*> fieldsOfDirToField;
    Field *nextField = this->actField;
    while (nextField!=field)
    {
        fieldsOfDirToField.push_back(nextField);
        nextField = nextField->nextField(dir);
    }

    return fieldsOfDirToField;
}


/**
 * Vracia štruktúru všetkých políčok ktorými môže ohrozovať súperoveho kráľa.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureQueen::getFieldsForPossMov()
{
    return this->fieldsInDanger;
}


/**
 * Vracia štruktúru všetkých políčok ktorými môže figúrka vytvárať šachmat.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigureQueen::getFieldsInDangerChesMat()
{
    std::vector<Field*> tmp;
    std::vector<Field*> tmp1;

    tmp1 = appendFieldsInDangerChessMat(Field::Direction::RU);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::RD);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::LU);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::LD);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));

    tmp1 = appendFieldsInDangerChessMat(Field::Direction::U);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::D);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::R);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));
    tmp1 = appendFieldsInDangerChessMat(Field::Direction::L);
    tmp.insert(std::end(tmp), std::begin(tmp1), std::end(tmp1));

    return tmp;
}


/**
  * Pridá polička v danom smere.
  * @param dir Smer na šachovnici.
*/
std::vector<Field*> FigureQueen::appendFieldsInDangerChessMat(Field::Direction dir)
{
    std::vector<Field*> tmp;
    Field *nextField = this->actField->nextField(dir);
    while (nextField != nullptr)
    {
        tmp.push_back(nextField);
        if (!nextField->isEmpty())
            if(!(nextField->get()->getID() == 0 && nextField->get()->isWhiteF()!=this->isWhiteF()))
                break;
        nextField = nextField->nextField(dir);
    }
    return tmp;
}
