//
// Created by Jozef on 5/3/2019.
//

#include "NotationMovement.h"

#include "MovementManager.h"
#include "FiguresManager.h"
#include "Field.h"
#include "Figure.h"

#include <regex>
#include <stdio.h>

NotationMovement::NotationMovement()
{
    this->startFieldCol = -1;
    this->startFieldRow = -1;
    this->movementFigureID = -1;
    this->goalFieldCol = -1;
    this->goalFieldRow = -1;
    this->changingFigureID = -1;
}

void NotationMovement::setNotationMovementFromUserMov(bool isLongNotation, FiguresManager *figuresManager, MovementManager *movementManager)
{
    this->isLongNotation = isLongNotation;
    this->startFieldCol = movementManager->getStartField()->getColPos();
    this->startFieldRow = movementManager->getStartField()->getRowPos();
    this->movementFigureID = movementManager->getMovementFigure()->getID();
    this->goalFieldCol = movementManager->getGoalField()->getColPos();
    this->goalFieldRow = movementManager->getGoalField()->getRowPos();
    if(movementManager->getIsChangingFigure())
        this->changingFigureID = movementManager->getGoalField()->get()->getID();
    this->isFigureRemoving = movementManager->getIsRemovingFigure();
    this->isChessMat = figuresManager->getChessMat();
    if(this->isChessMat)
        this->isChess = false;
    else
        this->isChess = figuresManager->getChess();
}

