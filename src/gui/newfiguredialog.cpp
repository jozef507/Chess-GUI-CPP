#include "newfiguredialog.h"
#include "ui_newfiguredialog.h"

NewFigureDialog::NewFigureDialog(QWidget *parent, TeamColor player) :
    QDialog(parent),
    ui(new Ui::NewFigureDialog)
{
    ui->setupUi(this);

    if (player == TeamColor::black)
    {
        ui->buttonKnight->setIcon(QIcon(QPixmap(":img/knightBlack")));
        ui->buttonBishop->setIcon(QIcon(QPixmap(":img/bishopBlack")));
        ui->buttonRook->setIcon(QIcon(QPixmap(":img/rookBlack")));
        ui->buttonQueen->setIcon(QIcon(QPixmap(":img/queenBlack")));
    }
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
