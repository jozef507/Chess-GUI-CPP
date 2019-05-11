//
// Created by Jozef on 4/24/2019.
//

#include "MovementManager.h"
#include "FiguresManager.h"
#include "Board.h"
#include "NotationMovement.h"
#include "Notation.h"
#include "Figure.h"


/**
 * Inicializuje ťah partie.
 */
MovementManager::MovementManager()
{
    this->canPlayerPlay = true;
    this->isWhiteOnTheMove = true;
    this->isMovementCompletlySet = false;
    this->isRemovingFigure = false;
    this->isChangingFigure = false;

    this->startField = nullptr;
    this->movementFigure = nullptr;
    this->goalField = nullptr;
    this->goalFieldFigure = nullptr;
    this->changingFigure = nullptr;
}


/**
 * Vracia štartovacie políčko ťahu.
 * @return Odkaz na políčko.
 */
Field *MovementManager::getStartField() {
    return this->startField;
}


/**
* Vracia štartovacie políčko ťahu.
* @return Odkaz na štartovacie políčko.
*/
Field *MovementManager::getGoalField() {
    return this->goalField;
}


/**
 * Zmení hráča, ktorý je na ťahu.
 */
void MovementManager::changePlayer() {
    this->isWhiteOnTheMove = !isWhiteOnTheMove;
}


/**
 * Nastaví informáciu o tom či môže užívateľ previesť vlastný ťah.
 * @param canPlayerPlay
 */
void MovementManager::setCanPlayerPlay(bool canPlayerPlay) {
    this->canPlayerPlay = canPlayerPlay;
}


/**
  * Vynuluje informácie o ťahu a tým prípráví aplikáciu na ďalší ťah.
  */
void MovementManager::nullMovementManager() {
    this->isMovementCompletlySet = false;
    this->isRemovingFigure = false;
    this->isChangingFigure = false;

    this->startField = nullptr;
    this->movementFigure = nullptr;
    this->goalField = nullptr;
    this->goalFieldFigure = nullptr;
    this->changingFigure = nullptr;
}


/**
 * Nastavuje ťah ktorý sa má vykonať. Nastavuje štartovacie a cieľove políčko.
 * Ak je ťah vynulovaný a povola sa metóda tak sa nastaví štartovacie políčko ak nie nastavuje
 * sa cieľové políčko.
 * @param col Stlpec políčka.
 * @param row Riadok políčka.
 * @param board Šachovníca.
 * @return Úspešnosť nastavenia.
 */
bool MovementManager::setPlayerMovement(int col, int row, Board *board) {
    if (!canPlayerPlay) {
        return false;
    }

    if(this->isChangingFigure)
    {
        return false;
    }

    if (this->startField == nullptr) {
        this->startField = board->getField(col, row);
        if (this->startField->isEmpty()) {
            this->nullMovementManager();
            return false;
        }

        this->movementFigure = this->startField->get();
        if (this->movementFigure->isWhiteF() != this->isWhiteOnTheMove) {
            this->nullMovementManager();
            return false;
        }
        return true;
    } else {
        this->goalField = board->getField(col, row);
        if (!this->goalField->isEmpty())
            this->goalFieldFigure = goalField->get();
        this->isMovementCompletlySet = true;
        return true;
    }
}


/**
 * Vykoná už nastavený ťah prostredníctvom rozhrania na figúrku ktorý sa má presúvať.
 * Následne otestuje návratovú hodnotu od figúrky a nastavý ďalšie dôležíte informácie o ťahu.
 * @param figuresManager Manažer aktívnych figúrok.
 * @return Úspešnosť ťahu.
 */
