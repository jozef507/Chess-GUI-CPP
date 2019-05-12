/**
 * Trieda reprezentuje jadro (hlavnu logiku) aplikácie.
 * @author Jozef Ondria
 * @author Jan Holásek
 */

#include "GameChess.h"
#include "MovementManager.h"
#include "FiguresManager.h"
#include "Notation.h"
#include "NotationMovement.h"
#include "FigurePawn.h"
#include "FigureKing.h"
#include "FigureBishop.h"
#include "FigureQueen.h"
#include "FigureKnight.h"
#include "FigureRook.h"
#include "Board.h"



/**
     * Inicializuje partiu hry.
     * @param whiteFigureImages Pole odkzaov na obrázky bielých figúrok.
     * @param blackFigureImages Pole odkzaov na obrázky čiernych figúrok.
     */
GameChess::GameChess(std::string path/*,ImageView[] whiteFigureImages, ImageView[] blackFigureImages*/)
{
    this->board = new Board(8);
    this->movementManager = new MovementManager();
    this->figuresManager = new FiguresManager();
    this->notation = new Notation(path/*GuiGameFactory.stringFilepathArray[GuiGameFactory.counter++]*/);

    this->putPawnOnBoard(1, 2, true/*, whiteFigureImages[0]*/);
    this->putPawnOnBoard(2, 2, true/*, whiteFigureImages[1]*/);
    this->putPawnOnBoard(3, 2, true/*, whiteFigureImages[2]*/);
    this->putPawnOnBoard(4, 2, true/*, whiteFigureImages[3]*/);
    this->putPawnOnBoard(5, 2, true/*, whiteFigureImages[4]*/);
    this->putPawnOnBoard(6, 2, true/*, whiteFigureImages[5]*/);
    this->putPawnOnBoard(7, 2, true/*, whiteFigureImages[6]*/);
    this->putPawnOnBoard(8, 2, true/*, whiteFigureImages[7]*/);
    this->putRookOnBoard(1, 1, true/*, whiteFigureImages[8]*/);
    this->putRookOnBoard(8, 1, true/*, whiteFigureImages[9]*/);
    this->putKnightOnBoard(2, 1, true/*, whiteFigureImages[10]*/);
    this->putKnightOnBoard(7, 1, true/*, whiteFigureImages[11]*/);
    this->putBishopOnBoard(3, 1, true/*, whiteFigureImages[12]*/);
    this->putBishopOnBoard(6, 1, true/*, whiteFigureImages[13]*/);
    this->putQueenOnBoard(4, 1, true/*, whiteFigureImages[14]*/);
    this->putKingOnBoard(5, 1, true/*, whiteFigureImages[15]*/);


    this->putPawnOnBoard(1, 7, false/*, blackFigureImages[0]*/);
    this->putPawnOnBoard(2, 7, false/*, blackFigureImages[1]*/);
    this->putPawnOnBoard(3, 7, false/*, blackFigureImages[2]*/);
    this->putPawnOnBoard(4, 7, false/*, blackFigureImages[3]*/);
    this->putPawnOnBoard(5, 7, false/*, blackFigureImages[4]*/);
    this->putPawnOnBoard(6, 7, false/*, blackFigureImages[5]*/);
    this->putPawnOnBoard(7, 7, false/*, blackFigureImages[6]*/);
    this->putPawnOnBoard(8, 7, false/*, blackFigureImages[7]*/);
    this->putRookOnBoard(1, 8, false/*, blackFigureImages[8]*/);
    this->putRookOnBoard(8, 8, false/*, blackFigureImages[9]*/);
    this->putKnightOnBoard(2, 8, false/*, blackFigureImages[10]*/);
    this->putKnightOnBoard(7, 8, false/*, blackFigureImages[11]*/);
    this->putBishopOnBoard(3, 8, false/*, blackFigureImages[12]*/);
    this->putBishopOnBoard(6, 8, false/*, blackFigureImages[13]*/);
    this->putQueenOnBoard(4, 8, false/*, blackFigureImages[14]*/);
    this->putKingOnBoard(5, 8, false/*, blackFigureImages[15]*/);

    this->figuresManager->setWhiteFieldsInDanger();
    this->figuresManager->setBlackFieldsInDanger();
}

/**
 * Deštruktor.
 */
GameChess::~GameChess()
{
    delete this->notation;
    delete this->figuresManager;
    delete this->movementManager;
    delete this->board;
}


/**
 * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
 * @param col Stlpec políčka kam sa má figúrka vložiť.
 * @param row Riadok políčka kam sa má figúrka vložiť.
 * @param isPawnWhite Informácia o farbe figúrky.
 * @param image Odkaz na obrázok figúrky z grafického rozhrania.
 */
void GameChess::putPawnOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigurePawn *pawn = new FigurePawn(isPawnWhite/*, image*/);
        field->put(pawn);
        this->figuresManager->addActiveFigure(pawn);
    }
}


