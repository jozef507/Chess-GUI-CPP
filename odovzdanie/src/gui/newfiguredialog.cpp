/**
 * newfiguredialog.cpp
 *
 * Dialogové okno pro výběr nové figury
 *
 * @author Jan Holásek (xholas09)
 */

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

/**
 * @brief Vybrán jezdec
 */
void NewFigureDialog::on_buttonKnight_clicked()
{
    close();
    setResult(1);
}

/**
 * @brief Vybrán střelec
 */
void NewFigureDialog::on_buttonBishop_clicked()
{
    close();
    setResult(2);
}

/**
 * @brief Vybrána věž
 */
void NewFigureDialog::on_buttonRook_clicked()
{
    close();
    setResult(3);
}

/**
 * @brief Vybrána dáma
 */
void NewFigureDialog::on_buttonQueen_clicked()
{
    close();
    setResult(4);
}
