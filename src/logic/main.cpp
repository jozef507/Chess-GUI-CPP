#include <iostream>
#include "Board.h"
#include "FigurePawn.h"
#include "Game.h"
#include "GameChess.h"
using namespace std;
/*
// Base class
class Shape{
public:
    virtual int getArea()=0;
    virtual void setWidth(int w) = 0;
    virtual void setHeight(int h) = 0;
    bool isEmpty();
};

// Derived classes
class Rectangle: public Shape {
public:
    int getArea() {
        return (width * height);
    }

    void setWidth(int w) {
        width = w;
    }

    void setHeight(int h) {
        height = h;
    }

protected:
    int width;
    int height;

};

class Triangle: public Shape {
public:

    Triangle(int width, int height, Rectangle *rect)
    {
        this->height = height;
        this->width = width;
        this->rect = rect;
    }

    int getArea() {
        if(this->rect == nullptr)
        {
            return (width * height)/2;
        } else
        {
            this->rect->setHeight(4);
            this->rect->setWidth(4);
            return this->rect->getArea();
        }
    }

    void setWidth(int w) {
        width = w;
    }

    void setHeight(int h) {
        height = h;
    }

    void nulRect()
    {
        this->rect = nullptr;
    }

protected:
    Rectangle *rect;

protected:
    int width;
    int height;

};
*/
int main(void)
{


    Game *game = new GameChess("C:\\Users\\Jozef\\Desktop\\subor2.txt");
    for (int i = 0; i < 77; ++i) {
        game->setPlaybackMovement();
        game->performPlaybackMovement();
        if(game->getIsChangingFigure())
        {
            game->createNewFigure(game->getChangingFigureID());
        }
        game->incrementIndexOfNotationLines();
        game->completeNotationMovement();
        game->nullMovementManager();
        game->changePlayer();
    }


    for (int i = 76; i >=39; --i) {
        game->setPlaybackUndoMovement();
        game->performPlaybackUndoMovement();
        game->decrementIndexOfNotationLines();
        game->nullMovementManager();
    }


    game->setPlayerMovement(3,4);
    game->setPlayerMovement(2,3);
    bool movement = game->performPlayerMovement();

    game->addPlayerNotationMovement();
    game->completeNotationMovement();
    game->nullMovementManager();
    game->changePlayer();


    game->setPlayerMovement(6,1);
    game->setPlayerMovement(2,1);
    movement = game->performPlayerMovement();

    game->addPlayerNotationMovement();
    game->completeNotationMovement();
    game->nullMovementManager();
    game->changePlayer();

    delete game;

}