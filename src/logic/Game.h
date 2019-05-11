//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_GAME_H
#define ICP_GAME_H

#include <string>
#include <vector>

class MovementManager;
class Field;

/**
 * Rozhranie pre grafické rozhranie, ktoré zahrňa metódy dôležité pre samotné gui
 * ale aj pre riadenie logiky programu.
 */
class Game
{
public:

    /**
     * Deštruktor.
     */
    virtual ~Game()= default;

    /**
     * Vráti ID typu figúrky na poličkú určenom parametrami.
     * @param col Stlpec políčka.
     * @param row Riadok políčka.
     * @return ID typu figúrky.
     */
    virtual int getFigureIDOnField(int col, int row) = 0;

    /**
     * Kontroluje či je figúrka na poličku zadanom parametrami biela alebo nie(čierna).
     * @param col Stlpec políčka.
     * @param row Riadok políčka.
     * @return Úspešnosť kontroly.
     */
    virtual bool getIsWhiteFigureOnField(int col, int row) = 0;

    /**
     * Kontroluje či je políčko zadané parametrami prázdne.
     * @param col Stlpec políčka.
     * @param row Riadok políčka.
     * @return Úspešnosť kontroly.
     */
    virtual bool getIsFieldEmpty(int col, int row) = 0;

    /**
     * Vráti slpec štartovacieho polička aktuálneho ťahu.
     * @return Stlpec políčka.
     */
    virtual int getStartFieldCol() = 0;

    /**
     * Vráti riadok štartovacieho polička aktuálneho ťahu.
     * @return Riadok políčka.
     */
    virtual int getStartFieldRow() = 0;

    /**
     * Vráti stlpec cieľoveho polička aktuálneho ťahu.
     * @return Stlpec políčka.
     */
    virtual int getGoalFieldCol() = 0;

    /**
     * Vráti riadok cieľoveho polička aktuálneho ťahu.
     * @return Riadok políčka.
     */
    virtual int getGoalFieldRow() = 0;

    /**
     * Vráti cieľove políčko.
     * @return Políčko.
     */
    virtual Field *getGoalField() = 0;

    /**
     * Zmeni poradie hráča, ktorý je na ťahu.
     */
    virtual void changePlayer() = 0;

    /**
     * Kontrola či môže užívateľ previesť vlastný ťah.
     * @param canPlayerPlay
     */
    virtual void setCanPlayerPlay(bool canPlayerPlay) = 0;

    /**
     * Vynuluje informacie o ťahu v logike ktorý je reprezentovaný triedy MovementManager,
     * a tým pripraví jadro(logiku) na ďalší ťah.
     */
    virtual void nullMovementManager() = 0;

    /**
     * Nastavuje informácie o najbližšom ťahu hráča, ktorý sa má vykonať.
     * @param col Stĺpec políčka ktoré sa má do ťahu nastaviť.
     * @param row Riadok políčka ktoré sa má do ťahu nastaviť.
     * @return Úspešnosť metódy.
     */
    virtual bool setPlayerMovement(int col, int row) = 0;

    /**
     * Nastavuje informácie o najbližšom prehrávanom ťahu, ktorý sa má vykonať. Tieto informácie
     * sa vyberú z notácie partie.
     * @return Úspešnosť metódy.
     */
    virtual bool setPlaybackMovement() = 0;

    /**
     * Vykonáva už nastavený ťah hráča v jadre programu.
     * @return Úspešnosť ťahu.
     */
    virtual bool performPlayerMovement() = 0;

    /**
     * Vykonáva už nastavený prehrávaný ťah v jadre programu.
     * @return Úspešnosť ťahu.
     */
    virtual bool performPlaybackMovement() = 0;

    /**
     * Nastaví momentálny ťah v jadre programu a testuje správnosť/povolenosť ťahu.
     * @return Úspešnosť testu.
     */
    virtual bool setPlaybackUndoMovement() = 0;

    /**
     * Vykonáva momentálne nastavený ťah v jadre programu a testuje správnosť/povolenosť ťahu.
     * @return Úspešnosť testu.
     */
    virtual bool performPlaybackUndoMovement() = 0;


