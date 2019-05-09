#include <utility>
#include <iostream>

//
// Created by Jozef on 4/24/2019.
//

#include "Notation.h"

#include "NotationMovement.h"
#include "MovementManager.h"
#include "FiguresManager.h"

#include <fstream>
#include <sstream>
#include <regex>
#include <cctype>

Notation::Notation(std::string path)
{
    this->filePath = path;
    if(!this->getFileContent())
        this->isRight = false;

    this->indexProcNotMov = 0;
    this->isRight = true;

    if(gameNotationLines.empty())
    {
        this->isEmpty = true;
        this->isLongNotation = true;
    }
    else
    {
        this->isEmpty = false;
        this->processNotation();
    }

    if(!this->isRight)
        this->setWrongNotation();
}

Notation::~Notation()
{
    int length = this->notationMovements.size();
    NotationMovement *notationMovement = nullptr;
    for (int i = length-1; i >= 0; --i)
    {
        notationMovement = this->notationMovements.back();
        this->notationMovements.pop_back();
        delete notationMovement;
    }
}

bool Notation::getFileContent()
{
    std::ifstream in(this->filePath);
    //std::ifstream in("/icp/subor");
    //std::ifstream in("C:\\Users\\Jozef\\Desktop\\subor2.txt");

    if(!in)
    {
        std::cout << "Cannot open input file.\n";
        return false;
    }

    std::string str;
    while (std::getline(in, str))
    {
        if(str.length()>0)
            this->gameNotationLines.push_back(str);
    }

    in.close();

    return true;
}

void Notation::processNotation()
{
    int lenght = (int)this->gameNotationLines.size();
    for (int i = 0; i<lenght; i++)
    {
        std::string line = this->gameNotationLines.at((unsigned long)i);

        trim(line);
        std::vector<std::string> lineArray;
        split( line, lineArray, ' ' );
        removeSpaces(lineArray);


        if(lineArray.size() != 3)
        {
            if((i+1)!=lenght)
                this->isRight = false;
            else if(lineArray.size()!=2)
                this->isRight = false;
        }

        try
        {
            if((i+1) != std::stoi(lineArray.at(0).substr(0, lineArray.at(0).size()-1)))
                this->isRight = false;
        }
        catch (std::invalid_argument& e)
        {
            this->isRight = false;
        }


        NotationMovement *mov = new NotationMovement();
        if(!mov->setNotationMovementFromString(lineArray.at(1)))
            this->isRight = false;
        this->notationMovements.push_back(mov);

        if(i==0)
            this->isLongNotation = mov->getIsLongNotation();
        else
            if(this->isLongNotation != mov->getIsLongNotation())
                this->isRight = false;

        if(lineArray.size() > 2)
        {
            mov = new NotationMovement();
            if(!mov->setNotationMovementFromString(lineArray.at(2)))
                this->isRight = false;
            this->notationMovements.push_back(mov);
            if(this->isLongNotation != mov->getIsLongNotation())
                this->isRight = false;
        }
    }
}


void Notation::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void Notation::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Notation::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void Notation::removeSpaces(std::vector<std::string> &vec)
{
    int length = (int)vec.size();
    for(int i = 0; i<length;)
    {
        std::string s = vec.at((unsigned long)i);
        if(s.compare("")==0)
        {
            vec.erase(vec.begin()+i);
            length--;
        } else
        {
            i++;
        }

    }
}


size_t Notation::split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}


void Notation::addPlayerNotationMovement(FiguresManager *figuresManager, MovementManager *movementManager)
{
    this->removeUselessNotMovs();
    this->removeUselessLines();

    NotationMovement *mov = new NotationMovement();
    mov->setNotationMovementFromUserMov(this->isLongNotation, figuresManager, movementManager);
    this->notationMovements.push_back(mov);
    this->indexProcNotMov++;
    this->addNotMovToNotationLines(figuresManager, movementManager, mov);
}

