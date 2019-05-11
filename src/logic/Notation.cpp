#include <utility>
#include <iostream>
#include <cctype>

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


/**
* Inicializuje notáciu.
* @param path Cesta k súboru s obsahom notácie.
*/
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

/**
 * Deštruktor.
 */
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


/**
 * Načíta riadky notácie zo súboru do vectoru pre zapis notacie.
 * @return Úspešnosť operácie.
 */
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


/**
* Prechádza celú notáciu zo súboru a postupne spracováva riadok za riadkom a ťah za ťahom.
* Každý ťah konvertuje na inštanciu triedy NotationMovement ktorý reprezentuje jeden ťah zápisu.
* Zneho sa vyberajú najdôležitejšie informacie o ťahu a to pri prehrávaní partii.
*/
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


/**
 * Vlastná funkcia pre odseknutie ľavých bielych znakov.
 * @param s Reťazec pre osekanie.
 */
void Notation::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}


/**
 * Vlastná funkcia pre odseknutie pravých bielych znakov.
 * @param s Reťazec pre osekanie.
 */
void Notation::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}


/**
 * Vlastná funkcia pre odseknutie bielych znakov z ľavej a pravej strany.
 * @param s Reťazec pre osekanie.
 */
void Notation::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


/**
 * Odstraňuje z vectoru notacie riadky ktoré sú prázdne.
 * @param vec Vector riadkov notácie.
 */
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


/**
 * Rozdelí string podľa oddeľovača.
 * @param txt Režazec na rozdelenie.
 * @param strs Vector pre naplnenie oddelených častí.
 * @param ch Oddeľovač
 * @return Počet oddelenych elementov.
 */
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


/**
* Pri vlastnom ťahu užívateľa táto metóda odstráni ďalšie už zbytočné ťahy z notácie
* a prída ťah užívateľa v do tejto notácii.
* @param figuresManager Manažer aktívnych/pasívnych figúrok.
* @param movementManager Manažer ťahu.
*/
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


/**
 * Pomocná funkcia pre odstranenie všetkých už nepotrebných ťahov zo štrúktúry pre NotationMovements.
 */
void Notation::removeUselessNotMovs()
{
    while(this->indexProcNotMov < (int)this->notationMovements.size())
    {
        NotationMovement *mov = this->notationMovements.at(this->indexProcNotMov);
        this->notationMovements.erase(this->notationMovements.begin() + (this->indexProcNotMov));
        delete mov;
    }
}


/**
 * Odstráni zo zápisu notácie (stringovo) už nepotrebne riadky tejto notácie.
 */
void Notation::removeUselessLines()
{
    int linesIndex = (this->indexProcNotMov+1)/2;
    int linesFlag = (this->indexProcNotMov+1)%2;

    int linesToRemove = this->gameNotationLines.size() - linesIndex;

    for (int i = 0; i < linesToRemove;i++)
    {
        this->gameNotationLines.pop_back();
    }

    if(linesFlag==0 /*&& linesToRemove!=0*/)
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


/**
 * Pridá jeden ťah reprezentovaný NotationMovementom do zápisu notácie.
 * @param figuresManager Manžer aktívnych/pasívnych figúrok.
 * @param movementManager Manažer logického ťahu.
 * @param mov Ťah notácie.
 */
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


/**
 * Uloži notáciu do súboru z ktorého bola načítaná.
 * @return Úspešnosť uloženia.
 */
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


/**
    * Uloži notáciu do súboru zadanom v parametri funkcie.
    * @param path Cesta k danému súboru.
    * @return Úspešnosť uloženia.
    */
bool Notation::saveNotationToAnotherFile(std::string path)
{
    std::ofstream myfile;
    myfile.open(path);
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


/**
* Testuje či je index pre štruktúru ťahov notácie nulový ak áno znamena to že sme spracuvávame prvý prvok
* štruktúry.
* @return
*/
bool Notation::isFirstIndex()
{
    if(this->indexProcNotMov == 0)
        return true;
    else
        return false;
}


/**
* Testuje či je index pre štruktúru ťahov notácie poslený, či pracujeme s poslednym prvkom štruktúry.
* @return
*/
bool Notation::isLastIndex()
{
    if (this->indexProcNotMov == (int)this->notationMovements.size())
        return true;
    else
        return false;
}


/**
* Vracia zápis notácie implementovanú riadok po riadku v štruktúre ArrayList.
* @return Štruktúru notácie.
*/
std::vector<std::string> Notation::getGameNotationLines()
{
    return this->gameNotationLines;
}


/**
* Vracia index aktuálneho spracovaneho ťahu notácie ale prevedený na riadok notácie.
* @return
*/
int Notation::getIndexProcNotMov()
{
    return (this->indexProcNotMov-1)/2;
}


/**
* Testovanie či je notácia prázdna.
* @return Výsledok testu.
*/
bool Notation::getIsEmpty()
{
    return this->isEmpty;
}


/**
* Vráti inštanciu/objekt triedy NotationMovement pre ťah ktorý sa aktuálne spracúváva.
* @return
*/
NotationMovement *Notation::getActualNotMov()
{
    return this->notationMovements.at((unsigned long)(this->indexProcNotMov));
}


/**
* Inkrementuje index určujúci aktuálny spracovávaný ťah notácie.
*/
void Notation::incrementIndexOfNotationLines()
{
    this->indexProcNotMov++;
}


/**
* Dekrementuje index určujúci aktuálny spracovávaný ťah notácie.
*/
void Notation::decrementIndexOfNotationLines()
{
    this->indexProcNotMov--;
}


/**
* Vráti ID figúrky ktorá má v danom ťahu vymeniť pešiaka.
* @return Hodnota ID.
*/
int Notation::getChangingFigureID()
{
    return this->getActualNotMov()->getChangingFigureID();
}


/**
* Pri postupnom prehrávani/hraní partie táto metóda doplnňuje chýbajúce informácie do
* aktuálneho ťahu notácie. (napríklad pri krátkom formáte notácie to je štartovacie políčko,
* využívane neskôr pri kroku spať)
* @param movementManager Manažer ťahu.
*/
void Notation::completeNotationMovement(MovementManager *movementManager)
{
    this->notationMovements.at((unsigned long)this->indexProcNotMov-1)->completeNotationMovement(movementManager);
}


/**
* Vracia inštanciu triedy NotationMovement pre ťah inštancie predchadzajúceho ťahu.
* Využíívane pri kroku spať(undo).
* @return
*/
NotationMovement *Notation::getPrevNotationMovement()
{
    return this->notationMovements.at((unsigned long)this->indexProcNotMov-1);
}


/**
* Vracia informáciu o tom či je formát notácie šachovej partie správny.
* @return Pravdivostná hodnota.
*/
bool Notation::getIsRight ()
{
    return this->isRight;
}


/**
* Nastaví notáciu ako nesprávnu chybovou hláškou.
*/
void Notation::setWrongNotation()
{
    this->gameNotationLines.clear();
    this->gameNotationLines.emplace_back("Chess notation is incorrect!");
}