/**
 * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
 * @param col Stlpec políčka kam sa má figúrka vložiť.
 * @param row Riadok políčka kam sa má figúrka vložiť.
 * @param isRookWhite Informácia o farbe figúrky.
 * @param image Odkaz na obrázok figúrky z grafického rozhrania.
 */
void GameChess::putRookOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureRook *rook = new FigureRook(isPawnWhite/*, image*/);
        field->put(rook);
        this->figuresManager->addActiveFigure(rook);

    }
}


/**
 * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
 * @param col Stlpec políčka kam sa má figúrka vložiť.
 * @param row Riadok políčka kam sa má figúrka vložiť.
 * @param isRookWhite Informácia o farbe figúrky.
 * @param image Odkaz na obrázok figúrky z grafického rozhrania.
 */
void GameChess::putKnightOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureKnight *knight = new FigureKnight(isPawnWhite/*, image*/);
        field->put(knight);
        this->figuresManager->addActiveFigure(knight);

    }
}


/**
 * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
 * @param col Stlpec políčka kam sa má figúrka vložiť.
 * @param row Riadok políčka kam sa má figúrka vložiť.
 * @param isRookWhite Informácia o farbe figúrky.
 * @param image Odkaz na obrázok figúrky z grafického rozhrania.
 */
void GameChess::putBishopOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureBishop *bishop = new FigureBishop(isPawnWhite/*, image*/);
        field->put(bishop);
        this->figuresManager->addActiveFigure(bishop);
    }
}


/**
 * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
 * @param col Stlpec políčka kam sa má figúrka vložiť.
 * @param row Riadok políčka kam sa má figúrka vložiť.
 * @param isRookWhite Informácia o farbe figúrky.
 * @param image Odkaz na obrázok figúrky z grafického rozhrania.
 */
void GameChess::putQueenOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureQueen *queen = new FigureQueen(isPawnWhite/*, image*/);
        field->put(queen);
        this->figuresManager->addActiveFigure(queen);

    }
}


/**
  * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
  * @param col Stlpec políčka kam sa má figúrka vložiť.
  * @param row Riadok políčka kam sa má figúrka vložiť.
  * @param isRookWhite Informácia o farbe figúrky.
  * @param image Odkaz na obrázok figúrky z grafického rozhrania.
  */
void GameChess::putKingOnBoard(int col, int row, bool isPawnWhite)
{
    Field *field = this->board->getField(col, row);
    if (field->isEmpty()) {
        FigureKing *king = new FigureKing(isPawnWhite/*, image*/);
        field->put(king);
        this->figuresManager->addActiveFigure(king);
        this->figuresManager->setKing(king);
    }
}


/**
* Vracia cieľové políčko momentálne nastaveného ťahu.
* @return Objekt políčka.
*/
Field *GameChess::getGoalField() {
    return this->movementManager->getGoalField();
}

/**
 * Mení v jadre programu hráča, ktorý je na ťahu.
 */
void GameChess::changePlayer() { this->movementManager->changePlayer(); }

/**
 * Nastaví informáciu o tom či môže užívateľ vykonávať vlastné ťahy.
 * @param canPlayerPlay Hodnota informácie.
 */
void GameChess::setCanPlayerPlay(bool canPlayerPlay) {
    this->movementManager->setCanPlayerPlay(canPlayerPlay);
}

/**
 * Vynuluje informacie o ťahu v logike ktorý je reprezentovaný triedy MovementManager,
 * a tým pripraví jadro(logiku) na ďalší ťah.
 */
void GameChess::nullMovementManager() { this->movementManager->nullMovementManager(); }

/**
 * Nastavuje informácie o najbližšom ťahu hráča, ktorý sa má vykonať.
 * @param col Stĺpec políčka ktoré sa má do ťahu nastaviť.
 * @param row Riadok políčka ktoré sa má do ťahu nastaviť.
 * @return Úspešnosť metódy.
 */
bool GameChess::setPlayerMovement(int col, int row)
{
    return this->movementManager->setPlayerMovement(col, row, this->board);
}

/**
 * Nastavuje informácie o najbližšom prehrávanom ťahu, ktorý sa má vykonať. Tieto informácie
 * sa vyberú z notácie partie.
 * @return Úspešnosť metódy.
 */
bool GameChess::setPlaybackMovement()
{
    return this->movementManager->setPlaybackMovement(this->board, this->notation, this->figuresManager);
}

/**
 * Vykonáva už nastavený ťah hráča v jadre programu.
 * @return Úspešnosť ťahu.
 */
bool GameChess::performPlayerMovement()
{
    return this->movementManager->performMovement(this->figuresManager);
}

/**
 * Vykonáva už nastavený prehrávaný ťah v jadre programu.
 * @return Úspešnosť ťahu.
 */