void Notation::removeUselessNotMovs()
{
    while(this->indexProcNotMov < (int)this->notationMovements.size())
    {
        NotationMovement *mov = this->notationMovements.at(this->indexProcNotMov);
        this->notationMovements.erase(this->notationMovements.begin() + (this->indexProcNotMov));
        delete mov;
    }
}

void Notation::removeUselessLines()
{
    int linesIndex = (this->indexProcNotMov+1)/2;
    int linesFlag = (this->indexProcNotMov+1)%2;

    int linesToRemove = this->gameNotationLines.size() - linesIndex;

    for (int i = 0; i < linesToRemove;i++)
    {
        this->gameNotationLines.pop_back();
    }

    if(linesFlag==0 && linesToRemove!=0)
    {
        std::string s = this->gameNotationLines.back();
        this->gameNotationLines.pop_back();

        trim(s);

        std::vector<std::string> lineArray;
        split( s, lineArray, ' ' );
        removeSpaces(lineArray);

        s = ""+lineArray.at(0)+" "+lineArray.at(1);
        trim(s);
        this->gameNotationLines.push_back(s);
    }
}

void Notation::addNotMovToNotationLines(FiguresManager *figuresManager, MovementManager *movementManager,
                              NotationMovement *mov)
{
    int linesIndex = (this->indexProcNotMov+1)/2;
    int linesFlag = (this->indexProcNotMov+1)%2;
    std::string s;

    if(linesFlag == 1)
    {
        s = this->gameNotationLines.back();
        this->gameNotationLines.pop_back();
        trim(s);
        s = s + " ";

    }
    else
    {
        s = ""+ std::to_string(linesIndex) +". ";
    }

    if(movementManager->getIsWhiteOnTheMove())
        s = s + mov->getGeneratedStrOfNotMov(figuresManager->getActiveWhiteFigures(),
                                            movementManager->getMovementFigure(), movementManager->getStartField());
    else
        s = s + mov->getGeneratedStrOfNotMov(figuresManager->getActiveBlackFigures(),
                                            movementManager->getMovementFigure(), movementManager->getStartField());
    this->gameNotationLines.push_back(s);
}

bool Notation::saveNotation()
{
    std::ofstream myfile;
    myfile.open(this->filePath);
    if(!myfile.is_open())
    {
        return false;
    }

    int length = (int)this->gameNotationLines.size();
    std::string str;
    for (int i = 0; i < length; ++i)
    {
        str = this->gameNotationLines.at(i);
        myfile << str <<std::endl;
    }
    myfile.close();
    return true;
}

bool Notation::isFirstIndex()
{
    if(this->indexProcNotMov == 0)
        return true;
    else
        return false;
}


bool Notation::isLastIndex()
{
    if (this->indexProcNotMov == (int)this->notationMovements.size())
        return true;
    else
        return false;
}

std::vector<std::string> Notation::getGameNotationLines()
{
    return this->gameNotationLines;
}

int Notation::getIndexProcNotMov()
{
    return (this->indexProcNotMov-1)/2;
}

bool Notation::getIsEmpty()
{
    return this->isEmpty;
}

NotationMovement *Notation::getActualNotMov()
{
    return this->notationMovements.at((unsigned long)(this->indexProcNotMov));
}

void Notation::incrementIndexOfNotationLines()
{
    this->indexProcNotMov++;
}

void Notation::decrementIndexOfNotationLines()
{
    this->indexProcNotMov--;
}

int Notation::getChangingFigureID()
{
    return this->getActualNotMov()->getChangingFigureID();
}

void Notation::completeNotationMovement(MovementManager *movementManager)
{
    this->notationMovements.at((unsigned long)this->indexProcNotMov-1)->completeNotationMovement(movementManager);
}

NotationMovement *Notation::getPrevNotationMovement()
{
    return this->notationMovements.at((unsigned long)this->indexProcNotMov-1);
}

bool Notation::getIsRight ()
{
    return this->isRight;
}

void Notation::setWrongNotation()
{
    this->gameNotationLines.clear();
    this->gameNotationLines.emplace_back("Chess notation is incorrect!");
}
