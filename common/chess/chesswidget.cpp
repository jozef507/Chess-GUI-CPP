#include "chesswidget.h"
#include "ui_chesswidget.h"

#include "boardwidget.h"

ChessWidget::ChessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWidget)
{
    ui->setupUi(this);

    saved = false;
    fileName = nullptr;

    // Chess board
    BoardWidget* board = new BoardWidget;
    ui->horizontalLayout->replaceWidget(ui->frame, board);

}

ChessWidget::~ChessWidget()
{
    delete ui;
}
