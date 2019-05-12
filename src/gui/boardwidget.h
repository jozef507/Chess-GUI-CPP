/**
 * boardwidget.h
 *
 * Qt widget řešící zobrazení šachovnice a figur
 *
 * Autor: Jan Holásek (xholas09)
 */

#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>

#include "chesstypes.h"
#include "../logic/QtGame.h"

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();

    /**
     * @brief Propojuje zobrazení hry s vnitřní logikou
     * @param Vnitřní logika hry
     */
    void setGame(QtGame* newGame);

    /**
     * @brief Zajišťuje čtvercový charakter šachovnice
     * @param Šířka widgetu
     * @return Výška widgetu
     */
    int heightForWidth(int w) const;

    /**
     * @brief Přesune figuru ze zdrojového pole na cílové
     * @param Sloupec zdrojového pole
     * @param Řádek zdrojového pole
     * @param Sloupec cílového pole
     * @param Řádek cílového pole
     */
    void moveFigure(int srcX, int srcY, int dstX, int dstY);
    /**
     * @brief Vymění figuru na pozici za novou
     * @param Typ nové figury
     * @param Barva nové figury
     * @param Sloupec
     * @param Řádek
     */
    void changeFigure(FigureType type, TeamColor color, int posX, int posY);
    /**
     * @brief Obnoví vykreslení šachovnice podle vnitřní logiky
     */
    void updateBoard();
    /**
     * @brief Obnoví pole šachovnice podle vnitřní logiky
     * @param Sloupec
     * @param Řádek
     */
    void updatePosition(int posX, int posY);

private:
    Ui::BoardWidget *ui;

    // Image sizes
    double boardSize = 1000;
    double boardBorderSize = 47 + 3; // border + offset for position correction
    double boardSquareSize = 113.25;

    double figureSize = 110;

    double scale;

    // Game Logic
    QtGame* game;

    // Move by user input
    QLabel* moveImg;
    QPoint moveFrom;
    bool moveByClick;
    bool moveByDrag;
    bool moveInvalid;

    // Figures buffer
    typedef std::vector<std::vector<QLabel*>> figureBuffer;
    figureBuffer figures;

    /**
     * @brief Přidá novou figuru na zadané pole
     * @param Typ figury
     * @param Barva figury
     * @param Sloupec
     * @param Řádek
     */
    void addFigure(FigureType type, TeamColor team, int posX, int posY);
    /**
     * @brief Přepočítává pozici ze šachovnice na pozici v obraze
     * @param Sloupec šachovnice
     * @param Řádek šachovnice
     * @return Pozice v obraze
     */
    QPoint getFigureImgPosition(int x, int y);
    /**
     * @brief Přepočítává pozici z obrazu no pizici v šachovnici
     * @param Souřadnice x
     * @param Souřadnice y
     * @return Pozice na šachovnici
     */
    QPoint getFigureBoardPosition(int x, int y);

    /**
     * @brief Přepočítání velikostí
     * @param event
     */
    void resizeEvent(QResizeEvent* event);

    /**
     * @brief Začátek tahu
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Ukončení tahu
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief Posun figury s kurzorem myši
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // BOARDWIDGET_H
