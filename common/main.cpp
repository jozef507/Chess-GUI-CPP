#include <iostream>
#include "Board.h"
#include "FigurePawn.h"
#include "Game.h"
#include "GameChess.h"
using namespace std;
int main(void)
{


    Game *game = new GameChess("C:\\Users\\Jozef\\Desktop\\notations\\subor2.txt");

    if(game->getIsFieldEmpty(1,1))
        printf("Je prazdna;\n");
    else
        printf("Neni prazdna\n");

    if(game->getIsFieldEmpty(1,2))
        printf("Je prazdna;\n");
    else
        printf("Neni prazdna\n");

    if(game->getIsFieldEmpty(1,3))
        printf("Je prazdna;\n");
    else
        printf("Neni prazdna\n");

    if(game->getIsFieldEmpty(1,4))
        printf("Je prazdna;\n");
    else
        printf("Neni prazdna\n");

    if(game->getIsFieldEmpty(8,8))
        printf("Je prazdna;\n");
    else
        printf("Neni prazdna\n");

    for (int i = 0; i < 77; ++i) {
        game->setPlaybackMovement();
        game->performPlaybackMovement();
        if(game->getIsChangingFigure())
        {
            game->createNewFigure(game->getChangingFigureID());
        }
        game->incrementIndexOfNotationLines();
        game->completeNotationMovement();
        game->nullMovementManager();
        game->changePlayer();
    }


    for (int i = 76; i >=39; --i) {
        game->setPlaybackUndoMovement();
        game->performPlaybackUndoMovement();
        game->decrementIndexOfNotationLines();
        game->nullMovementManager();
    }


    game->setPlayerMovement(3,4);
    game->setPlayerMovement(2,3);
    bool movement = game->performPlayerMovement();

    game->addPlayerNotationMovement();
    game->completeNotationMovement();
    game->nullMovementManager();
    game->changePlayer();


    game->setPlayerMovement(6,1);
    game->setPlayerMovement(2,1);
    movement = game->performPlayerMovement();

    game->addPlayerNotationMovement();
    game->completeNotationMovement();
    game->nullMovementManager();
    game->changePlayer();

    game->saveNotationToAnotherFile("C:\\Users\\Jozef\\Desktop\\notations\\subor4.txt");

    delete game;

}