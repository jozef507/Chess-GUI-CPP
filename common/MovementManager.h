/**
 * Trieda reprezentuje aktuálny ťah hry.
 * @author Jozef Ondria
 * @author Jan Holásek
 */

#ifndef ICP_MOVEMENTMANAGER_H
#define ICP_MOVEMENTMANAGER_H


class Field;
class Figure;
class FiguresManager;
class Board;
class Notation;
class NotationMovement;

/**
 * Trieda ktorá reprezentuje ťah partie - jeho všetky dôležité informácie:
 * štartovacie políčko, cieľové políčko, firgúrky na týchto políčkach...
 */
class MovementManager
{
private:
    bool canPlayerPlay;
    bool isWhiteOnTheMove;
    bool isMovementCompletlySet;
    bool isRemovingFigure;
    bool isChangingFigure;
    //private boolean isFigureChoosen;
    Field *startField;
    Figure *movementFigure;
    Field *goalField;
    Figure *goalFieldFigure;
    Figure *changingFigure;

public:

    /**
     * Inicializuje ťah partie.
     */
    MovementManager();

    /**
     * Deštruktor.
     */
    ~MovementManager() = default;

    /**
     * Vracia štartovacie políčko ťahu.
     * @return Odkaz na políčko.
     */
    Field *getStartField();

    /**
    * Vracia štartovacie políčko ťahu.
    * @return Odkaz na štartovacie políčko.
    */
    Field *getGoalField();

    /**
     * Zmení hráča, ktorý je na ťahu.
     */
    void changePlayer();

    /**
     * Nastaví informáciu o tom či môže užívateľ previesť vlastný ťah.
     * @param canPlayerPlay
     */
    void setCanPlayerPlay(bool canPlayerPlay);

    /**
      * Vynuluje informácie o ťahu a tým prípráví aplikáciu na ďalší ťah.
      */
    void nullMovementManager();

    /**
     * Nastavuje ťah ktorý sa má vykonať. Nastavuje štartovacie a cieľove políčko.
     * Ak je ťah vynulovaný a povola sa metóda tak sa nastaví štartovacie políčko ak nie nastavuje
     * sa cieľové políčko.
     * @param col Stlpec políčka.
     * @param row Riadok políčka.
     * @param board Šachovníca.
     * @return Úspešnosť nastavenia.
     */
    bool setPlayerMovement(int col, int row, Board *board);

    /**
     * Vykoná už nastavený ťah prostredníctvom rozhrania na figúrku ktorý sa má presúvať.
     * Následne otestuje návratovú hodnotu od figúrky a nastavý ďalšie dôležíte informácie o ťahu.
     * @param figuresManager Manažer aktívnych figúrok.
     * @return Úspešnosť ťahu.
     */
    bool performMovement(FiguresManager *figuresManager);

    /**
     * Nastavuje prehrávaný ťah ktorý sa má vykonať. Nastavuje štartovacie a cieľove políčko.
     * Ak je ťah vynulovaný a povola sa metóda tak sa nastaví štartovacie políčko ak nie nastavuje
     * sa cieľové políčko. Tieto políčka sa získavajú z notácie šachovej partie.
     * @param board Šachovnica.
     * @param notation Notácia partie.
     * @param figuresManager Manažer aktívnych figúrok.
     * @return Úspešnosť nastavenia.
     */
    bool setPlaybackMovement(Board *board, Notation *notation, FiguresManager *figuresManager);

    /**
      * Nastaví prehravaný ťah do predu. Informácie o ťahu sa získavajú z notácie partie.
      * @param mov Ťah repretentovaný notáciou.
      * @param board Šachovnica.
      * @param figuresManager Manažer aktívných figúrok.
      * @return Úspešnosť nastavenia.
      */
    bool setPlaybackUndoMovement(NotationMovement *mov, Board *board, FiguresManager *figuresManager);

    /**
     * Vykoná už nastavený ťah dozadu.
     * @param mov Ťah reprezentovaný notáciou.
     * @param figuresManager Manažer aktívnych figúrok.
     * @return Úspešnosť ťahu.
     */
    bool performPlaybackUndoMovement(NotationMovement *mov, FiguresManager *figuresManager);

    /**
     * Vracia figúrku ktorá nahrádza pešiaka.
     * @return Odkaz na figúrku.
     */
    Figure *getChangingFigure();

    /**
     * Vracia figúrku ktorej ťah sa vykonáva.
     * @return Odkaz na figúrku.
     */
    Figure *getMovementFigure();

    /**
     * Vracia figúrku ktorej ťah sa vykonáva.
     * @return Odkaz na figúrku.
     */
    Figure *getGoalFieldFigure();

    /**
     * Vracia informáciu o tom či je na ťahu práve biely hráč.
     * @return Pravdivostna informácia.
     */
    bool getIsWhiteOnTheMove();

    /**
     * Vracia informáciu o tom či je ťah kompletne nastavený (či už je nastavené aj cieľové políčko).
     * @return Pravdivostna informácia.
     */
    bool getIsMovementCompletlySet();

    /**
     * Vracia informáciu o tom či dochádza k vyhodeniu figúrky.
     * @return Pravdivostna informácia.
     */
    bool getIsRemovingFigure();

    /**
     * Vracia informáciu o tom či dochádza k zámene pešiaka.
     * @return Pravdivostna informácia.
     */
    bool getIsChangingFigure();
};


#endif //ICP_MOVEMENTMANAGER_H
