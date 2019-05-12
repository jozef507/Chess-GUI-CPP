/**
 * Trieda reprezentuje jadro (hlavnu logiku) aplikácie.
 * @author Jozef Ondria
 */

#ifndef ICP_CHESSGAME_H
#define ICP_CHESSGAME_H

#include "Game.h"
#include <string>
#include <vector>

class MovementManager;
class Notation;
class Field;
class Board;
class FiguresManager;

/**
 * Hlavičkový súbor:
 * Trieda reprezentujúca celé jadro/logiku jedenej hry.
 * Obsahuje inštancie tried potrebných pre správu celej hry: board, movementManager,
 * figuresManager, notation.
 */
class GameChess: public Game
{

private:
    Board *board;
    MovementManager *movementManager;
    FiguresManager *figuresManager;
    Notation *notation;

    //List<Figure> activeWhiteFigures;
    //List<Figure> activeBlackFigures;

    /**
     * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
     * @param col Stlpec políčka kam sa má figúrka vložiť.
     * @param row Riadok políčka kam sa má figúrka vložiť.
     * @param isPawnWhite Informácia o farbe figúrky.
     * @param image Odkaz na obrázok figúrky z grafického rozhrania.
     */
    void putPawnOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);

    /**
     * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
     * @param col Stlpec políčka kam sa má figúrka vložiť.
     * @param row Riadok políčka kam sa má figúrka vložiť.
     * @param isRookWhite Informácia o farbe figúrky.
     * @param image Odkaz na obrázok figúrky z grafického rozhrania.
     */
    void putRookOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);

    /**
     * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
     * @param col Stlpec políčka kam sa má figúrka vložiť.
     * @param row Riadok políčka kam sa má figúrka vložiť.
     * @param isRookWhite Informácia o farbe figúrky.
     * @param image Odkaz na obrázok figúrky z grafického rozhrania.
     */
    void putKnightOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);

    /**
     * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
     * @param col Stlpec políčka kam sa má figúrka vložiť.
     * @param row Riadok políčka kam sa má figúrka vložiť.
     * @param isRookWhite Informácia o farbe figúrky.
     * @param image Odkaz na obrázok figúrky z grafického rozhrania.
     */
    void putBishopOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);

    /**
     * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
     * @param col Stlpec políčka kam sa má figúrka vložiť.
     * @param row Riadok políčka kam sa má figúrka vložiť.
     * @param isRookWhite Informácia o farbe figúrky.
     * @param image Odkaz na obrázok figúrky z grafického rozhrania.
     */
    void putQueenOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);

    /**
      * Vytvorí novú figúrku - pešiaka, vloží ho na šachovnicu a pridá do aktívnych figúrok.
      * @param col Stlpec políčka kam sa má figúrka vložiť.
      * @param row Riadok políčka kam sa má figúrka vložiť.
      * @param isRookWhite Informácia o farbe figúrky.
      * @param image Odkaz na obrázok figúrky z grafického rozhrania.
      */
    void putKingOnBoard(int col, int row, bool isPawnWhite/*, ImageView image*/);

    /**
     * Nastaví field v ktorom bola zamenena figúrka (pešiak) za novú figúrku.
     */
    virtual void setChangedFigureField();


