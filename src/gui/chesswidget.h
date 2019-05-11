#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <vector>

#include <QWidget>

#include "guiinterface.h"
#include "boardwidget.h"
#include "../logic/QtGame.h"

namespace Ui {
class ChessWidget;
}

class ChessWidget : public QWidget, GuiInterface
{
    Q_OBJECT

public:
    explicit ChessWidget(QWidget *parent = nullptr);
    ~ChessWidget();

    int getNewFigureId();

    void updateFigurePosition(int srcX, int srcY, int dstX, int dstY);
    void changeFigureType(FigureType newType, TeamColor color, int posX, int posY);
    void updatePosition(int posX, int posY);
    void updateBoard();
    void updateNotation(std::vector<std::string> notation, int index);

    bool isSaved();

    QString getFileName();
    bool loadFile();
    void saveFile(bool saveAs = false);

private slots:
    void on_buttonToFirst_clicked();

    void on_buttonPrevious_clicked();

    void on_buttonNext_clicked();

    void on_buttonToLast_clicked();

private:
    Ui::ChessWidget *ui;

    BoardWidget* board;
    QtGame* game;

    bool saved;
    QString fileName;

};

#endif // CHESSWIDGET_H
