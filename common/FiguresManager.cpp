/**
 * Trieda reprezentuje manažéra pre aktívne/pasívne figúrky.
 * @author Jozef Ondria
 * @author Jan Holásek
 */


#include <iostream>
#include "FiguresManager.h"
#include "Figure.h"
#include "FigureKing.h"

/**
 * Inicializace objektu.
 */
FiguresManager::FiguresManager()
{
    this->chessMat = false;
}

/**
 * Deštruktor.
 */
FiguresManager:: ~FiguresManager()
{
    int length = this->activeWhiteFigures.size();
    Figure *figure;
    for (int i = length-1; i >= 0; --i)
    {
        figure = this->activeWhiteFigures.back();
        this->activeWhiteFigures.pop_back();
        delete figure;
    }

    length = this->activeBlackFigures.size();
    figure = nullptr;
    for (int i = length-1; i >= 0; --i)
    {
        figure = this->activeBlackFigures.back();
        this->activeBlackFigures.pop_back();
        delete figure;
    }

    length = this->removedFigures.size();
    figure = nullptr;
    for (int i = length-1; i >= 0; --i)
    {
        figure = this->removedFigures.back();
        this->removedFigures.pop_back();
        delete figure;
    }

    length = this->changedFigures.size();
    figure = nullptr;
    for (int i = length-1; i >= 0; --i)
    {
        figure = this->changedFigures.back();
        this->changedFigures.pop_back();
        delete figure;
    }
}


/**
 * Základná metoda tejto triedy, volaná po uskutočnení každého ťahu. Jej úlohou je aktualizovať
 * štruktúry aktívnych/pasívnych figúrok ale najmä aktualizovať štruktúry pre políčka v ohrození požívajuce
 * sa na detekciu šachu a šachmatu.
 * @param whiteOnTheMove Informácia o tom ktorý hráč je na ťahu.
 * @param movingFigure Odkaz na figúrku ktorá sa pri ťahu presúva.
 * @param removedFigure Odkaz na figúrku ktorý bola vyhodená.
 * @return Úspešnosť operácie.
 */
bool FiguresManager::updateFigures(bool whiteOnTheMove, Figure *movingFigure, Figure *removedFigure)
{
    std::vector<Figure*> tmpActiveWhiteFigures(this->activeWhiteFigures);
    std::vector<Figure*> tmpActiveBlackFigures(this->activeBlackFigures);
    std::vector<Figure*> tmpRemovedFigures(this->removedFigures);
    std::vector<Field*> tmpWhiteFieldsInDanger(this->whiteFieldsInDanger);
    std::vector<Field*> tmpBlackFieldsInDanger(this->blackFieldsInDanger);

    if(removedFigure != nullptr)
    {
        this->addRemovedFigure(removedFigure);
    }

    this->setWhiteFieldsInDanger();
    this->setBlackFieldsInDanger();

    bool chess;
    if(whiteOnTheMove)
    {
        Field *kingField = this->whiteKing->getActualField();
        if (std::find(this->blackFieldsInDanger.begin(), this->blackFieldsInDanger.end(), kingField) != this->blackFieldsInDanger.end())
            chess = true;
        else
            chess = false;
    }
    else
    {
        Field *kingField = this->blackKing->getActualField();
        if (std::find(this->whiteFieldsInDanger.begin(), this->whiteFieldsInDanger.end(), kingField) != this->whiteFieldsInDanger.end())
            chess = true;
        else
            chess = false;
    }

    if(chess)
    {
        this->activeWhiteFigures = tmpActiveWhiteFigures;
        this->activeBlackFigures = tmpActiveBlackFigures;
        this->removedFigures = tmpRemovedFigures;
        this->whiteFieldsInDanger = tmpWhiteFieldsInDanger;
        this->blackFieldsInDanger = tmpBlackFieldsInDanger;
        return false;
    }

    if (this->checkChess(movingFigure))
    {
        this->checkChessMat(whiteOnTheMove);
    }

    return true;

}