    /**
     * @return Informáciu o tom či je na ťahu biely hráč.
     */
    virtual bool isWhiteOnTheMove() = 0;
    //getImageOfMovFigure;
    //getImageOfGoalFieldFigure;

    /**
     * Vracia notáciu šachovej partie, ktorá je uložena v Stringovom ArraListe po riadku.
     * @return ArrayList notácie.
     */
    virtual std::vector<std::string> getGameNotation() = 0;

    /**
     * Vracia riadok poradie riadku notácie, ktorý má byť vyznačený.
     * @return Poradie riadku.
     */
    virtual int getIndexOfGameNotation() = 0;

    /**
     * Vracia informáciu o tom či je momentálne ťah kompletne nastavený. (Je nastavené
     * štartovacie aj cieľové políčko.)
     * @return Uspešnosť testu.
     */
    virtual bool isMovementCompletlySet() = 0;

    /**
     * Testuje to či sa v momentalne nastaveném ťahu nachádza vyhadzovanie figurky.
     * @return Úspešnosť testu.
     */
    virtual bool isRemovingFigure() = 0;

    /**
     * Kontroluje pritomnosť šachu v hre.
     * @return Výsledok kontroly.
     */
    virtual bool getChess() = 0;

    /**
     * Kontroluje pritomnosť šachu v hre.
     * @return Výsledok kontroly.
    */
    virtual bool getChessMat() = 0;

    /**
     * Testuje to či sa v momentalne nastaveném ťahu nachádza výmena pešiaka za novú figúrku.
     * @return Úspešnosť testu.
     */
    virtual bool getIsChangingFigure () = 0;

    /**
     * Vytvára v jadre programu novú figúrku a položí ju na šachovnicu.
     * @param image Obrázok novej figúrky, ktorý sa uloži ako premenna objektu novej figúrky.
     * @param id Identifikátor typu figúrky, ktorá sa má vytvoriť.
     * @return Úspešnosť vytvorenia.
    */
    virtual bool createNewFigure(/*ImageView image, */int id) = 0;


    /**
     * V prípade vlastného ťahu užívateľa pridá nový ťah do notácie partie.
     * Informácie sa získavajú z aktuálne nastaveného ťahu.
     */
    virtual void addPlayerNotationMovement() = 0;

    /**
     * Ukladá notáciu do súboru.
     * @return Úspešnosť uloženia.
     */
    virtual bool saveNotation() = 0 ;

    /**
     * Ukladá notáciu do súboru predaného v argumente.
     * @param path Cesta k súboru.
     * @return Úspešnosť uloženia.
     */
    virtual bool saveNotationToAnotherFile(std::string path) = 0;

    /**
     * Vráti hodnotu identifikátoru figúrky ktorá nahradila pešiaka.
     * @return ID figúrky.
     */
    virtual int getChangingFigureID() = 0;

    /**
     * Inkrementuje index notácie pre výber aktuálneho ťahu.
     */
    virtual void incrementIndexOfNotationLines() = 0;

    /**
     * Dekrementuje index notácie pre výber aktuálneho ťahu.
     */
    virtual void decrementIndexOfNotationLines() = 0;

    /**
     * Testovanie či je index ťahov notácie na začiatku (je nulový).
     * @return Úspešnosť testu.
     */
    virtual bool isFirstIndexOfNotation() = 0 ;

    /**
     * Testovanie či je index ťahov notácie na konci (je posledný).
     * @return Úspešnosť testu.
     */
    virtual bool isLastIndexOfNotation() = 0;

    /**
     * Skompletuje informácie o ťahu notácie ak nie sú kompletné.
     * Využívané pri krátkej forme zápisu notácie.
     */
    virtual void completeNotationMovement() = 0;

    /**
     * Vracia momentálne nastavený ťah partie.
     * @return Objekt ťahu.
     */
    virtual MovementManager *getMovementManager() = 0;

    /**
     * Vracia informáciu o tom či zápis notácie partie správny.
     * @return Úspešnosť testu.
     */
    virtual bool isNotationRight() = 0;
};


#endif //ICP_GAME_H