bool NotationMovement::setNotationMovementFromString(std::string s)
{
    if(std::regex_match(s, std::regex("[KDVSJ]?[abcdefgh][12345678][x]?[abcdefgh][12345678][VDSJ]?[+#]?")))
    {
        this->isLongNotation = true;

        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]+[#]")))
        {
            this->isChessMat = true;
            s.erase(std::remove(s.begin(), s.end(), '#'), s.end());
        }
        else
            this->isChessMat = false;


        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]+[+]")))
        {
            this->isChess = true;
            s.erase(std::remove(s.begin(), s.end(), '+'), s.end());
        }
        else
             this->isChess = false;

        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]*[x][a-zA-Z_0-9]+")))
        {
            this->isFigureRemoving = true;
            s.erase(std::remove(s.begin(), s.end(), 'x'), s.end());
        }
        else
            this->isFigureRemoving = false;


        std::string figure = "";
        if(std::regex_match(s, std::regex("[KDVSJ][a-zA-Z_0-9]+")))
        {
            figure = "";
            std::regex rgx("([KDVSJ])\\w+");
            std::smatch match;
            if (std::regex_search(s, match, rgx))
                figure =  match[1];

            this->movementFigureID = getFigureID(figure);
        }
        else
            this->movementFigureID = getFigureID("p");


        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]+[VDSJ]")))
        {
            figure = "";
            std::regex rgx("\\w+([VDSJ])");
            std::smatch match;
            if (std::regex_search(s, match, rgx))
                figure = match[1];

            this->changingFigureID = getFigureID(figure);
        }
        else
            this->changingFigureID = -1;


        if(std::regex_match(s, std::regex("[KDVSJ]?[abcdefgh][12345678][abcdefgh][12345678][VDSJ]?")))
        {
            figure = "";
            std::regex rgx("[KDVSJ]?([abcdefgh])[12345678][abcdefgh][12345678][VDSJ]?");
            std::smatch match;
            if (std::regex_search(s, match, rgx))
                figure = match[1];

            this->startFieldCol = getIntFieldColumn(figure);


            figure = "";
            std::regex rgx1("[KDVSJ]?[abcdefgh]([12345678])[abcdefgh][12345678][VDSJ]?");
            std::smatch match1;
            if (std::regex_search(s, match1, rgx1))
                figure = match1[1];

            if(figure.compare("")!=0)
                this->startFieldRow = std::stoi(figure);
            else
                this->startFieldRow = -1;


            figure = "";
            std::regex rgx2("[KDVSJ]?[abcdefgh][12345678]([abcdefgh])[12345678][VDSJ]?");
            std::smatch match2;
            if (std::regex_search(s, match2, rgx2))
                figure = match2[1];
            this->goalFieldCol = getIntFieldColumn(figure);

            figure = "";
            std::regex rgx3("[KDVSJ]?[abcdefgh][12345678][abcdefgh]([12345678])[VDSJ]?");
            std::smatch match3;
            if (std::regex_search(s, match3, rgx3))
                figure = match3[1];

            if(figure.compare("")!=0)
                this->goalFieldRow = std::stoi(figure);
            else
                this->startFieldRow = -1;
        }
        else
        {
            return false;
        }
    }
    else if(std::regex_match(s, std::regex("[KDVSJ]?[abcdefgh12345678]?[x]?[abcdefgh][12345678][VDSJ]?[+#]?")))
    {
        this->isLongNotation = false;

        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]+[#]")))
        {
            this->isChessMat = true;
            s.erase(std::remove(s.begin(), s.end(), '#'), s.end());
        }
        else
            this->isChessMat = false;

        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]+[+]")))
        {
            this->isChess = true;
            s.erase(std::remove(s.begin(), s.end(), '+'), s.end());
        }
        else
            this->isChess = false;


        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]*[x][a-zA-Z_0-9]+")))
        {
            this->isFigureRemoving = true;
            s.erase(std::remove(s.begin(), s.end(), 'x'), s.end());
        }
        else
            this->isFigureRemoving = false;


        std::string figure = "";
        if(std::regex_match(s, std::regex("[KDVSJ][a-zA-Z_0-9]+")))
        {
            std::regex rgx("([KDVSJ])\\w+");
            std::smatch match;
            if (std::regex_search(s, match, rgx))
                figure = match[1];

            this->movementFigureID = getFigureID(figure);
        }
        else
            this->movementFigureID = getFigureID("p");

        if(std::regex_match(s, std::regex("[a-zA-Z_0-9]+[VDSJ]")))
        {
            figure = "";
            std::regex rgx("\\w+([VDSJ])");
            std::smatch match;
            if (std::regex_search(s, match, rgx))
                figure = match[1];

            this->changingFigureID = getFigureID(figure);
        }
        else
            this->changingFigureID = -1;

        if(std::regex_match(s, std::regex("[KDVSJ]?[abcdefgh12345678]?[abcdefgh][12345678][VDSJ]?")))
        {
            figure = "";
            std::regex rgx("[KDVSJ]?([abcdefgh12345678])[abcdefgh][12345678][VDSJ]?");
            std::smatch match;
            if (std::regex_search(s, match, rgx))
                figure = match[1];


            if(figure.compare("")!=0)
            {
                this->startFieldCol = getIntFieldColumn(figure);
                if(this->startFieldCol == -1)
                    this->startFieldRow = std::stoi(figure);
                else
                    this->startFieldRow = -1;
            }
            else
            {
                this->startFieldCol = -1;
                this->startFieldRow = -1;
            }

            figure = "";
            std::regex rgx1("[KDVSJ]?[abcdefgh12345678]?([abcdefgh])[12345678][VDSJ]?");
            std::smatch match1;
            if (std::regex_search(s, match1, rgx1))
                figure = match1[1];

            this->goalFieldCol = getIntFieldColumn(figure);

            figure = "";
            std::regex rgx2("[KDVSJ]?[abcdefgh12345678]?[abcdefgh]([12345678])[VDSJ]?");
            std::smatch match2;
            if (std::regex_search(s, match2, rgx2))
                figure = match2[1];

            if(figure.compare("")!=0)
                this->goalFieldRow = std::stoi(figure);
            else
                this->startFieldRow = -1;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

int NotationMovement::getFigureID(std::string s)
{
    if (s.compare("")==0)
        return -1;

    if (s.compare("K")==0)
        return 0;
    else if(s.compare("D")==0)
        return 1;
    else if(s.compare("S")==0)
        return 2;
    else if(s.compare("J")==0)
        return 3;
    else if(s.compare("V")==0)
        return 4;
    else if(s.compare("p")==0)
        return 5;
    else
        return -1;
}


std::string NotationMovement::getStrFigureID(int id)
{
    if (id==0)
        return "K";
    else if(id==1)
        return "D";
    else if(id==2)
        return "S";
    else if(id==3)
        return "J";
    else if(id==4)
        return "V";
    else if(id==5)
        return "";
    else
        return nullptr;
}

int NotationMovement::getIntFieldColumn(std::string s)
{
    if (s.compare("")==0)
        return -1;

    if (s.compare("a")==0)
        return 1;
    else if(s.compare("b")==0)
        return 2;
    else if(s.compare("c")==0)
        return 3;
    else if(s.compare("d")==0)
        return 4;
    else if(s.compare("e")==0)
        return 5;
    else if(s.compare("f")==0)
        return 6;
    else if(s.compare("g")==0)
        return 7;
    else if(s.compare("h")==0)
        return 8;
    else
        return -1;
}
std::string  NotationMovement::getStrFieldColumn(int i)
{
    if (i==1)
        return "a";
    else if(i==2)
        return "b";
    else if(i==3)
        return "c";
    else if(i==4)
        return "d";
    else if(i==5)
        return "e";
    else if(i==6)
        return "f";
    else if(i==7)
        return "g";
    else if(i==8)
        return "h";
    else
        return nullptr;
}

bool NotationMovement::getIsLongNotation()
{
    return this->isLongNotation;
}

std::string NotationMovement::getGeneratedStrOfNotMov(std::vector<Figure*> activeFigures, Figure *movementFigure, Field *startFieldOfMovementFig)
{
    std::string s = "";
    if (this->isLongNotation)
    {
        s = s+getStrFigureID(this->movementFigureID);
        s = s+getStrFieldColumn(this->startFieldCol);
        s = s+std::to_string(this->startFieldRow);
        if(this->isFigureRemoving)
            s = s+"x";
        s = s+getStrFieldColumn(this->goalFieldCol);
        s = s+std::to_string(this->goalFieldRow);
        if(this->changingFigureID!=-1)
            s = s+getStrFigureID(this->changingFigureID);
        if(this->isChess)
            s = s+"+";
        if(this->isChessMat)
            s = s+"#";

    }
    else
    {
        s = s+getStrFigureID(this->movementFigureID);

        std::vector<Figure*> tmp(activeFigures);

        int length = (int)tmp.size();
        for(int i = 0; i<length; i++)
        {
            if(tmp.at((unsigned long)i)->getID() == this->movementFigureID)
            {
                std::vector<Field*> fields = tmp.at((unsigned long)i)->getFieldsInDanger();
                if(tmp.at((unsigned long)i) != movementFigure
                        && std::find(fields.begin(), fields.end(), movementFigure->getActualField()) != fields.end())
                {
                    if(startFieldOfMovementFig->getColPos() != tmp.at((unsigned long)i)->getActualField()->getColPos())
                        s = s + getStrFieldColumn(startFieldOfMovementFig->getColPos());
                    else
                        s = s + std::to_string(startFieldOfMovementFig->getRowPos());

                    break;
                }
            }
        }

        if(this->isFigureRemoving)
            s = s+"x";
        s = s+getStrFieldColumn(this->goalFieldCol);
        s = s+ std::to_string(this->goalFieldRow);
        if(this->changingFigureID!=-1)
            s = s+getStrFigureID(this->changingFigureID);
        if(this->isChess)
            s = s+"+";
        if(this->isChessMat)
            s = s+"#";
    }

    return s;
}

int NotationMovement::getStartFieldCol()
{
    return this->startFieldCol;
}

int NotationMovement::getStartFieldRow()
{
    return this->startFieldRow;
}

int NotationMovement::getGoalFieldCol()
{
    return this->goalFieldCol;
}

int NotationMovement::getGoalFieldRow()
{
    return this->goalFieldRow;
}

int NotationMovement::getMovementFigureID()
{
    return this->movementFigureID;
}

int NotationMovement::getChangingFigureID()
{
    return this->changingFigureID;
}

bool NotationMovement::getIsFigureRemoving()
{
    return this->isFigureRemoving;
}

bool NotationMovement::getIsChess()
{
    return this->isChess;
}

bool NotationMovement::getIsChessMat()
{
    return this->isChessMat;
}

void NotationMovement::completeNotationMovement(MovementManager *movementManager)
{
    if(this->startFieldCol == -1)
        this->startFieldCol = movementManager->getStartField()->getColPos();

    if(this->startFieldRow == -1)
        this->startFieldRow = movementManager->getStartField()->getRowPos();
}