/**
 * Pridá figúrku figure do štruktúry aktívnych figúrok podľa jej farby.
 * @param figure
 */
void FiguresManager::addActiveFigure(Figure *figure)
{
    if (figure->isWhiteF())
        this->activeWhiteFigures.push_back(figure);
    else
        this->activeBlackFigures.push_back(figure);
}


/**
 * Pridá vyhodenú figúrku figure do štruktúry pre vyhodené figúrky.
 * @param figure
 */
void FiguresManager::addRemovedFigure(Figure *figure)
{
    if (figure->isWhiteF())
    {
        if (std::find(this->activeWhiteFigures.begin(), this->activeWhiteFigures.end(), figure) != this->activeWhiteFigures.end())
        {
            this->activeWhiteFigures.erase(std::remove(this->activeWhiteFigures.begin(), this->activeWhiteFigures.end(), figure), this->activeWhiteFigures.end());;
            this->removedFigures.push_back(figure);
        }
    }
    else
    {
        if (std::find(this->activeBlackFigures.begin(), this->activeBlackFigures.end(), figure) != this->activeBlackFigures.end())
        {
            this->activeBlackFigures.erase(std::remove(this->activeBlackFigures.begin(), this->activeBlackFigures.end(), figure), this->activeBlackFigures.end());;
            this->removedFigures.push_back(figure);
        }
    }
}


/**
  * Pridá zamenenú figúruku(pešiaka) figure do štruktúry pre zamenené figúrky.
  * @param figure
  */
void FiguresManager::addChangedFigure(Figure *figure)
{
    if (figure->isWhiteF())
    {
        if (std::find(this->activeWhiteFigures.begin(), this->activeWhiteFigures.end(), figure) != this->activeWhiteFigures.end())
        {
            this->activeWhiteFigures.erase(std::remove(this->activeWhiteFigures.begin(), this->activeWhiteFigures.end(), figure), this->activeWhiteFigures.end());;
            this->changedFigures.push_back(figure);
        }
    }
    else
    {
        if (std::find(this->activeBlackFigures.begin(), this->activeBlackFigures.end(), figure) != this->activeBlackFigures.end())
        {
            this->activeBlackFigures.erase(std::remove(this->activeBlackFigures.begin(), this->activeBlackFigures.end(), figure), this->activeBlackFigures.end());;
            this->changedFigures.push_back(figure);
        }
    }
}


/**
 * Nastaví/aktualizuje štruktúru ohrozených políčok bielymi figúrkami.
 */
void FiguresManager::setWhiteFieldsInDanger()
{
    this->whiteFieldsInDanger.clear();
    int length = (int) this->activeWhiteFigures.size();
    Figure *tmpFigure;
    for(int i = 0; i < length; i++)
    {
        tmpFigure = this->activeWhiteFigures.at((unsigned long)i);
        tmpFigure->setFieldsInDanger();
        std::vector<Field*> tmpFields = tmpFigure->getFieldsInDanger();
        this->whiteFieldsInDanger.insert(std::end(this->whiteFieldsInDanger), std::begin(tmpFields), std::end(tmpFields));
    }
}


/**
 * Nastaví/aktualizuje štruktúru ohrozených políčok čiernymi figúrkami.
 */
void FiguresManager::setBlackFieldsInDanger()
{
    this->blackFieldsInDanger.clear();
    int length = (int) this->activeBlackFigures.size();
    Figure *tmpFigure;
    for(int i = 0; i < length; i++)
    {
        tmpFigure = this->activeBlackFigures.at((unsigned long)i);
        tmpFigure->setFieldsInDanger();
        std::vector<Field*> tmpFields = tmpFigure->getFieldsInDanger();
        this->blackFieldsInDanger.insert(std::end(this->blackFieldsInDanger), std::begin(tmpFields), std::end(tmpFields));
    }
}


