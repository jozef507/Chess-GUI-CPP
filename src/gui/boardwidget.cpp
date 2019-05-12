#include "boardwidget.h"
#include "ui_boardwidget.h"
#include <iostream>

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);

    figures = figureBuffer(8, std::vector<QLabel*>(8));
}

BoardWidget::~BoardWidget()
{
    delete ui;
}


void BoardWidget::setGame(QtGame* newGame)
{
    game = newGame;

    updateBoard();
}

int BoardWidget::heightForWidth(int w) const
{
    return w;
}

void BoardWidget::moveFigure(int srcX, int srcY, int dstX, int dstY)
{
    unsigned long long X = static_cast<unsigned long long>(srcX);
    unsigned long long Y = static_cast<unsigned long long>(srcY);

    QLabel* figure = figures[X][Y];
    figures[X][Y] = nullptr;

    X = static_cast<unsigned long long>(dstX);
    Y = static_cast<unsigned long long>(dstY);

    if (figures[X][Y] != nullptr)
    {
        delete figures[X][Y];
    }

    figures[X][Y] = figure;

    figure->move(getFigureImgPosition(dstX, dstY));
}

void BoardWidget::changeFigure(FigureType type, TeamColor color, int posX, int posY)
{
    unsigned long long X = static_cast<unsigned long long>(posX);
    unsigned long long Y = static_cast<unsigned long long>(posY);

    delete figures[X][Y];

    addFigure(type, color, posX, posY);
}

void BoardWidget::updateBoard()
{
    QPixmap newBoardPixmap(":/img/board");
    ui->boardLabel->setPixmap(newBoardPixmap.scaled(ui->boardLabel->width(), ui->boardLabel->height(), Qt::KeepAspectRatio));

    scale = static_cast<double>(ui->boardLabel->width()) / 1000;

    for (int x = 0; x < 8; x++) {
        unsigned long long indexX = static_cast<unsigned long long>( x );

        for (int y = 0; y < 8; y++) {
            unsigned long long indexY = static_cast<unsigned long long>( y );

            if (figures[indexX][indexY] != nullptr)
            {
                delete figures[indexX][indexY];
                figures[indexX][indexY] = nullptr;
            }

            if (game->isFieldEmpty(x, y))
            {
                figures[indexX][indexY] = nullptr;
                continue;
            }

            FigureType type = game->getFigureType(x, y);
            TeamColor color = game->getFigureColor(x, y);

            addFigure(type, color, x, y);
        }
    }
}

void BoardWidget::updatePosition(int posX, int posY)
{
    unsigned long long X = static_cast<unsigned long long>(posX);
    unsigned long long Y = static_cast<unsigned long long>(posY);

    if (figures[X][Y] != nullptr)
    {
        delete figures[X][Y];
        figures[X][Y] = nullptr;
    }

    if (!game->isFieldEmpty(posX, posY))
    {
        FigureType type = game->getFigureType(posX, posY);
        TeamColor color = game->getFigureColor(posX, posY);

        addFigure(type, color, posX, posY);
    }
}


void BoardWidget::addFigure(FigureType type, TeamColor team, int posX, int posY)
{
    QLabel* newFigure = new QLabel(this);
    QPixmap img;

    if (team == TeamColor::white)
    {
        switch (type) {
        case FigureType::pawn:
            img = QPixmap(":img/pawnWhite");
            break;
        case FigureType::rook:
            img = QPixmap(":img/rookWhite");
            break;
        case FigureType::knight:
            img = QPixmap(":img/knightWhite");
            break;
        case FigureType::bishop:
            img = QPixmap(":img/bishopWhite");
            break;
        case FigureType::queen:
            img = QPixmap(":img/queenWhite");
            break;
        case FigureType::king:
            img = QPixmap(":img/kingWhite");
            break;
        default:
            return;
        }
    }
    else
    {
        switch (type) {
        case FigureType::pawn:
            img = QPixmap(":img/pawnBlack");
            break;
        case FigureType::rook:
            img = QPixmap(":img/rookBlack");
            break;
        case FigureType::knight:
            img = QPixmap(":img/knightBlack");
            break;
        case FigureType::bishop:
            img = QPixmap(":img/bishopBlack");
            break;
        case FigureType::queen:
            img = QPixmap(":img/queenBlack");
            break;
        case FigureType::king:
            img = QPixmap(":img/kingBlack");
            break;
        default:
            return;
        }
    }

    int newFigureSize = static_cast<int>( figureSize * scale );

    newFigure->setPixmap(img.scaled(newFigureSize, newFigureSize, Qt::KeepAspectRatio));
    newFigure->move(getFigureImgPosition(posX, posY));

    unsigned long long X = static_cast<unsigned long long>(posX);
    unsigned long long Y = static_cast<unsigned long long>(posY);

    figures[X][Y] = newFigure;

    // To fix figures disappearing when rezized
    newFigure->show();
}

QPoint BoardWidget::getFigureImgPosition(int x, int y)
{
    int posX = static_cast<int>( ((boardSquareSize * x) + boardBorderSize) * scale );
    int posY = static_cast<int>( ((boardSquareSize * (7 - y)) + boardBorderSize) * scale ); // 7 - y for reverse order of rows (7 on top down to 0 on bottom of chess-board)

    return QPoint (posX, posY);
}

QPoint BoardWidget::getFigureBoardPosition(int x, int y)
{
    int posX = static_cast<int>( (static_cast<double>( x ) / scale - boardBorderSize) / boardSquareSize );
    int posY = 7 - static_cast<int>( (static_cast<double>( y ) / scale - boardBorderSize) / boardSquareSize );

    return  QPoint(posX, posY);
}

void BoardWidget::resizeEvent(QResizeEvent* event)
{
    int newBoardSize = event->size().width() > event->size().height() ? event->size().height() : event->size().width();
    ui->boardLabel->resize(newBoardSize, newBoardSize);

    updateBoard();
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = getFigureBoardPosition(event->x(), event->y());

    if (!moveByClick)
    {
        moveFrom = pos;

        unsigned long long X = static_cast<unsigned long long>(pos.x());
        unsigned long long Y = static_cast<unsigned long long>(pos.y());

        moveImg = figures[X][Y];
    }
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (moveImg == nullptr)
    {
        moveInvalid = true;
    }

    if (moveInvalid)
    {
        moveImg = nullptr;

        moveByClick = false;
        moveByDrag = false;
        moveInvalid = false;
        return;
    }

    QPoint pos = getFigureBoardPosition(event->x(), event->y());

    if (!moveByDrag && !moveByClick)
    {
        moveByClick = true;
        return;
    }

    if (!game->addMove(moveFrom.x(), moveFrom.y(), pos.x(), pos.y()))
    {
        moveImg->move(getFigureImgPosition(moveFrom.x(), moveFrom.y()));
    }

    moveByClick = false;
    moveByDrag = false;
}

void BoardWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (moveInvalid)
    {
        return;
    }

    if (moveByClick)
    {
        moveByClick = false;
        moveInvalid = true;
        return;
    }

    moveByDrag = true;

    if (moveImg == nullptr)
    {
        moveInvalid = true;
        return;
    }

    int offset = static_cast<int>( (figureSize / 2) * scale );
    QPoint newPos(event->x() - offset, event->y() - offset);

    moveImg->move(newPos);
}
