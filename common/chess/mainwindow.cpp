#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNewGame_triggered()
{
    addTab();
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSaveAs_triggered()
{

}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    closeTab(index);
}

void MainWindow::addTab()
{
    QWidget* newGame = new QWidget;

    ui->tabWidget->addTab(newGame, "*New Game");
    ui->tabWidget->setCurrentWidget(newGame);
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}
