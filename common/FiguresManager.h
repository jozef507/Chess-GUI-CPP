//
// Created by Jozef on 5/3/2019.
//

#ifndef ICP_FIGURESMANAGER_H
#define ICP_FIGURESMANAGER_H


#include <vector>

class FigureKing;
class Figure;
class Field;

class FiguresManager
{
private:
    bool chessMat;
    FigureKing *whiteKing;
    FigureKing *blackKing;

    std::vector<Figure*> activeWhiteFigures;
    std::vector<Figure*> activeBlackFigures;
    std::vector<Figure*> removedFigures;
    std::vector<Figure*> changedFigures;

    std::vector<Field*> whiteFieldsInDanger;
    std::vector<Field*> blackFieldsInDanger;

public:
    FiguresManager();
    ~FiguresManager();

    bool updateFigures(bool whiteOnTheMove, Figure *movingFigure, Figure *removedFigure);
    void addActiveFigure(Figure *figure);
    void addRemovedFigure(Figure *figure);
    void addChangedFigure(Figure *figure);
    void setWhiteFieldsInDanger();
    void setBlackFieldsInDanger();
    std::vector<Field*> getWhiteFieldsInDangerWithoutKing();
    std::vector<Field*> getBlackFieldsInDangerWithoutKing();
    bool checkChess(Figure *movingFigure);
    bool checkChessMat(bool isWhiteOnTheMove);
    void setKing(FigureKing *king);
    bool getChess();
    bool getChessMat();
    Figure *getLastChangedFigure ();
    void removeLastChangedFigure ();
    std::vector<Figure*> getActiveWhiteFigures ();
    std::vector<Figure*> getActiveBlackFigures ();
    Figure *getLastRemovedFigure();
    void removeLastRemovedFigure();
    void removeActiveFigure(Figure *figure);
    void setChessMat(bool is);
};


#endif //ICP_FIGURESMANAGER_H
