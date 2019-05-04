#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();

    int heightForWidth(int w) const;

private:
    Ui::BoardWidget *ui;

    double scale;

    void resizeEvent(QResizeEvent* event);

};

#endif // BOARDWIDGET_H
