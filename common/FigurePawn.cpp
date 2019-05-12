/**
 * Trieda reprezentuje figúrku pešiaka.
 * @author Jozef Ondria
 * @author Jan Holásek
 */

#include <cmath>
#include "FigurePawn.h"
#include "FiguresManager.h"
//#include "Figure.h"


/**
 * Inicializacia pešiaka.
 * @param isWhite Informacia o farbe.
 * @param image Obrázok figúrky používaný v grafickom rozhraní.
 */
FigurePawn::FigurePawn(bool isWhite)
{
    this->ID = 5;
    this->isWhite = isWhite;
    this->firstMovementDone = false;
    this->isRemovingFigure = false;
    this->actField = nullptr;
}


/**
 * Vracia informáciu o tom či je figúrka biela. Ak nie je čierna.
 * @return Pravdivostna hodnota.
 */
bool FigurePawn::isWhiteF()
{
    return this->isWhite;
}


/**
 * Vráti pozíciu aktualnej pozície figúrky.
 * @return Odkaz na políčko.
 */
Field *FigurePawn::getActualField()
{
    return this->actField;
}


/**
 * Nastaví aktuálnu pozíciu figúrky.
 * @param field Políčko pozície na ktorú sa má figurka nastaviť.
 */
void FigurePawn::setActualPosition(Field *field)
{
    this->actField = field;
}


/**
 * Vynulovanie/zrušenie aktualnej pozície figúrky.
 */
void FigurePawn::nulActualPosition()
{
    this->actField = nullptr;
}


/**
 * Vykonáva ťah figúrky a zároveń testuje či je ťah možný.
 * @param moveTo Cieľove políčko ťahu.
 * @param figuresManager Manažer aktívnych figúrok.
 * @return Stav úspešnosti ťahu.
 */
int FigurePawn::move(Field *moveTo, FiguresManager *figuresManager)
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

    if(isOnTheLastField())
    {
        if (flag==1)
            flag = 3;
        else
            flag = 4;
    }

    this->firstMovementDone = true;
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
bool FigurePawn::isMovementPossible(int actCol, int actRow, Field *moveTo, int movetoCol, int movetoRow)
{
    int colDiff = std::abs(movetoCol-actCol);
    int rowDiff = std::abs(movetoRow-actRow);

    if(this->isWhiteF() && this->actField->getRowPos() == 2)
        this->firstMovementDone = false;
    else if(!this->isWhiteF() && this->actField->getRowPos() == 7)
        this->firstMovementDone = false;

    if (colDiff == 0)
    {
        if(!this->firstMovementDone)
        {
            if(rowDiff != 1 && rowDiff != 2)
                return false;
        }
        else
        {
            if(rowDiff != 1)
                return false;
        }


        Field::Direction dir;
        if (this->isWhite)
        {
            if (!(actRow < movetoRow))
                return false;
            dir = Field::Direction::U;
        }
        else
        {
            if (!(actRow > movetoRow))
                return false;
            dir = Field::Direction::D;
        }

        if(!checkDirWithoutRemove(dir, rowDiff))
            return false;
    }
    else if(colDiff==1)
    {
        if(rowDiff!=1)
            return false;

        if (this->isWhite)
        {
            if (!(actRow < movetoRow))
                return false;
        }
        else
        {
            if (!(actRow > movetoRow))
                return false;
        }

        if(moveTo->isEmpty())
            return false;

        Figure *movetoFigure = moveTo->get();
        if(movetoFigure->isWhiteF() == this->isWhiteF())
            return false;

        if(movetoFigure->getID() == 0)
            return false;

        this->isRemovingFigure = true;
    }
    else
    {
        return false;
    }

    return true;
}

bool FigurePawn::checkDirWithoutRemove(Field::Direction dir, int diff)
{
    Field *nextField = this->actField;
    for (int i = 0; i < diff; i++)
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
void FigurePawn::setFieldsInDanger()
{
    this->fieldsInDanger.clear();

    if(this->isWhiteF())
    {
        Field *nextField = this->actField->nextField(Field::Direction::LU);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RU);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
    }
    else
    {
        Field *nextField = this->actField->nextField(Field::Direction::LD);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RD);
        if(nextField!=nullptr)
            this->fieldsInDanger.push_back(nextField);
    }
}


/**
 * Vracia štruktúru políčok ktoré figúrka ohrozuje.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigurePawn::getFieldsInDanger()
{
    return this->fieldsInDanger;
}


/**
 * Vracia id figúrky.
 * @return ID figúrky.
 */
int FigurePawn::getID()
{
    return this->ID;
}


/**
 * Vráti štruktúru všetkych políčok smerujúcich k danému fieldu v parametri.
 * @param field Odkaz na field.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigurePawn::getFieldsOfDirectionToField(Field *field)
{
    if(!(std::find(this->fieldsInDanger.begin(), this->fieldsInDanger.end(), field) != this->fieldsInDanger.end()))
    {
        return {};
    }

    std::vector<Field*> fieldsOfDirToField;
    fieldsOfDirToField.push_back(this->actField);

    return fieldsOfDirToField;

}

bool FigurePawn::isOnTheLastField()
{
    if(this->isWhiteF())
    {
        if(this->actField->getRowPos()==8)
            return true;
    }
    else
    {
        if(this->actField->getRowPos()==1)
            return true;
    }
    return false;
}


/**
 * Vracia štruktúru všetkých políčok ktorými môže ohrozovať súperoveho kráľa.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigurePawn::getFieldsForPossMov()
{
    std::vector<Field*> tmp;
    if (this->isWhiteF()) {
        if (this->firstMovementDone)
        {
            Field *field = this->actField->nextField(Field::Direction::U);
            if (field != nullptr && field->isEmpty())
                tmp.push_back(field);
        }
        else
        {
            Field *field = this->actField->nextField(Field::Direction::U);
            if (field != nullptr && field->isEmpty())
            {
                tmp.push_back(field);
                field = field->nextField(Field::Direction::U);
                if (field != nullptr && field->isEmpty())
                    tmp.push_back(field);
            }
        }
    }
    else
    {
        if (this->firstMovementDone) {
            Field *field = this->actField->nextField(Field::Direction::D);
            if (field != nullptr && field->isEmpty())
                tmp.push_back(field);
        } else {
            Field *field = this->actField->nextField(Field::Direction::D);
            if (field != nullptr && field->isEmpty()) {
                tmp.push_back(field);
                field = field->nextField(Field::Direction::D);
                if (field != nullptr && field->isEmpty())
                    tmp.push_back(field);
            }
        }
    }

    if(this->isWhiteF())
    {
        Field *nextField = this->actField->nextField(Field::Direction::LU);
        if(nextField!= nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RU);
        if(nextField!=nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
    }
    else
    {
        Field *nextField = this->actField->nextField(Field::Direction::LD);
        if(nextField!=nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
        nextField = this->actField->nextField(Field::Direction::RD);
        if(nextField!=nullptr && !nextField->isEmpty())
            tmp.push_back(nextField);
    }

    return tmp;
}


/**
 * Vracia štruktúru všetkých políčok ktorými môže figúrka vytvárať šachmat.
 * @return Štruktúra políčok.
 */
std::vector<Field*> FigurePawn::getFieldsInDangerChesMat()
{
    return this->fieldsInDanger;
}


