/**
 * newfiguredialog.h
 *
 * Dialogové okno pro výběr nové figury
 *
 * Autor: Jan Holásek (xholas09)
 */

#ifndef NEWFIGUREDIALOG_H
#define NEWFIGUREDIALOG_H

#include <QDialog>
#include "chesstypes.h"

namespace Ui {
class NewFigureDialog;
}

class NewFigureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFigureDialog(QWidget *parent = nullptr, TeamColor player = TeamColor::white);
    ~NewFigureDialog();

private slots:
    /**
     * @brief Vybrán jezdec
     */
    void on_buttonKnight_clicked();

    /**
     * @brief Vybrán střelec
     */
    void on_buttonBishop_clicked();

    /**
     * @brief Vybrána věž
     */
    void on_buttonRook_clicked();

    /**
     * @brief Vybrána dáma
     */
    void on_buttonQueen_clicked();

private:
    Ui::NewFigureDialog *ui;
};

#endif // NEWFIGUREDIALOG_H
