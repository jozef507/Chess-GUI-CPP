#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>

#include "chesswidget.h"

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
    int activeTabIdx = ui->tabWidget->currentIndex();

    // Create tab with empty game
    addTab();

    // Load game from file
    if (ChessWidget* activeGame = dynamic_cast<ChessWidget*>(ui->tabWidget->currentWidget()) )
    {
        if (!activeGame->loadFile())
        {
            // Cannot open file, undo changes
            closeTab(ui->tabWidget->currentIndex(), true);
            ui->tabWidget->setCurrentIndex(activeTabIdx);
            return;
        }

        actualiseTabName();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (ChessWidget* game = dynamic_cast<ChessWidget*>(ui->tabWidget->currentWidget()))
    {
        game->saveFile();
        actualiseTabName();
    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    if (ChessWidget* game = dynamic_cast<ChessWidget*>(ui->tabWidget->currentWidget()))
    {
        game->saveFile(true);
        actualiseTabName();
    }
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    closeTab(index);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    // Close all tabs -> Force saving/discarding changes
    while (ui->tabWidget->count() > 0) {
        if (!closeTab(ui->tabWidget->currentIndex()))
        {
            event->ignore(); // Prevent closing
            return;
        }
    }

    event->accept();
}

void MainWindow::addTab(QString fileName)
{
    ChessWidget* newGame = new ChessWidget;

    newGame->updateBoard();

    ui->tabWidget->addTab(newGame, fileName);
    ui->tabWidget->setCurrentWidget(newGame);

}

void MainWindow::actualiseTabName()
{
    if (ChessWidget* game = dynamic_cast<ChessWidget*>(ui->tabWidget->currentWidget()))
    {
        if (game->getFileName() != nullptr)
        {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), game->isSaved() ? game->getFileName() : "*" + game->getFileName());
        }
        else
        {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), "*Nová Hra");
        }
    }
}

bool MainWindow::closeTab(int index, bool force)
{
    if (ChessWidget* game = dynamic_cast<ChessWidget*>(ui->tabWidget->widget(index)))
    {
        if (!force && !game->isSaved())
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, ui->tabWidget->tabText(index), "Uložit?",
                                          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
            switch (reply) {
            case QMessageBox::Save:
                // Save file before closing
                game->saveFile();
                if (!game->isSaved())
                {
                    // Save aborted
                    return false;
                }
                break;
            case QMessageBox::Discard:
                break;
            default:
                return false;
            }
        }
    }

    ui->tabWidget->removeTab(index);

    return true;
}
