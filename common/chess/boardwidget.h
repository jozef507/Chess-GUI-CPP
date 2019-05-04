#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();

private:
    Ui::BoardWidget *ui;
};

#endif // BOARDWIDGET_H