bool GameChess::performPlaybackMovement()
{
    bool flag = this->movementManager->performMovement(this->figuresManager);
    if (!flag)
        return false;

    if(this->movementManager->getIsRemovingFigure() != this->notation->getActualNotMov()->getIsFigureRemoving())
    {
        this->notation->setIsRight(false);
        return false;
    }

    if((this->movementManager->getIsChangingFigure()))
    {
        if(this->notation->getActualNotMov()->getChangingFigureID() == -1)
        {
            this->notation->setIsRight(false);
            return false;
        }
    }
    else
    {
        if(this->notation->getActualNotMov()->getChangingFigureID() != -1)
        {
            this->notation->setIsRight(false);
            return false;
        }
    }

    if(this->figuresManager->getChessMat() != this->notation->getActualNotMov()->getIsChessMat())
    {
        if(this->figuresManager->getChess() != this->notation->getActualNotMov()->getIsChess())
        {
            this->notation->setIsRight(false);
            return false;
        }
    }


    return true;
}

/**
 * Nastaví momentálny ťah v jadre programu a testuje správnosť/povolenosť ťahu.
 * @return Úspešnosť testu.
 */
bool GameChess::setPlaybackUndoMovement()
{
    return this->movementManager->setPlaybackUndoMovement(this->notation->getPrevNotationMovement(), this->board, this->figuresManager);
}

/**
 * Vykonáva momentálne nastavený ťah v jadre programu a testuje správnosť/povolenosť ťahu.
 * @return Úspešnosť testu.
 */
bool GameChess::performPlaybackUndoMovement()
{
    return this->movementManager->performPlaybackUndoMovement(this->notation->getPrevNotationMovement(), this->figuresManager);
}

/**
 * @return Informáciu o tom či je na ťahu biely hráč.
 */
bool GameChess::isWhiteOnTheMove()
{
    return this->movementManager->getIsWhiteOnTheMove();
}

/*ImageView getImageOfMovFigure()
{
    return this.movementManager.getMovementFigure().getImage();
}

ImageView getImageOfGoalFieldFigure()
{
    return this.movementManager.getGoalFieldFigure().getImage();
}*/

/**
 * Vracia notáciu šachovej partie, ktorá je uložena v Stringovom ArraListe po riadku.
 * @return ArrayList notácie.
 */
std::vector<std::string> GameChess::getGameNotation()
{
    return this->notation->getGameNotationLines();
}

/**
 * Vracia riadok poradie riadku notácie, ktorý má byť vyznačený.
 * @return Poradie riadku.
 */
int GameChess::getIndexOfGameNotation()
{
    return this->notation->getIndexProcNotMov();
}


/**
 * Vracia informáciu o tom či je momentálne ťah kompletne nastavený. (Je nastavené
 * štartovacie aj cieľové políčko.)
 * @return Uspešnosť testu.
 */
bool GameChess::isMovementCompletlySet()
{
    return this->movementManager->getIsMovementCompletlySet();
}


/**
 * Testuje to či sa v momentalne nastaveném ťahu nachádza vyhadzovanie figurky.
 * @return Úspešnosť testu.
 */
bool GameChess::isRemovingFigure()
{
    return this->movementManager->getIsRemovingFigure();
}

/**
 * Vracia informáciu o tom či v momentálnom ťahu nastal šach.
 * @return Hodnota informácie.
 */
bool GameChess::getChess()
{
    return this->figuresManager->getChess();
}

/**
 * Vracia informáciu o tom či v momentálnom ťahu nastal šachmat.
 * @return Hodnota informácie.
 */
bool GameChess::getChessMat()
{
    return this->figuresManager->getChessMat();
}

/**
 * Testuje to či sa v momentalne nastaveném ťahu nachádza výmena pešiaka za novú figúrku.
 * @return Úspešnosť testu.
 */
bool GameChess::getIsChangingFigure()
{
    return this->movementManager->getIsChangingFigure();
}

/**
 * Vytvára v jadre programu novú figúrku a položí ju na šachovnicu.
 * @param image Obrázok novej figúrky, ktorý sa uloži ako premenna objektu novej figúrky.
 * @param id Identifikátor typu figúrky, ktorá sa má vytvoriť.
 * @return Úspešnosť vytvorenia.
 */
bool GameChess::createNewFigure(/*image,*/ int id)
{
    switch (id)
    {
        case 4:
            setChangedFigureField();
            putRookOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                           this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        case 3:
            setChangedFigureField();
            putKnightOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                             this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        case 2:
            setChangedFigureField();
            putBishopOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                             this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        case 1:
            setChangedFigureField();
            putQueenOnBoard(this->movementManager->getGoalField()->getColPos(), this->movementManager->getGoalField()->getRowPos(),
                            this->movementManager->getIsWhiteOnTheMove()/*, image*/);
            return this->figuresManager->updateFigures(this->movementManager->getIsWhiteOnTheMove(), this->movementManager->getGoalField()->get(),
                                                     nullptr);
        default:
            return false;
    }
}


