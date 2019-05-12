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
    void on_buttonKnight_clicked();

    void on_buttonBishop_clicked();

    void on_buttonRook_clicked();

    void on_buttonQueen_clicked();

private:
    Ui::NewFigureDialog *ui;
};

#endif // NEWFIGUREDIALOG_H
