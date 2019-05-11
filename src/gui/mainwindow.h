#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void actualiseTabName();

private slots:
    void on_actionNewGame_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionClose_triggered();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;

    void closeEvent (QCloseEvent *event);

    void addTab(QString fileName = "*Nová Hra");

    bool closeTab(int index, bool force = false);

};

#endif // MAINWINDOW_H