bool MovementManager::performMovement(FiguresManager *figuresManager) {
    if (this->startField != nullptr && this->movementFigure != nullptr && this->goalField != nullptr)
    {
        int flag = this->movementFigure->move(this->goalField, figuresManager);
        if(flag==-1)
        {
            return false;
        }
        else if(flag == 1)
        {
            return true;
        }
        else if(flag == 2)
        {
            this->isRemovingFigure = true;
            return true;
        }
        else if(flag == 3)
        {
            this->isChangingFigure = true;
            return true;
        }
        else if(flag == 4)
        {
            this->isChangingFigure = true;
            this->isRemovingFigure = true;
            return true;
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
}


/**
 * Nastavuje prehrávaný ťah ktorý sa má vykonať. Nastavuje štartovacie a cieľove políčko.
 * Ak je ťah vynulovaný a povola sa metóda tak sa nastaví štartovacie políčko ak nie nastavuje
 * sa cieľové políčko. Tieto políčka sa získavajú z notácie šachovej partie.
 * @param board Šachovnica.
 * @param notation Notácia partie.
 * @param figuresManager Manažer aktívnych figúrok.
 * @return Úspešnosť nastavenia.
 */
bool MovementManager::setPlaybackMovement(Board *board, Notation *notation, FiguresManager *figuresManager)
{
    if(this->isChangingFigure)
        return false;

    NotationMovement *mov = notation->getActualNotMov();

    this->goalField = board->getField(mov->getGoalFieldCol(), mov->getGoalFieldRow());
    if (!this->goalField->isEmpty())
        this->goalFieldFigure = goalField->get();

    if((mov->getIsLongNotation()) || (!mov->getIsLongNotation() && mov->getStartFieldCol() != -1 && mov->getStartFieldRow() != -1))
    {
        this->startField = board->getField(mov->getStartFieldCol(),mov->getStartFieldRow());
    }
    else
    {
        int movementFigureID = mov->getMovementFigureID();
        std::vector<Figure*> activeFigures;
        if(this->isWhiteOnTheMove)
            activeFigures = figuresManager->getActiveWhiteFigures();
        else
            activeFigures = figuresManager->getActiveBlackFigures();

        std::vector<Figure*> tmpFigures;
        int ID = -1;
        std::vector<Field*> tmpFields;
        for (int i = 0; i<(int)activeFigures.size(); i++)
        {
            ID = activeFigures.at((unsigned long)i)->getID();
            tmpFields = activeFigures.at((unsigned long)i)->getFieldsForPossMov();

            if(ID == movementFigureID
                && std::find(tmpFields.begin(), tmpFields.end(), this->goalField) != tmpFields.end())
            {
                tmpFigures.push_back(activeFigures.at((unsigned long)i));
            }
        }

        if(tmpFigures.size()==1)
            this->startField = tmpFigures.at(0)->getActualField();
        else if(tmpFigures.size()>1)
        {
            if(mov->getStartFieldCol() != -1)
            {
                for (int i = 0; i<(int)tmpFigures.size(); i++)
                {
                    if(mov->getStartFieldCol() == tmpFigures.at((unsigned long)i)->getActualField()->getColPos())
                    {
                        this->startField = tmpFigures.at((unsigned long)i)->getActualField();
                        break;
                    }
                }
            }
            else if(mov->getStartFieldRow() != -1)
            {
                for (int i = 0; i<(int)tmpFigures.size(); i++)
                {
                    if(mov->getStartFieldRow() == tmpFigures.at((unsigned long)i)->getActualField()->getRowPos())
                    {
                        this->startField = tmpFigures.at((unsigned long)i)->getActualField();
                        break;
                    }
                }
            }
        }
    }

    if (this->startField->isEmpty())
    {
        this->nullMovementManager();
        return false;
    }

    this->movementFigure = this->startField->get();
    if (this->movementFigure->isWhiteF() != this->isWhiteOnTheMove) {
        this->nullMovementManager();
        return false;
    }

    this->isMovementCompletlySet = true;
    return true;
}


/**
  * Nastaví prehravaný ťah do predu. Informácie o ťahu sa získavajú z notácie partie.
  * @param mov Ťah repretentovaný notáciou.
  * @param board Šachovnica.
  * @param figuresManager Manažer aktívných figúrok.
  * @return Úspešnosť nastavenia.
  */
bool MovementManager::setPlaybackUndoMovement(NotationMovement *mov, Board *board, FiguresManager *figuresManager)
{
    this->startField = board->getField(mov->getStartFieldCol(), mov->getStartFieldRow());
    this->goalField = board->getField(mov->getGoalFieldCol(), mov->getGoalFieldRow());
    if(mov->getChangingFigureID()!=-1)
    {
        this->movementFigure = figuresManager->getLastChangedFigure();
        figuresManager->removeLastChangedFigure();
        this->changingFigure = this->goalField->get();
        this->isChangingFigure = true;
    }
    else
    {
        this->movementFigure = goalField->get();
    }

    this->isWhiteOnTheMove = this->movementFigure->isWhiteF();

    if(mov->getIsFigureRemoving())
    {
        this->goalFieldFigure = figuresManager->getLastRemovedFigure();
        figuresManager->removeLastRemovedFigure();
        this->isRemovingFigure = true;
    }

    this->isWhiteOnTheMove = this->movementFigure->isWhiteF();
    return true;
}


/**
 * Vykoná už nastavený ťah dozadu.
 * @param mov Ťah reprezentovaný notáciou.
 * @param figuresManager Manažer aktívnych figúrok.
 * @return Úspešnosť ťahu.
 */
bool MovementManager::performPlaybackUndoMovement(NotationMovement *mov, FiguresManager *figuresManager)
{
    if(this->isChangingFigure)
    {
        this->goalField->remove(this->changingFigure);
        figuresManager->removeActiveFigure(this->changingFigure);
        delete this->changingFigure;

        this->startField->put(this->movementFigure);
        figuresManager->addActiveFigure(this->movementFigure);
    }
    else
    {
        this->goalField->remove(this->movementFigure);
        this->startField->put(this->movementFigure);
    }


    if(this->isRemovingFigure)
    {
        this->goalField->put(this->goalFieldFigure);
        figuresManager->addActiveFigure(this->goalFieldFigure);
    }

    figuresManager->setChessMat(false);
    return true;

}



/**
 * Vracia figúrku ktorá nahrádza pešiaka.
 * @return Odkaz na figúrku.
 */
Figure *MovementManager::getChangingFigure() {
    return this->changingFigure;
}


/**
 * Vracia figúrku ktorej ťah sa vykonáva.
 * @return Odkaz na figúrku.
 */
Figure *MovementManager::getMovementFigure() {
    return this->movementFigure;
}


/**
 * Vracia figúrku ktorej ťah sa vykonáva.
 * @return Odkaz na figúrku.
 */
Figure *MovementManager::getGoalFieldFigure() {
    return this->goalFieldFigure;
}


/**
 * Vracia informáciu o tom či je na ťahu práve biely hráč.
 * @return Pravdivostna informácia.
 */
bool MovementManager::getIsWhiteOnTheMove() {
    return this->isWhiteOnTheMove;
}


/**
 * Vracia informáciu o tom či je ťah kompletne nastavený (či už je nastavené aj cieľové políčko).
 * @return Pravdivostna informácia.
 */
bool MovementManager::getIsMovementCompletlySet() {
    return this->isMovementCompletlySet;
}


/**
 * Vracia informáciu o tom či dochádza k vyhodeniu figúrky.
 * @return Pravdivostna informácia.
 */
bool MovementManager::getIsRemovingFigure() {
    return this->isRemovingFigure;
}


/**
 * Vracia informáciu o tom či dochádza k zámene pešiaka.
 * @return Pravdivostna informácia.
 */
bool MovementManager::getIsChangingFigure() {
    return this->isChangingFigure;
}