#include <iostream>
#include <string>

#include "ui.h"

UI::UI()
{
    game = new QtGame(this);
}

UI::~UI()
{
    delete game;
}

void UI::run()
{
    std::string in;
    while(std::getline(std::cin, in, '\n'))
    {
        if (in == "exit")
        {
            exit(0);
        }
        else
        {
            std::cout << "Move: \n";
            if (!game->addMove(1,2,1,3))
            {
                std::cout << "Fail!\n";
            }
            std::cout << "Done: \n";

            std::cout << "Move: \n";
            if (!game->addMove(8,7,8,5))
            {
                std::cout << "Fail!\n";
            }
            std::cout << "Done: \n";

            std::cout << "Move: \n";
            if (!game->addMove(1,3,1,4))
            {
                std::cout << "Fail!\n";
            }
            std::cout << "Done: \n";

            std::cout << "Move: \n";
            if (!game->addMove(8,8,8,6))
            {
                std::cout << "Fail!\n";
            }
            std::cout << "Done: \n";

            continue;
        }
    }
}

int UI::getNewFigureId()
{
    std::cout << "Set new figure ID:\n";

    int id;
    std::cin >> id;
    return id;
}

void UI::updateFigurePosition(int srcX, int srcY, int dstX, int dstY)
{
    char c1, c2;

    srcX -= 1;
    dstX -= 1;

    switch (srcX)
    {
    case 0:
        c1 = 'A';
        break;
    case 1:
        c1 = 'B';
        break;
    case 2:
        c1 = 'C';
        break;
    case 3:
        c1 = 'D';
        break;
    case 4:
        c1 = 'E';
        break;
    case 5:
        c1 = 'F';
        break;
    case 6:
        c1 = 'G';
        break;
    case 7:
        c1 = 'H';
        break;
    default:
        c1 = 'X';
        break;
    }

    switch (dstX)
    {
    case 0:
        c2 = 'A';
        break;
    case 1:
        c2 = 'B';
        break;
    case 2:
        c2 = 'C';
        break;
    case 3:
        c2 = 'D';
        break;
    case 4:
        c2 = 'E';
        break;
    case 5:
        c2 = 'F';
        break;
    case 6:
        c2 = 'G';
        break;
    case 7:
        c2 = 'H';
        break;
    default:
        c2 = 'X';
        break;
    }

    std::cout << c1 << srcY << " - " << c2 << dstY << "\n";

}

/*
 * 0 - king
 * 1 - queen
 * 2 - bishop
 * 3 - knight
 * 4 - rook
 * 5 - pawn
 */
int typeToInt(FigureType type)
{
    switch (type) {
    case FigureType::king:
        return 0;
    case FigureType::pawn:
        return 5;
    case FigureType::rook:
        return 4;
    case FigureType::queen:
        return 1;
    case FigureType::bishop:
        return 2;
    case FigureType::knight:
        return 3;
    case FigureType::invalid:
        return -1;
    }
}

void UI::changeFigureType(FigureType newType, TeamColor color, int posX, int posY)
{
    char c1;

    posX -= 1;

    switch (posX)
    {
    case 0:
        c1 = 'A';
        break;
    case 1:
        c1 = 'B';
        break;
    case 2:
        c1 = 'C';
        break;
    case 3:
        c1 = 'D';
        break;
    case 4:
        c1 = 'E';
        break;
    case 5:
        c1 = 'F';
        break;
    case 6:
        c1 = 'G';
        break;
    case 7:
        c1 = 'H';
        break;
    default:
        c1 = 'X';
        break;
    }

    int type = typeToInt(newType);
    std::string col = color == TeamColor::white ? "white" : "black";
    std::cout << "Figure " << c1 << posY << "changed to " << type << " " << col << "\n";
}

void UI::updateBoard()
{
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {

        }
    }
}

void UI::updateNotation(std::vector<std::string> notation, int index)
{
    std::cout << "Unimplemented... \n";
}
