#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    enum class TeamColor
    {
        white,
        black
    };
    enum class FigureType
    {
        pawn,
        rogue,
        knight,
        bishop,
        queen,
        king
    };

    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();

    int heightForWidth(int w) const;

private:
    Ui::BoardWidget *ui;

    double boardSize = 1000;
    double boardBorderSize = 47 + 3; // border + offset for position correction
    double boardSquareSize = 113.25;

    double figureSize = 110;

    double scale;
    //QLabel* labels[8][8];

    typedef std::vector<std::vector<QLabel*>> figureBuffer;
    figureBuffer figures;

    void resizeEvent(QResizeEvent* event);

    void addFigure(FigureType type, TeamColor team, int posX, int posY);
    QPoint getFigureImgPosition(int x, int y);
};

#endif // BOARDWIDGET_H
