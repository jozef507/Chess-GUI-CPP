//
// Created by Jozef on 4/21/2019.
//

#include "Field.h"
#include "Figure.h"


/**
 * Inicializuje políčko.
 * @param col Stlpec políčka na šachovnici.
 * @param row Riadok políčka na šachovnici.
 */
Field::Field(int col, int row)
{
    this->col = col;
    this->row = row;
    this->figure = nullptr;
    this->nextFields = new Field*[8];
}


/**
* Deštruktor.
*/
Field::~Field()
{
    delete[] this->nextFields;
}

/**
 * Vráti pozíciu stlpca na šachovnici tohto políčka.
 * @return Hodnotu slpca.
 */
int Field::getColPos()
{
    return this->col;
}

/**
 * Vráti pozíciu riadka na šachovnici tohto políčka.
 * @return Hodnotu riadka.
 */
int Field::getRowPos()
{
    return this->row;
}


/**
 * Pridáva políčku susedné políčko v smere na šachovnici.
 * @param dirs Smer na šachovnici.
 * @param field Plíčko ktoré prídá ako susedné.
 */
void Field::addNextField(Direction dirs, Field *field)
{
    this->nextFields[dirs] = field;
}

/**
 * Vracia susedné políčko tohto políčka v danom smere.
 * @param dirs Smer na šachovnici.
 * @return Odkaz na políčko.
 */
Field *Field::nextField(Direction dirs)
{
    Field *tmp = nextFields[dirs];
    return tmp;
}

/**
 * Testovanie či je dané políčko prázdne.
 * @return Úspešnosť testu.
 */
bool Field::isEmpty()
{
    return (this->figure == nullptr);
}

/**
 * Vráti figúrku ležiacu na danom políčku.
 * @return Odkaz na figúrku.
 */
Figure *Field::get()
{
    Figure *figure = this->figure;
    if (this->isEmpty())
    {
        return nullptr;
    }
    else
    {
        return figure;
    }
}

/**
 * Vloží danú figúrku na toto políčko a testuje úspešnosť tohto úkonu.
 * @param figure Figúrka ktorá má byť vložená na políčko.
 * @return Úspešnosť testu.
 */
bool Field::put(Figure *figure)
{
    if(this->isEmpty())
    {
        this->figure = figure;
        figure->setActualPosition(this);
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Odstráni danú figúrku z tohto políčka a testuje úspešnosť tohto úkonu.
 * @param figure Figúrka ktorá má byť odstránená z políčka.
 * @return Úspešnosť testu.
 */
bool Field::remove(Figure *figure)
{
    if(this->isEmpty())
    {
        return false;
    }
    else
    {
        if(this->figure == figure)
        {
            this->figure = nullptr;
            figure->nulActualPosition();
            return true;
        }
        else
        {
            return false;
        }
    }
}