/**
 * Nastaví/aktualizuje štruktúru ohrozených políčok bielymi figúrkami okrem bieleho kráľa.
 * @return
 */
std::vector<Field*> FiguresManager::getWhiteFieldsInDangerWithoutKing()
{
    std::vector<Field*> whiteFieldsInDangerWithoutKing;
    int length = (int) this->activeWhiteFigures.size();
    Figure *tmpFigure;
    for(int i = 0; i < length; i++)
    {
        tmpFigure = this->activeWhiteFigures.at((unsigned long)i);

        if(tmpFigure->getID()!=0)
        {
            tmpFigure->setFieldsInDanger();
            std::vector<Field*> tmpFields = tmpFigure->getFieldsInDanger();
            whiteFieldsInDangerWithoutKing.insert(std::end(whiteFieldsInDangerWithoutKing), std::begin(tmpFields), std::end(tmpFields));
        }
    }
    return whiteFieldsInDangerWithoutKing;
}


/**
* Nastaví/aktualizuje štruktúru ohrozených políčok čiernymi figúrkami okrem čierneho kráľa.
* @return
*/
std::vector<Field*> FiguresManager::getBlackFieldsInDangerWithoutKing()
{
    std::vector<Field*> blackFieldsInDangerWithoutKing;
    int length = (int) this->activeBlackFigures.size();
    Figure *tmpFigure;
    for(int i = 0; i < length; i++)
    {
        tmpFigure = this->activeBlackFigures.at((unsigned long)i);

        if(tmpFigure->getID()!=0)
        {
            tmpFigure->setFieldsInDanger();
            std::vector<Field*> tmpFields = tmpFigure->getFieldsInDanger();
            blackFieldsInDangerWithoutKing.insert(std::end(blackFieldsInDangerWithoutKing), std::begin(tmpFields), std::end(tmpFields));
        }
    }
    return blackFieldsInDangerWithoutKing;
}


/**
 * Metóda kontroluje či je prítomny na šachovnici šach.
 * @param isWhiteOnTheMove Hrač na ťahu.
 * @param movingFigure Presúvaná figúrka.
 * @return Výsledok kontroly.
 */
bool FiguresManager::checkChess(Figure *movingFigure)
{
    Field *kingFieldBlack = this->blackKing->getActualField();
    if (std::find(this->whiteFieldsInDanger.begin(), this->whiteFieldsInDanger.end(), kingFieldBlack) != this->whiteFieldsInDanger.end())
    {
        this->blackKing->setInChess(true);
        this->blackKing->setChessBy(movingFigure);
        return true;
    }
    else
    {
        this->blackKing->setInChess(false);
        this->blackKing->setChessBy(nullptr);
    }


    Field *kingFieldWhite = this->whiteKing->getActualField();
    if (std::find(this->blackFieldsInDanger.begin(), this->blackFieldsInDanger.end(), kingFieldWhite) != this->blackFieldsInDanger.end())
    {
        this->whiteKing->setInChess(true);
        this->whiteKing->setChessBy(movingFigure);
        return true;
    }
    else
    {
        this->whiteKing->setInChess(false);
        this->whiteKing->setChessBy(nullptr);
    }
    return false;
}


/**
 * Metóda kontroluje či momentálny stav na šachovnici nespôsobuje šach mat.
 * @param isWhiteOnTheMove Hráč na ťahu.
 * @return Výsledok kotnroly.
 */
