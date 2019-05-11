#include "chesswidget.h"
#include "ui_chesswidget.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QTextStream>

ChessWidget::ChessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWidget)
{
    ui->setupUi(this);

    saved = false;
    fileName = nullptr;

    // Chess board
    board = new BoardWidget;
    ui->horizontalLayout->replaceWidget(ui->frame, board);

    game = new QtGame(this);

    board->setGame(game);
}

ChessWidget::~ChessWidget()
{
    delete ui;
}

/*
 * 0 - king
 * 1 - queen
 * 2 - bishop
 * 3 - knight
 * 4 - rook
 * 5 - pawn
 */
int ChessWidget::getNewFigureId()
{
    int id = 1;

    // TODO: get id from user

    return id;
}

void ChessWidget::updateFigurePosition(int srcX, int srcY, int dstX, int dstY)
{
    board->moveFigure(srcX, srcY, dstX, dstY);
}

void ChessWidget::changeFigureType(FigureType newType, TeamColor color, int posX, int posY)
{
    board->changeFigure(newType, color, posX, posY);
}

void ChessWidget::updatePosition(int posX, int posY)
{
    board->updatePosition(posX, posY);
}

void ChessWidget::updateBoard()
{
    board->updateBoard();
}

void ChessWidget::updateNotation(std::vector<std::string> notation, int index)
{
    // TODO:
}


bool ChessWidget::isSaved()
{
    return saved;
}

QString ChessWidget::getFileName()
{
    return fileName;
}

bool ChessWidget::loadFile()
{
    // Get filename from dialog window
    fileName = QFileDialog::getOpenFileName(this, nullptr, nullptr, "All Files (*) ;; Text Files (*.txt)");

    if (fileName == nullptr)
    {
        // File not selected
        return false;
    }

    QFile* file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, nullptr, file->errorString());
        return false;
    }

    QTextStream* in = new QTextStream(file);

    ui->textBrowser->setText(in->readAll());

    saved = true;

    return true;
}

void ChessWidget::saveFile(bool saveAs)
{
    if (saveAs || fileName == nullptr)
    {
        QString newName = QFileDialog::getSaveFileName(this, nullptr, nullptr, "All Files (*) ;; Text Files (*.txt)");

        if (newName == nullptr)
        {
            // File not selected
            return;
        }

        fileName = newName;
    }

    // TODO: Save File

    saved = true;
}

void ChessWidget::on_buttonToFirst_clicked()
{
    while (game->previousPosition());
}

void ChessWidget::on_buttonPrevious_clicked()
{
    game->previousPosition();
}

void ChessWidget::on_buttonNext_clicked()
{
    game->nextPosition();
}

void ChessWidget::on_buttonToLast_clicked()
{
    while (game->nextPosition());
}
