#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>

#include "chesstypes.h"
#include "../logic/QtGame.h"

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:

    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();

    void setGame(QtGame* newGame);

    int heightForWidth(int w) const;

    void moveFigure(int srcX, int srcY, int dstX, int dstY);
    void changeFigure(FigureType type, TeamColor color, int posX, int posY);
    void updateBoard();
    void updatePosition(int posX, int posY);

private:
    Ui::BoardWidget *ui;

    double boardSize = 1000;
    double boardBorderSize = 47 + 3; // border + offset for position correction
    double boardSquareSize = 113.25;

    double figureSize = 110;

    double scale;

    QtGame* game;

    QLabel* moveImg;
    QPoint moveFrom;
    bool moveByClick;
    bool moveByDrag;
    bool moveInvalid;

    typedef std::vector<std::vector<QLabel*>> figureBuffer;
    figureBuffer figures;

    void resizeEvent(QResizeEvent* event);

    void addFigure(FigureType type, TeamColor team, int posX, int posY);
    QPoint getFigureImgPosition(int x, int y);
    QPoint getFigureBoardPosition(int x, int y);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
};

#endif // BOARDWIDGET_H