bool FiguresManager::checkChessMat(bool isWhiteOnTheMove)
{
    if(isWhiteOnTheMove)
    {
        std::vector<Field*> whiteFieldsInDangerChessMat;
        std::vector<Field*> tmpFieldsInDanger;
        Figure *tmpFigure;
        for(int i = 0; i < (int)this->activeWhiteFigures.size(); i++)
        {
            tmpFigure = this->activeWhiteFigures.at((unsigned long)i);
            /*tmpFieldsInDanger = tmpFigure->getFieldsInDangerChesMat();
            if(!tmpFieldsInDanger.empty())
            {
                for (int j = 0; j < tmpFieldsInDanger.size(); ++j)
                {
                    whiteFieldsInDangerChessMat.push_back(tmpFieldsInDanger.at(j));
                }
            }*/
            tmpFieldsInDanger = tmpFigure->getFieldsInDangerChesMat();
            whiteFieldsInDangerChessMat.insert(std::end(whiteFieldsInDangerChessMat), std::begin(tmpFieldsInDanger), std::end(tmpFieldsInDanger));
        }

        if(this->blackKing->canMove(whiteFieldsInDangerChessMat))
        {
            this->chessMat = false;
            return false;
        }
        else
        {
            std::vector<Field*> fieldsInChessDir = this->blackKing->getChessBy()->getFieldsOfDirectionToField(this->blackKing->getActualField());
            std::vector<Field*> blackFieldsInDangerWithoutKing = this->getBlackFieldsInDangerWithoutKing();

            int length = (int)fieldsInChessDir.size();
            bool chessmatFlag = true;
            for (int i = 0; i<length; i++)
            {
                Field *field = fieldsInChessDir.at((unsigned long)i);
                if (std::find(blackFieldsInDangerWithoutKing.begin(), blackFieldsInDangerWithoutKing.end(), field) != blackFieldsInDangerWithoutKing.end())
                {
                    int fieldOccurrences = (int)count(blackFieldsInDangerWithoutKing.begin(), blackFieldsInDangerWithoutKing.end(), field);
                    int pawnOccurrences = 0;

                    Field *nextField = field->nextField(Field::Direction::LU);
                    if(nextField!= nullptr)
                        if(nextField->get()!= nullptr && nextField->get()->getID()==5)
                            pawnOccurrences++;

                    nextField = field->nextField(Field::Direction::RU);
                    if(nextField!= nullptr)
                        if(nextField->get()!= nullptr && nextField->get()->getID()==5)
                            pawnOccurrences++;

                    if(fieldOccurrences == pawnOccurrences)
                        continue;
                    chessmatFlag = false;
                }
            }

            if(chessmatFlag)
            {
                std::cout << "--------------------------------------------" << std::endl;
                this->chessMat=true;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        std::vector<Field*> blackieldsInDangerChessMat;
        std::vector<Field*> tmpFieldsInDanger;
        Figure *tmpFigure;
        for(int i = 0; i < activeBlackFigures.size(); i++)
        {
            tmpFigure = activeBlackFigures.at((unsigned long)i);
            /*tmpFieldsInDanger = tmpFigure->getFieldsInDangerChesMat();
            if(!tmpFieldsInDanger.empty())
            {
                for (int j = 0; j < tmpFieldsInDanger.size(); ++j)
                {
                    blackieldsInDangerChessMat.push_back(tmpFieldsInDanger.at(j));
                }
            }*/
            tmpFieldsInDanger = tmpFigure->getFieldsInDangerChesMat();
            blackieldsInDangerChessMat.insert(std::end(blackieldsInDangerChessMat), std::begin(tmpFieldsInDanger), std::end(tmpFieldsInDanger));
        }

        if(this->whiteKing->canMove(blackieldsInDangerChessMat))
        {
            this->chessMat = false;
            return false;
        }
        else
        {
            std::vector<Field*> fieldsInChessDir = this->whiteKing->getChessBy()->getFieldsOfDirectionToField(this->whiteKing->getActualField());
            std::vector<Field*> whiteFieldsInDangerWithoutKing = this->getWhiteFieldsInDangerWithoutKing();

            int length = (int) fieldsInChessDir.size();
            bool chessmatFlag = true;
            for (int i = 0; i<length; i++)
            {
                Field *field = fieldsInChessDir.at((unsigned long)i);
                if (std::find(whiteFieldsInDangerWithoutKing.begin(), whiteFieldsInDangerWithoutKing.end(), field) != whiteFieldsInDangerWithoutKing.end())
                {
                    int fieldOccurrences = (int)count(whiteFieldsInDangerWithoutKing.begin(), whiteFieldsInDangerWithoutKing.end(), field);
                    int pawnOccurrences = 0;

                    Field *nextField = field->nextField(Field::Direction::LD);
                    if(nextField!=nullptr)
                        if(nextField->get() != nullptr && nextField->get()->getID()==5)
                            pawnOccurrences++;

                    nextField = field->nextField(Field::Direction::RD);
                    if(nextField!=nullptr)
                        if(nextField->get() != nullptr && nextField->get()->getID()==5)
                            pawnOccurrences++;

                    if(fieldOccurrences == pawnOccurrences)
                        continue;
                    chessmatFlag = false;
                }
            }

            if(chessmatFlag)
            {
                std::cout << "--------------------------------------------" << std::endl;
                this->chessMat = true;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}


/**
 * Nastaví člena/premennu tejto triedy kráľa na kráľa daného parametrom.
 * @param king Kráľ ktorý má byť priradený objektu.
 */
void FiguresManager::setKing(FigureKing *king)
{
    if(king->isWhiteF())
    {
        this->whiteKing = king;
    }
    else
    {
        this->blackKing = king;
    }
}


/**
 * Vracia informáciu o tom či je na šachovnici stav - šachmat.
 * @return Pravdivostná hodnota.
 */
bool FiguresManager::getChess()
{
    return  this->whiteKing->getInChess() || this->blackKing->getInChess();
}


/**
 * Vracia informáciu o tom či je na šachovnici stav - šachmat.
 * @return Pravdivostná hodnota.
 */
bool FiguresManager::getChessMat()
{
    return this->chessMat;
}


/**
  * Vráti poslednú figúrku priradenú do štruktúry - zamenené figúrky.
  * @return Odkaz na figúrku.
  */
Figure *FiguresManager::getLastChangedFigure ()
{
    return this->changedFigures.back();
}


/**
 * Odstráni poseldnú figúrku zo štruktúry - zamenené figúrky.
 */
void FiguresManager::removeLastChangedFigure ()
{
    this->changedFigures.pop_back();
}


/**
 * Vráti štruktúru aktívnych bielych figúrok.
 * @return Štruktúru figúrok.
 */
std::vector<Figure*> FiguresManager::getActiveWhiteFigures ()
{
    return this->activeWhiteFigures;
}


/**
 * Vráti štruktúru aktívnych čiernych figúrok.
 * @return Štruktúru figúrok.
 */
std::vector<Figure*> FiguresManager::getActiveBlackFigures ()
{
    return this->activeBlackFigures;
}


/**
 * Vráti poslednú figúrku priradenú do štruktúry - vyhodené figúrky.
 * @return Odkaz na figúrku.
 */
Figure *FiguresManager::getLastRemovedFigure()
{
    return this->removedFigures.back();
}


/**
 * Odstráni poseldnú figúrku zo štruktúry - vyhodené figúrky.
 */
void FiguresManager::removeLastRemovedFigure()
{
    this->removedFigures.pop_back();

}


/**
 * Odstráni z aktívnych figúrok figurkú danú parametrom.
 * @param figure Odkaz na danú figúrku.
 */
void FiguresManager::removeActiveFigure(Figure *figure)
{
    if(figure->isWhiteF())
        this->activeWhiteFigures.erase(std::remove(this->activeWhiteFigures.begin(), this->activeWhiteFigures.end(), figure), this->activeWhiteFigures.end());
    else
        this->activeBlackFigures.erase(std::remove(this->activeBlackFigures.begin(), this->activeBlackFigures.end(), figure), this->activeBlackFigures.end());;
}


/**
 * Nastaví člena tiredy šachmat podľa daného parametru.
 * @param is Pravdivostná hotnota.
 */
void FiguresManager::setChessMat(bool is)
{
    this->chessMat = is;
}