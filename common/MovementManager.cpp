//
// Created by Jozef on 4/24/2019.
//

#include "MovementManager.h"

MovementManager::MovementManager(Board *board)
{
    this->board = board;
    this->canPlayerPlay = true;
    this->isWhiteOnTheMove = true;
    this->startField = nullptr;
    this->movementFigure = nullptr;
    this->goalField = nullptr;
    this->goalFieldFigure = nullptr;
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
    this->startField = nullptr;
    this->movementFigure = nullptr;
    this->goalField = nullptr;
    this->goalFieldFigure = nullptr;
}

bool MovementManager::setMovement(int col, int row) {
    if (!canPlayerPlay) {
        return false;
    }

    if (this->startField == nullptr) {
        this->startField = this->board->getField(col, row);
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
        this->goalField = this->board->getField(col, row);
        if (!this->goalField->isEmpty())
            this->goalFieldFigure = goalField->get();
        return true;
    }
}

int MovementManager::performMovement() {
    if (this->startField != nullptr && this->movementFigure != nullptr && this->goalField != nullptr) {
        return (this->movementFigure->move(this->goalField));
    } else {
        return 0;
    }
}

Figure *MovementManager::getMovementFigure() {
    return this->movementFigure;
}

Figure *MovementManager::getGoalFieldFigure() {
    return this->goalFieldFigure;
}

bool MovementManager::isWhiteOnTheMoveF() {
    return this->isWhiteOnTheMove;
}