public:

    /**
     * Inštruktor hry.
     * @param path Cesta k súboru notácie.
     */
    GameChess(std::string path);

    /**
     * Deštruktor.
     */
    ~GameChess();

    /**
     * Vráti ID typu figúrky na poličkú určenom parametrami.
     * @param col Stlpec políčka.
     * @param row Riadok políčka.
     * @return ID typu figúrky.
     */
    virtual int getFigureIDOnField(int col, int row);

    /**
     * Kontroluje či je figúrka na poličku zadanom parametrami biela alebo nie(čierna).
     * @param col Stlpec políčka.
     * @param row Riadok políčka.
     * @return Úspešnosť kontroly.
     */
    virtual bool getIsWhiteFigureOnField(int col, int row);

    /**
     * Kontroluje či je políčko zadané parametrami prázdne.
     * @param col Stlpec políčka.
     * @param row Riadok políčka.
     * @return Úspešnosť kontroly.
     */
    virtual bool getIsFieldEmpty(int col, int row);

    /**
     * Vráti slpec štartovacieho polička aktuálneho ťahu.
     * @return Stlpec políčka.
     */
    virtual int getStartFieldCol();

    /**
     * Vráti riadok štartovacieho polička aktuálneho ťahu.
     * @return Riadok políčka.
     */
    virtual int getStartFieldRow();

    /**
     * Vráti stlpec cieľoveho polička aktuálneho ťahu.
     * @return Stlpec políčka.
     */
    virtual int getGoalFieldCol();

    /**
     * Vráti riadok cieľoveho polička aktuálneho ťahu.
     * @return Riadok políčka.
     */
    virtual int getGoalFieldRow();

    /**
     * Vráti cieľove políčko.
     * @return Políčko.
     */
    virtual Field *getGoalField();

    /**
     * Zmeni poradie hráča, ktorý je na ťahu.
     */
    virtual void changePlayer();

    /**
     * Kontrola či môže užívateľ previesť vlastný ťah.
     * @param canPlayerPlay
     */
    virtual void setCanPlayerPlay(bool canPlayerPlay);

    /**
     * Vynuluje informacie o ťahu v logike ktorý je reprezentovaný triedy MovementManager,
     * a tým pripraví jadro(logiku) na ďalší ťah.
     */
    virtual void nullMovementManager();


    /**
     * Nastavuje informácie o najbližšom ťahu hráča, ktorý sa má vykonať.
     * @param col Stĺpec políčka ktoré sa má do ťahu nastaviť.
     * @param row Riadok políčka ktoré sa má do ťahu nastaviť.
     * @return Úspešnosť metódy.
     */
    virtual bool setPlayerMovement(int col, int row);

    /**
     * Nastavuje informácie o najbližšom prehrávanom ťahu, ktorý sa má vykonať. Tieto informácie
     * sa vyberú z notácie partie.
     * @return Úspešnosť metódy.
     */
    virtual bool setPlaybackMovement();

    /**
     * Vykonáva už nastavený ťah hráča v jadre programu.
     * @return Úspešnosť ťahu.
     */
    virtual bool performPlayerMovement();

    /**
     * Vykonáva už nastavený prehrávaný ťah v jadre programu.
     * @return Úspešnosť ťahu.
     */
    virtual bool performPlaybackMovement();

    /**
     * Nastaví momentálny ťah v jadre programu a testuje správnosť/povolenosť ťahu.
     * @return Úspešnosť testu.
     */
    virtual bool setPlaybackUndoMovement();

    /**
     * Vykonáva momentálne nastavený ťah v jadre programu a testuje správnosť/povolenosť ťahu.
     * @return Úspešnosť testu.
     */
    virtual bool performPlaybackUndoMovement();


    /**
     * @return Informáciu o tom či je na ťahu biely hráč.
     */
    virtual bool isWhiteOnTheMove();
    //getImageOfMovFigure;
    //getImageOfGoalFieldFigure;

    /**
     * Vracia notáciu šachovej partie, ktorá je uložena v Stringovom ArraListe po riadku.
     * @return ArrayList notácie.
     */
    virtual std::vector<std::string> getGameNotation();

    /**
     * Vracia riadok poradie riadku notácie, ktorý má byť vyznačený.
     * @return Poradie riadku.
     */
    virtual int getIndexOfGameNotation();

    /**
     * Vracia informáciu o tom či je momentálne ťah kompletne nastavený. (Je nastavené
     * štartovacie aj cieľové políčko.)
     * @return Uspešnosť testu.
     */
    virtual bool isMovementCompletlySet();

    /**
     * Testuje to či sa v momentalne nastaveném ťahu nachádza vyhadzovanie figurky.
     * @return Úspešnosť testu.
     */
    virtual bool isRemovingFigure();

    /**
     * Kontroluje pritomnosť šachu v hre.
     * @return Výsledok kontroly.
     */
    virtual bool getChess();

    /**
     * Kontroluje pritomnosť šachu v hre.
     * @return Výsledok kontroly.
    */
    virtual bool getChessMat();

    /**
    * Testuje to či sa v momentalne nastaveném ťahu nachádza výmena pešiaka za novú figúrku.
    * @return Úspešnosť testu.
    */
    virtual bool getIsChangingFigure ();

    /**
     * Vytvára v jadre programu novú figúrku a položí ju na šachovnicu.
     * @param image Obrázok novej figúrky, ktorý sa uloži ako premenna objektu novej figúrky.
     * @param id Identifikátor typu figúrky, ktorá sa má vytvoriť.
     * @return Úspešnosť vytvorenia.
    */
    virtual bool createNewFigure(/*ImageView image, */int id);


    /**
     * V prípade vlastného ťahu užívateľa pridá nový ťah do notácie partie.
     * Informácie sa získavajú z aktuálne nastaveného ťahu.
     */
    virtual void addPlayerNotationMovement();

    /**
     * Ukladá notáciu do súboru.
     * @return Úspešnosť uloženia.
     */
    virtual bool saveNotation() ;

    /**
     * Ukladá notáciu do súboru predaného v argumente.
     * @param path Cesta k súboru.
     * @return Úspešnosť uloženia.
     */
    virtual bool saveNotationToAnotherFile(std::string path) ;

    /**
    * Vráti hodnotu identifikátoru figúrky ktorá nahradila pešiaka.
    * @return ID figúrky.
    */
    virtual int getChangingFigureID();

    /**
     * Inkrementuje index notácie pre výber aktuálneho ťahu.
     */
    virtual void incrementIndexOfNotationLines();

    /**
     * Dekrementuje index notácie pre výber aktuálneho ťahu.
     */
    virtual void decrementIndexOfNotationLines();

    /**
     * Testovanie či je index ťahov notácie na začiatku (je nulový).
     * @return Úspešnosť testu.
     */
    virtual bool isFirstIndexOfNotation();

    /**
     * Testovanie či je index ťahov notácie na konci (je posledný).
     * @return Úspešnosť testu.
     */
    virtual bool isLastIndexOfNotation();

    /**
     * Skompletuje informácie o ťahu notácie ak nie sú kompletné.
     * Využívané pri krátkej forme zápisu notácie.
     */
    virtual void completeNotationMovement();

    /**
     * Vracia momentálne nastavený ťah partie.
     * @return Objekt ťahu.
     */
    virtual MovementManager *getMovementManager();

    /**
     * Vracia informáciu o tom či zápis notácie partie správny.
     * @return Úspešnosť testu.
     */
    virtual bool isNotationRight();
};


#endif //ICP_CHESSGAME_H
