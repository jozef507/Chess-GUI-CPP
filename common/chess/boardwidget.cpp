#include "boardwidget.h"
#include "ui_boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);
}

BoardWidget::~BoardWidget()
{
    delete ui;
}

int BoardWidget::heightForWidth(int w) const
{
    return w;
}

void BoardWidget::resizeEvent(QResizeEvent* event)
{
    int newBoardSize = event->size().width() > event->size().height() ? event->size().height() : event->size().width();
    ui->boardLabel->resize(newBoardSize, newBoardSize);

    scale = static_cast<double>(ui->boardLabel->width()) / 1000;

    /*
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (labels[x][y] != nullptr)
            {
                labels[x][y]->move(getFigureImgPosition(x, y));
            }
        }
    }
    */

    //QMessageBox::information(this, nullptr, "label size: " + QString::number(ui->boardLabel->width()) + "\nevent size: " + QString::number(event->size().width()), QMessageBox::Ok);
}
