#include "chesswidget.h"
#include "ui_chesswidget.h"

ChessWidget::ChessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWidget)
{
    ui->setupUi(this);
}

ChessWidget::~ChessWidget()
{
    delete ui;
}
