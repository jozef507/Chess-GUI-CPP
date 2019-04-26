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
int main(void) {
/*
    Rectangle Rect;
    Triangle  tri(5,7, &Rect);
    Triangle *tri1 = new Triangle(5,5, &Rect);
    Shape *s;
    s = tri1;

    Rect.setWidth(5);
    Rect.setHeight(7);

    // Print the area of the object.
    cout << "Total Rectangle area: " << Rect.getArea() << endl;


    // Print the area of the object.
    cout << "Total Triangle area: " << (*s).getArea() << endl;

    tri.nulRect();
    cout << "Total Triangle area: " << (*s).getArea() << endl;

    cout << "Total Rectangle area: " << Rect.getArea() << endl;

    //return 0;
*/
    /*Board *board = new Board(8);
    Board *board1 = new Board(8);
    Field *i = board->getField(1,1);
    Field *j = board->getField(8,8);
    Field *k = board1->getField(1,1);
    Field *l = board1->getField(8,8);

    FigurePawn *figurePawn = new FigurePawn(true);
    Figure *figure = figurePawn;

    bool apo = i->isEmpty();
    i->put(figure);
    apo = i->isEmpty();

    delete board;
    delete board1;
    ;*/

    Game *game = new GameChess();
    Field *i = game->getField(1,8);
    Field *j = game->getField(2,8);
    Field *k = game->getField(3,8);
    Field *l = game->getField(4,8);


    game->setMovement(1,2);
    game->setMovement(1,3);
    int movement = game->performMovement();

    delete game;

}