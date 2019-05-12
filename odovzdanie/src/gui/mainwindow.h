/**
 * mainwindow.h
 *
 * Hlavní okno programu, obsahuje záložky s jednotlivými partiemi
 *
 * @author Jan Holásek (xholas09)
 */

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

    /**
     * @brief Obnoví jméno záložky
     */
    void actualiseTabName();

private slots:
    /**
     * @brief Vytvoří novou záložku s novou hrou
     */
    void on_actionNewGame_triggered();

    /**
     * @brief Vytvoří novou záložku a načte hru ze souboru
     */
    void on_actionOpen_triggered();

    /**
     * @brief Uloží notaci z aktivní záložky
     */
    void on_actionSave_triggered();

    /**
     * @brief Uloží notaci z aktivní záložky do nového souboru
     */
    void on_actionSaveAs_triggered();

    /**
     * @brief Ukončí program
     */
    void on_actionClose_triggered();

    /**
     * @brief Zavře záložku podle indexu
     * @param Index zavírané záložky
     */
    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;

    /**
     * @brief Událost při zavření programu
     * @param event
     */
    void closeEvent (QCloseEvent *event);

    /**
     * @brief Přidá novou záložku
     * @param Jméno souboru / záložky
     */
    void addTab(QString fileName = "*Nová Hra");

    /**
     * @brief Zavře záložku
     * @param Index zavírané záložky
     * @param Vynutí zavření bez uložení
     */
    bool closeTab(int index, bool force = false);

};

#endif // MAINWINDOW_H
