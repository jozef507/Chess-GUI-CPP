#include "boardwidget.h"
#include "ui_boardwidget.h"

BoardWidget::BoardWidget(QtGame* newGame, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);

    scale = static_cast<double>(ui->boardLabel->width()) / 1000;

    figures = figureBuffer(8, std::vector<QLabel*>(8));

    game = newGame;

    /*
    // White figures
    addFigure(FigureType::rook,    TeamColor::white, 0, 0);
    addFigure(FigureType::knight,   TeamColor::white, 1, 0);
    addFigure(FigureType::bishop,   TeamColor::white, 2, 0);
    addFigure(FigureType::queen,    TeamColor::white, 3, 0);
    addFigure(FigureType::king,     TeamColor::white, 4, 0);
    addFigure(FigureType::bishop,   TeamColor::white, 5, 0);
    addFigure(FigureType::knight,   TeamColor::white, 6, 0);
    addFigure(FigureType::rook,    TeamColor::white, 7, 0);
    // White pawns
    for (int x = 0; x < 8; x++) {
        addFigure(FigureType::pawn, TeamColor::white, x, 1);
    }

    // Black figures
    addFigure(FigureType::rook,    TeamColor::black, 0, 7);
    addFigure(FigureType::knight,   TeamColor::black, 1, 7);
    addFigure(FigureType::bishop,   TeamColor::black, 2, 7);
    addFigure(FigureType::queen,    TeamColor::black, 3, 7);
    addFigure(FigureType::king,     TeamColor::black, 4, 7);
    addFigure(FigureType::bishop,   TeamColor::black, 5, 7);
    addFigure(FigureType::knight,   TeamColor::black, 6, 7);
    addFigure(FigureType::rook,    TeamColor::black, 7, 7);
    // Black pawns
    for (int x = 0; x < 8; x++) {
        addFigure(FigureType::pawn, TeamColor::black, x, 6);
    }
    */
}

BoardWidget::~BoardWidget()
{
    delete ui;
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

    figures[X][Y] = figure;

    figure->move(getFigureImgPosition(dstX, dstY));
}

void BoardWidget::changeFigure(FigureType type, TeamColor color, int posX, int posY)
{
    addFigure(type, color, posX, posY);
}

void BoardWidget::resizeEvent(QResizeEvent* event)
{
    int newBoardSize = event->size().width() > event->size().height() ? event->size().height() : event->size().width();
    ui->boardLabel->resize(newBoardSize, newBoardSize);

    scale = static_cast<double>(ui->boardLabel->width()) / boardSize;

    int newFigureSize = static_cast<int>( figureSize * scale );

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            QLabel* figure = figures[static_cast<unsigned long long>( x )][static_cast<unsigned long long>( y )];
            if (figure != nullptr)
            {
                figure->move(getFigureImgPosition(x, y));
                figure->resize(newFigureSize, newFigureSize);

                // TODO: img has to be reloaded from resources
                figure->setPixmap(figure->pixmap()->scaled(newFigureSize, newFigureSize, Qt::KeepAspectRatio));
            }
        }
    }

    //QMessageBox::information(this, nullptr, "label size: " + QString::number(ui->boardLabel->width()) + "\nevent size: " + QString::number(event->size().width()), QMessageBox::Ok);
}

void BoardWidget::addFigure(FigureType type, TeamColor team, int posX, int posY)
{
    QLabel* newFigure = new QLabel(this);
    QPixmap img;

    if (team == TeamColor::white)
    {
        switch (type) {
        case FigureType::pawn:
            img = QPixmap(":img/pawn_white.png");
            break;
        case FigureType::rook:
            img = QPixmap(":img/rogue_white.png");
            break;
        case FigureType::knight:
            img = QPixmap(":img/knight_white.png");
            break;
        case FigureType::bishop:
            img = QPixmap(":img/bishop_white.png");
            break;
        case FigureType::queen:
            img = QPixmap(":img/queen_white.png");
            break;
        case FigureType::king:
            img = QPixmap(":img/king_white.png");
            break;
        default:
            return;
        }
    }
    else
    {
        switch (type) {
        case FigureType::pawn:
            img = QPixmap(":img/pawn_black.png");
            break;
        case FigureType::rook:
            img = QPixmap(":img/rogue_black.png");
            break;
        case FigureType::knight:
            img = QPixmap(":img/knight_black.png");
            break;
        case FigureType::bishop:
            img = QPixmap(":img/bishop_black.png");
            break;
        case FigureType::queen:
            img = QPixmap(":img/queen_black.png");
            break;
        case FigureType::king:
            img = QPixmap(":img/king_black.png");
            break;
        default:
            return;
        }
    }

    int newFigureSize = static_cast<int>( figureSize * scale );

    newFigure->setPixmap(img.scaled(newFigureSize, newFigureSize, Qt::KeepAspectRatio));
    newFigure->move(getFigureImgPosition(posX, posY));

    figures[static_cast<unsigned long long>( posX )][static_cast<unsigned long long>( posY )] = newFigure;
}

QPoint BoardWidget::getFigureImgPosition(int x, int y)
{
    int posX = static_cast<int>( ((boardSquareSize * x) + boardBorderSize) * scale );
    int posY = static_cast<int>( ((boardSquareSize * (7 - y)) + boardBorderSize) * scale ); // 7 - y for reverse order of rows (7 on top down to 0 on bottom of chess-board)

    return QPoint (posX, posY);
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = getFigureImgPosition(event->x(), event->y());

    if (!moveByClick)
    {
        moveFrom = pos;
    }
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (moveInvalid)
    {
        moveByClick = false;
        moveByDrag = false;
        moveInvalid = false;
        return;
    }

    QPoint pos = getFigureImgPosition(event->x(), event->y());

    if (!moveByDrag && !moveByClick)
    {
        moveByClick = true;
        return;
    }

    game->addMove(moveFrom.x(), moveFrom.y(), pos.x(), pos.y());
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

    if (!moveByDrag)
    {
        moveByDrag = true;

        moveImg = figures[static_cast<unsigned long long>( moveFrom.x() )][static_cast<unsigned long long>( moveFrom.y() )];
    }

    QPoint newPos(event->x(), event->y());

    moveImg->move(newPos);
}
