#include "newfiguredialog.h"
#include "ui_newfiguredialog.h"

NewFigureDialog::NewFigureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFigureDialog)
{
    ui->setupUi(this);
}

NewFigureDialog::~NewFigureDialog()
{
    delete ui;
}

void NewFigureDialog::on_buttonKnight_clicked()
{
    close();
    setResult(1);
}

void NewFigureDialog::on_buttonBishop_clicked()
{
    close();
    setResult(2);
}

void NewFigureDialog::on_buttonRook_clicked()
{
    close();
    setResult(3);
}

void NewFigureDialog::on_buttonQueen_clicked()
{
    close();
    setResult(4);
}
