#include "boardwidget.h"
#include "ui_boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);

    scale = static_cast<double>(ui->boardLabel->width()) / 1000;

    figures = figureBuffer(8, std::vector<QLabel*>(8));

    // White figures
    addFigure(FigureType::rogue,    TeamColor::white, 0, 0);
    addFigure(FigureType::knight,   TeamColor::white, 1, 0);
    addFigure(FigureType::bishop,   TeamColor::white, 2, 0);
    addFigure(FigureType::queen,    TeamColor::white, 3, 0);
    addFigure(FigureType::king,     TeamColor::white, 4, 0);
    addFigure(FigureType::bishop,   TeamColor::white, 5, 0);
    addFigure(FigureType::knight,   TeamColor::white, 6, 0);
    addFigure(FigureType::rogue,    TeamColor::white, 7, 0);
    // White pawns
    for (int x = 0; x < 8; x++) {
        addFigure(FigureType::pawn, TeamColor::white, x, 1);
    }

    // Black figures
    addFigure(FigureType::rogue,    TeamColor::black, 0, 7);
    addFigure(FigureType::knight,   TeamColor::black, 1, 7);
    addFigure(FigureType::bishop,   TeamColor::black, 2, 7);
    addFigure(FigureType::queen,    TeamColor::black, 3, 7);
    addFigure(FigureType::king,     TeamColor::black, 4, 7);
    addFigure(FigureType::bishop,   TeamColor::black, 5, 7);
    addFigure(FigureType::knight,   TeamColor::black, 6, 7);
    addFigure(FigureType::rogue,    TeamColor::black, 7, 7);
    // Black pawns
    for (int x = 0; x < 8; x++) {
        addFigure(FigureType::pawn, TeamColor::black, x, 6);
    }
}

BoardWidget::~BoardWidget()
{
    delete ui;
}

int BoardWidget::heightForWidth(int w) const
{
    return w;
}

void BoardWidget::resizeEvent(QResizeEvent* event)
{
    int newBoardSize = event->size().width() > event->size().height() ? event->size().height() : event->size().width();
    ui->boardLabel->resize(newBoardSize, newBoardSize);

    scale = static_cast<double>(ui->boardLabel->width()) / boardSize;

    int newFigureSize = static_cast<int>( figureSize * scale );

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            QLabel* figure = figures[x][y];
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
        case FigureType::rogue:
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
        }
    }
    else
    {
        switch (type) {
        case FigureType::pawn:
            img = QPixmap(":img/pawn_black.png");
            break;
        case FigureType::rogue:
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
        }
    }

    int newFigureSize = static_cast<int>( figureSize * scale );

    newFigure->setPixmap(img.scaled(newFigureSize, newFigureSize, Qt::KeepAspectRatio));
    newFigure->move(getFigureImgPosition(posX, posY));

    figures[posX][posY] = newFigure;
}

QPoint BoardWidget::getFigureImgPosition(int x, int y)
{
    int posX = static_cast<int>( ((boardSquareSize * x) + boardBorderSize) * scale );
    int posY = static_cast<int>( ((boardSquareSize * (7 - y)) + boardBorderSize) * scale ); // 7 - y for reverse order of rows (7 on top down to 0 on bottom of chess-board)

    return QPoint (posX, posY);
}
