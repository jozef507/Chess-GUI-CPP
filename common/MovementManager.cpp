//
// Created by Jozef on 4/24/2019.
//

#include "MovementManager.h"
#include "FiguresManager.h"
#include "Board.h"
#include "NotationMovement.h"
#include "Notation.h"
#include "Figure.h"

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

Field *MovementManager::getStartField() {
    return this->startField;
}

Field *MovementManager::getGoalField() {
    return this->goalField;
}

void MovementManager::changePlayer() {
    this->isWhiteOnTheMove = !isWhiteOnTheMove;
}

void MovementManager::setCanPlayerPlay(bool canPlayerPlay) {
    this->canPlayerPlay = canPlayerPlay;
}

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


Figure *MovementManager::getChangingFigure() {
    return this->changingFigure;
}

Figure *MovementManager::getMovementFigure() {
    return this->movementFigure;
}

Figure *MovementManager::getGoalFieldFigure() {
    return this->goalFieldFigure;
}

bool MovementManager::getIsWhiteOnTheMove() {
    return this->isWhiteOnTheMove;
}

bool MovementManager::getIsMovementCompletlySet() {
    return this->isMovementCompletlySet;
}

bool MovementManager::getIsRemovingFigure() {
    return this->isRemovingFigure;
}

bool MovementManager::getIsChangingFigure() {
    return this->isChangingFigure;
}