/**
 * Zamení pešiaka za náhradnú figúrku.
 */
void GameChess::setChangedFigureField()
{
    Field *field = this->movementManager->getGoalField();
    Figure *changedFigure = field->get();
    field->remove(changedFigure);
    this->figuresManager->addChangedFigure(changedFigure);
}


/**
 * V prípade vlastného ťahu užívateľa pridá nový ťah do notácie partie.
 * Informácie sa získavajú z aktuálne nastaveného ťahu.
 */
void GameChess::addPlayerNotationMovement()
{
    this->notation->addPlayerNotationMovement(this->figuresManager, this->movementManager);
}


/**
 * Ukladá notáciu do súboru.
 * @return Úspešnosť uloženia.
 */
bool GameChess::saveNotation()
{
    return this->notation->saveNotation();
}



bool GameChess::saveNotationToAnotherFile(std::string path)
{
    return this->notation->saveNotationToAnotherFile(path);
}


/**
 * Vráti hodnotu identifikátoru figúrky ktorá nahradila pešiaka.
 * @return ID figúrky.
 */
int GameChess::getChangingFigureID()
{
    return this->notation->getChangingFigureID();
}


/**
 * Inkrementuje index notácie pre výber aktuálneho ťahu.
 */
void GameChess::incrementIndexOfNotationLines()
{
    this->notation->incrementIndexOfNotationLines();
}

/**
 * Dekrementuje index notácie pre výber aktuálneho ťahu.
 */
void GameChess::decrementIndexOfNotationLines()
{
    this->notation->decrementIndexOfNotationLines();
}


/**
 * Testovanie či je index ťahov notácie na začiatku (je nulový).
 * @return Úspešnosť testu.
 */
bool GameChess::isFirstIndexOfNotation()
{
    return this->notation->isFirstIndex();
}


/**
 * Testovanie či je index ťahov notácie na konci (je posledný).
 * @return Úspešnosť testu.
 */
bool GameChess::isLastIndexOfNotation()
{
    return this->notation->isLastIndex();
}


/**
 * Skompletuje informácie o ťahu notácie ak nie sú kompletné.
 * Využívané pri krátkej forme zápisu notácie.
 */
void GameChess::completeNotationMovement()
{
    this->notation->completeNotationMovement(this->movementManager);
}


/**
 * Vracia momentálne nastavený ťah partie.
 * @return Objekt ťahu.
 */
MovementManager *GameChess::getMovementManager()
{
    return this->movementManager;
}


/**
 * Vracia informáciu o tom či zápis notácie partie správny.
 * @return Úspešnosť testu.
 */
bool GameChess::isNotationRight()
{
    return this->notation->getIsRight();
}



/**
 * Vráti ID typu figúrky na poličkú určenom parametrami.
 * @param col Stlpec políčka.
 * @param row Riadok políčka.
 * @return ID typu figúrky.
 */
int GameChess::getFigureIDOnField(int col, int row)
{
    return this->board->getField(col, row)->get()->getID();
}


/**
 * Kontroluje či je figúrka na poličku zadanom parametrami biela alebo nie(čierna).
 * @param col Stlpec políčka.
 * @param row Riadok políčka.
 * @return Úspešnosť kontroly.
 */
bool GameChess::getIsWhiteFigureOnField(int col, int row)
{
    return this->board->getField(col, row)->get()->isWhiteF();
}


/**
 * Vráti slpec štartovacieho polička aktuálneho ťahu.
 * @return Stlpec políčka.
 */
int GameChess::getStartFieldCol()
{
    return this->movementManager->getStartField()->getColPos();
}


/**
 * Vráti riadok štartovacieho polička aktuálneho ťahu.
 * @return Riadok políčka.
 */
int GameChess::getStartFieldRow()
{
    return this->movementManager->getStartField()->getRowPos();
}


/**
 * Vráti stlpec cieľoveho polička aktuálneho ťahu.
 * @return Stlpec políčka.
 */
int GameChess::getGoalFieldCol()
{
    return this->movementManager->getGoalField()->getColPos();

}


/**
 * Vráti riadok cieľoveho polička aktuálneho ťahu.
 * @return Riadok políčka.
 */
int GameChess::getGoalFieldRow()
{
    return this->movementManager->getGoalField()->getRowPos();

}


/**
 * Kontroluje či je políčko zadané parametrami prázdne.
 * @param col Stlpec políčka.
 * @param row Riadok políčka.
 * @return Úspešnosť kontroly.
 */
bool GameChess::getIsFieldEmpty(int col, int row)
{
    return this->board->getField(col, row)->isEmpty();
}
