/**
 * Trieda reprezentuje notáciu jedneho ťahu hry.
 * @author Jozef Ondria
 */

#include "NotationMovement.h"

#include "MovementManager.h"
#include "FiguresManager.h"
#include "Field.h"
#include "Figure.h"

#include <regex>
#include <stdio.h>


/**
 * Inicializuje ťah notácie.
 */
NotationMovement::NotationMovement()
{
    this->startFieldCol = -1;
    this->startFieldRow = -1;
    this->movementFigureID = -1;
    this->goalFieldCol = -1;
    this->goalFieldRow = -1;
    this->changingFigureID = -1;
}


/**
* Nastaví ťah notácie z uživateľoveho ťahu. Je to dôležite pre budúce volanie ťahov spať.
* @param isLongNotation Informacia či ide o krátku/dlhú formu zápisu.
* @param figuresManager Manažer aktivných/pasívnych figúrok.
* @param movementManager Manažer realneo ťahu.
*/
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


/**
 * Nastavuje ťah notácie zo zápisu z notácie.
 * @param s Reťazec zápisu ťahu.
 * @return Úspešnosť operácie.
 */
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


/**
 * Vráti ID typu figúrky zo stringoveho označenia figúrky.
 * @param s Označenie figúrky.
 * @return ID figúrky.
 */
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


/**
 * Vratia stringove označenie figúrky z ID figúrky.
 * @param id ID figúrky.
 * @return Označenie figúrky.
 */
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


/**
 * Vráti poradie stlpca políčka na šachovnici.
 * @param s Označenie stlpca.
 * @return Poradie stlpca.
 */
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


/**
 * Vráti označenie stlpca políčka z jeho poradia označenia.
 * @param i Poradie stlpca.
 * @return Označenie stlpca.
 */
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


/**
 * Vracia infomáciu o tom či ide o dlhý zápis ťahu v notácii.
 * @return Pravdivostna hodnota.
 */
bool NotationMovement::getIsLongNotation()
{
    return this->isLongNotation;
}


/**
 * Vygeneruje string/zapis ťahu z tohto ťahu notácie.
 * @param activeFigures Aktívne figúrky na šachovnici - štruktúra.
 * @param movementFigure Posúvacia figúrka.
 * @param startFieldOfMovementFig Štartovacie políčko ťahu.
 * @return Vygenerovaný string.
 */
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


/**
 * Vracia stlpec štartovaciaho políčka.
 * @return
 */
int NotationMovement::getStartFieldCol()
{
    return this->startFieldCol;
}


/**
 * Vracia riadok štartovaciaho políčka.
 * @return
 */
int NotationMovement::getStartFieldRow()
{
    return this->startFieldRow;
}


/**
 * Vracia stlpec cieľoveho políčka.
 * @return
 */
int NotationMovement::getGoalFieldCol()
{
    return this->goalFieldCol;
}


/**
 * Vracia riadok cieľoveho políčka.
 * @return
 */
int NotationMovement::getGoalFieldRow()
{
    return this->goalFieldRow;
}


/**
 * Vracia ID figúrky kotorá je pri ťahu posúvaná.
 * @return ID figúrky.
 */
int NotationMovement::getMovementFigureID()
{
    return this->movementFigureID;
}


/**
 * Vracia ID figúrky kotorá je zamenená za pešiaka.
 * @return ID figúrky.
 */
int NotationMovement::getChangingFigureID()
{
    return this->changingFigureID;
}


/**
 * Vracia ID figúrky kotorá je vyhodená.
 * @return ID figúrky.
 */
bool NotationMovement::getIsFigureRemoving()
{
    return this->isFigureRemoving;
}


/**
 * Vráti informáciu o tom či je v tomto ťahu šach.
 * @return Pravdivostna hodnota.
 */
bool NotationMovement::getIsChess()
{
    return this->isChess;
}


/**
 * Vráti informáciu o tom či je v tomto ťahu šachmat.
 * @return Pravdivostna hodnota.
 */
bool NotationMovement::getIsChessMat()
{
    return this->isChessMat;
}


/**
 * Zkompletuje ťah notácie z ťahu užívateľa.
 * @param movementManager Manážer realneho ťahu.
 */
void NotationMovement::completeNotationMovement(MovementManager *movementManager)
{
    if(this->startFieldCol == -1)
        this->startFieldCol = movementManager->getStartField()->getColPos();

    if(this->startFieldRow == -1)
        this->startFieldRow = movementManager->getStartField()->getRowPos();
}
