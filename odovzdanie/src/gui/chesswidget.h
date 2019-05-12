/**
 * chesswidget.h
 *
 * Qt widget řešící zobrazení jedné šachové partie včetně notace
 *
 * @author Jan Holásek (xholas09)
 */

#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <vector>

#include <QWidget>
#include <QTimer>

#include "guiinterface.h"
#include "boardwidget.h"
#include "../logic/QtGame.h"

namespace Ui {
class ChessWidget;
}

class ChessWidget : public QWidget, GuiInterface
{
    Q_OBJECT

public:
    explicit ChessWidget(QWidget *parent = nullptr);
    ~ChessWidget();

    /**
     * @brief Zobrazí dialogové okno pro výběr nové figury
     * @return Typ vybrané figury
     */
    FigureType getNewFigureType();

    /**
     * @brief Přesune figuru z výchozí pozice na cílovou
     * @param Zdrojový sloupec
     * @param Zdrojový řádek
     * @param Cílový sloupec
     * @param Cílový řádek
     */
    void updateFigurePosition(int srcX, int srcY, int dstX, int dstY);
    /**
     * @brief Změní typ figury na zadané pozici
     * @param Typ figury
     * @param Barva figury
     * @param Sloupec
     * @param Řádek
     */
    void changeFigureType(FigureType newType, TeamColor color, int posX, int posY);
    /**
     * @brief Obnoví obsah pole podle vnitřní logiky
     * @param Sloupec
     * @param Řádek
     */
    void updatePosition(int posX, int posY);
    /**
     * @brief Obnoví obsah všech polí šachovnice podle vnitřní logiky
     */
    void updateBoard();
    /**
     * @brief Obnoví notaci podle vnitřní logiky
     * @param Vektor řádků notace
     * @param Aktuální řádek v notaci
     * @param Udává zda byla notace změněna (vložen nový tah)
     */
    void updateNotation(std::vector<std::string> notation, int index, bool changed = false);

    /**
     * @brief Vrací zda je aktuální stav notace uložen do souboru.
     * @return Hodnota atributu saved
     */
    bool isSaved();

    /**
     * @brief Vrací jméno posledního souboru, do kterého byla notace uložena.
     * @return Jméno souboru s notací
     */
    QString getFileName();
    /**
     * @brief Načte notaci ze souboru
     * @param Pokud je pravda, získá soubor pomocí dialogového okna od uživatele, jinak použije předchozí soubor
     * @return Vrací true pokud proběhne v pořádku, false v případě chyby
     */
    bool loadFile(bool getFromUser = true);
    /**
     * @brief Uloží notaci do souboru
     * @param Pokud je true, získá nový soubor pomocí dialogového okna od uživatele
     */
    void saveFile(bool saveAs = false);

private slots:
    /**
     * @brief Přejít na začátek partie
     */
    void on_buttonToFirst_clicked();

    /**
     * @brief Vrátí pozici o jeden tah zpět
     */
    void on_buttonPrevious_clicked();

    /**
     * @brief Nastaví pozici na další tah
     */
    void on_buttonNext_clicked();

    /**
     * @brief Přejít na konec partie
     */
    void on_buttonToLast_clicked();

    /**
     * @brief Přejít na tah vybraný kliknutím do notace
     */
    void on_textBrowser_cursorPositionChanged();

    /**
     * @brief Zapíná a vypíná automatické přehrávání partie
     */
    void on_buttonPlayPause_clicked();

    /**
     * @brief Mění časovač přehrávání podle zadaného textu
     */
    void on_lineEdit_editingFinished();

    /**
     * @brief Událost při tiku časovače, nastaví další tah
     */
    void timer_tick();

private:
    Ui::ChessWidget *ui;

    // Widget s šachovnicí
    BoardWidget* board;
    // Vnitřní logika hry
    QtGame* game;

    // Časovač pro automatické přehrávání
    QTimer* timer;

    // Ukládání notace
    bool saved;
    QString fileName;

};

#endif // CHESSWIDGET_H
