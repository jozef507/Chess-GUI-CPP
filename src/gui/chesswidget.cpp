#include "chesswidget.h"
#include "ui_chesswidget.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QTextStream>

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
