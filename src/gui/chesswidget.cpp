#include "chesswidget.h"
#include "ui_chesswidget.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QTextStream>

ChessWidget::ChessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWidget)
{
    ui->setupUi(this);

    saved = false;
    fileName = nullptr;

    // Chess board
    board = new BoardWidget;
    ui->horizontalLayout->replaceWidget(ui->frame, board);

    game = new QtGame(this);

    board->setGame(game);
}

ChessWidget::~ChessWidget()
{
    delete ui;
}

/*
 * 0 - king
 * 1 - queen
 * 2 - bishop
 * 3 - knight
 * 4 - rook
 * 5 - pawn
 */
int ChessWidget::getNewFigureId()
{
    int id = 1;

    // TODO: get id from user

    return id;
}

void ChessWidget::updateFigurePosition(int srcX, int srcY, int dstX, int dstY)
{
    board->moveFigure(srcX, srcY, dstX, dstY);
}

void ChessWidget::changeFigureType(FigureType newType, TeamColor color, int posX, int posY)
{
    board->changeFigure(newType, color, posX, posY);
}

void ChessWidget::updatePosition(int posX, int posY)
{
    board->updatePosition(posX, posY);
}

void ChessWidget::updateBoard()
{
    board->updateBoard();
}

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


bool ChessWidget::isSaved()
{
    return saved;
}

QString ChessWidget::getFileName()
{
    return fileName;
}

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

    board->setGame(game);
    game->updateNotation();

    saved = true;

    return true;
}

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

void ChessWidget::on_buttonToFirst_clicked()
{
    while (game->previousPosition());
}

void ChessWidget::on_buttonPrevious_clicked()
{
    game->previousPosition();
}

void ChessWidget::on_buttonNext_clicked()
{
    game->nextPosition();
}

void ChessWidget::on_buttonToLast_clicked()
{
    while (game->nextPosition());
}

void ChessWidget::on_textBrowser_cursorPositionChanged()
{
    QTextCursor C = ui->textBrowser->textCursor();
    std::string S = ui->textBrowser->document()->toPlainText().toUtf8().constData();

    int line = 0;
    int part = 0;

    int i = 0;
    while (i < C.position())
    {
        if (S[static_cast<unsigned>( i )] == ' ')
        {
            part++;
        }

        if (S[static_cast<unsigned>( i )] == '\n')
        {
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
    int index = line + 1;
    game->setPosition(index, player);
}
