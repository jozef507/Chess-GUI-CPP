/**
 * chesswidget.cpp
 *
 * Qt widget řešící zobrazení jedné šachové partie včetně notace
 *
 * Autor: Jan Holásek (xholas09)
 */

#include "chesswidget.h"
#include "ui_chesswidget.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QTextStream>

#include "newfiguredialog.h"

ChessWidget::ChessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWidget)
{
    ui->setupUi(this);

    saved = true;
    fileName = nullptr;

    // Chess board
    board = new BoardWidget;
    ui->horizontalLayout->replaceWidget(ui->frame, board);

    game = new QtGame(this);

    board->setGame(game);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_tick()));
}

ChessWidget::~ChessWidget()
{
    delete ui;
}


/**
 * @brief Zobrazí dialogové okno pro výběr nové figury
 * @return Typ vybrané figury
 */
FigureType ChessWidget::getNewFigureType()
{
    /*
     * 0 - king
     * 1 - queen
     * 2 - bishop
     * 3 - knight
     * 4 - rook
     * 5 - pawn
     */
    NewFigureDialog dialog(this, game->getActivePlayer());

    int result = dialog.exec();

    switch (result) {
    case 1:
        return FigureType::knight;
    case 2:
        return FigureType::bishop;
    case 3:
        return FigureType::rook;
    case 4:
        return FigureType::queen;
    default:
        return FigureType::invalid;
    }
}

/**
 * @brief Přesune figuru z výchozí pozice na cílovou
 * @param Zdrojový sloupec
 * @param Zdrojový řádek
 * @param Cílový sloupec
 * @param Cílový řádek
 */
void ChessWidget::updateFigurePosition(int srcX, int srcY, int dstX, int dstY)
{
    board->moveFigure(srcX, srcY, dstX, dstY);
}

/**
 * @brief Změní typ figury na zadané pozici
 * @param Typ figury
 * @param Barva figury
 * @param Sloupec
 * @param Řádek
 */
void ChessWidget::changeFigureType(FigureType newType, TeamColor color, int posX, int posY)
{
    board->changeFigure(newType, color, posX, posY);
}

/**
 * @brief Obnoví obsah pole podle vnitřní logiky
 * @param Sloupec
 * @param Řádek
 */
void ChessWidget::updatePosition(int posX, int posY)
{
    board->updatePosition(posX, posY);
}

/**
 * @brief Obnoví obsah všech polí šachovnice podle vnitřní logiky
 */
void ChessWidget::updateBoard()
{
    board->updateBoard();
}

/**
 * @brief Obnoví notaci podle vnitřní logiky
 * @param Vektor řádků notace
 * @param Aktuální řádek v notaci
 * @param Udává zda byla notace změněna (vložen nový tah)
 */
void ChessWidget::updateNotation(std::vector<std::string> notation, int index, bool changed)
{
    if (changed)
    {
        saved = false;
    }

    QString S = "";

    int lineIndex = 0;
    int highlightStart = 0;
    int highlightEnd = 0;

    for (auto line : notation) {
        lineIndex++;

        if (lineIndex == index)
        {
            // Position of next line
            highlightStart = S.length();

            // Skip after next space
            unsigned i = 0;
            bool secondPart = game->getActivePlayer() == TeamColor::white;
            while (i < line.length())
            {
                highlightStart++;
                if (line[i] == ' ')
                {
                    // Skip first part (white move) and continue to second (black move)
                    if (secondPart){
                        secondPart = false;
                    }
                    else
                    {
                        break;
                    }
                }

                i++;
            }

            highlightEnd = highlightStart;
            i++;

            while (i < line.length()) {
                highlightEnd++;
                if (line[i] == ' ')
                {
                    break;
                }

                i++;
            }
        }

        S += (line + "\n").c_str();

    }

    ui->textBrowser->setText(S);

    // Highlight current move
    if (game->isInitialPosition())
    {
        return;
    }

    QTextCharFormat highlight;
    highlight.setBackground(Qt::gray);

    QTextCursor cursor(ui->textBrowser->document());
    cursor.setPosition(highlightStart, QTextCursor::MoveAnchor);
    cursor.setPosition(highlightEnd, QTextCursor::KeepAnchor);

    cursor.setCharFormat(highlight);
}


/**
 * @brief Vrací zda je aktuální stav notace uložen do souboru.
 * @return Hodnota atributu saved
 */
bool ChessWidget::isSaved()
{
    return saved;
}

