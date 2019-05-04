#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <QWidget>

namespace Ui {
class ChessWidget;
}

class ChessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChessWidget(QWidget *parent = nullptr);
    ~ChessWidget();

private:
    Ui::ChessWidget *ui;
};

#endif // CHESSWIDGET_H