/**
 * @brief Vrací jméno posledního souboru, do kterého byla notace uložena.
 * @return Jméno souboru s notací
 */
QString ChessWidget::getFileName()
{
    return fileName;
}

/**
 * @brief Načte notaci ze souboru
 * @param Pokud je pravda, získá soubor pomocí dialogového okna od uživatele, jinak použije předchozí soubor
 * @return Vrací true pokud proběhne v pořádku, false v případě chyby
 */
bool ChessWidget::loadFile(bool getFromUser)
{
    if (getFromUser)
    {
        // Get filename from dialog window
        QString defaultType = "Text Files (*.txt)";
        fileName = QFileDialog::getOpenFileName(this, nullptr, nullptr, "All Files (*) ;; Text Files (*.txt)", &defaultType);
    }

    if (fileName == nullptr)
    {
        // File not selected
        return false;
    }

    if (game != nullptr)
    {
        delete game;
        game = nullptr;
    }
    game = new QtGame(this, fileName);

    if (!game->isNotationCorrect())
    {
        QMessageBox::information(this, nullptr, "Zápis partie je chybný.");
        return false;
    }

    board->setGame(game);
    game->updateNotation();

    saved = true;

    return true;
}

/**
 * @brief Uloží notaci do souboru
 * @param Pokud je true, získá nový soubor pomocí dialogového okna od uživatele
 */
void ChessWidget::saveFile(bool saveAs)
{
    if (saveAs || fileName == nullptr)
    {
        QString defaultType = "Text Files (*.txt)";
        QString newName = QFileDialog::getSaveFileName(this, nullptr, nullptr, "All Files (*) ;; Text Files (*.txt)", &defaultType);

        if (newName == nullptr)
        {
            // File not selected
            return;
        }

        fileName = newName;

        game->saveFile(fileName.toUtf8().constData());

        loadFile(false);
    }
    else
    {
        game->saveFile();
    }

    saved = true;
}

/**
 * @brief Přejít na začátek partie
 */
void ChessWidget::on_buttonToFirst_clicked()
{
    while (game->previousPosition());
}

/**
 * @brief Vrátí pozici o jeden tah zpět
 */
void ChessWidget::on_buttonPrevious_clicked()
{
    game->previousPosition();
}

/**
 * @brief Nastaví pozici na další tah
 */
void ChessWidget::on_buttonNext_clicked()
{
    game->nextPosition();
}

/**
 * @brief Přejít na konec partie
 */
void ChessWidget::on_buttonToLast_clicked()
{
    while (game->nextPosition());
}

/**
 * @brief Přejít na tah vybraný kliknutím do notace
 */
void ChessWidget::on_textBrowser_cursorPositionChanged()
{
    int position = ui->textBrowser->textCursor().position();
    std::string text = ui->textBrowser->document()->toPlainText().toUtf8().constData();

    int line = 0;
    int part = 0;

    int i = 0;
    while (i < position)
    {
        if (text[static_cast<unsigned>( i )] == ' ')
        {
            part++;
        }

        if (text[static_cast<unsigned>( i )] == '\n')
        {
            part++;
            line++;
        }

        i++;
    }

    part = part % 3;

    if (part == 0)
    {
        return;
    }

    TeamColor player = part == 1 ? TeamColor::white : TeamColor::black;

    game->setPosition(line, player);
}

/**
 * @brief Zapíná a vypíná automatické přehrávání partie
 */
void ChessWidget::on_buttonPlayPause_clicked()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start();
    }
}

/**
 * @brief Mění časovač přehrávání podle zadaného textu
 */
void ChessWidget::on_lineEdit_editingFinished()
{
    std::string S = ui->lineEdit->text().toUtf8().constData();

    int i;
    try
    {
        i = static_cast<int>( std::stod(S) * 1000 );
    }
    catch (...)
    {
        i = 1000;
    }

    if (i > 1000000 || i < 0)
    {
        i = 1000;
    }

    if (timer->interval() != i)
    {
        timer->setInterval(i);
    }

//QMessageBox::information(nullptr, nullptr, ("HERE: " + std::to_string(i)).c_str() );

    std::string newS = std::to_string((i/1000)) + "." + std::to_string(i%1000).substr(0, 2) + "s";

    if (newS != S)
    {
        ui->lineEdit->setText(newS.c_str());
    }
}

/**
 * @brief Událost při tiku časovače, nastaví další tah
 */
void ChessWidget::timer_tick()
{
    if (!game->nextPosition())
    {
        timer->stop();
    }
}
