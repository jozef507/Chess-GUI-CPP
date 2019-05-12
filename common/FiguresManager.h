/**
 * Trieda reprezentuje manažéra pre aktívne/pasívne figúrky.
 * @author Jozef Ondria
 * @author Jan Holásek
 */

#ifndef ICP_FIGURESMANAGER_H
#define ICP_FIGURESMANAGER_H


#include <vector>

class FigureKing;
class Figure;
class Field;


/**
 * Trieda reprezentujúca manažera figúrok. Obsahuje informácie o aktívných figúrkach (na šachovnici)
 * vyhodených figurkách a takisto zamenených figúrkach.
 */
class FiguresManager
{
private:
    bool chessMat;
    FigureKing *whiteKing;
    FigureKing *blackKing;

    std::vector<Figure*> activeWhiteFigures;
    std::vector<Figure*> activeBlackFigures;
    std::vector<Figure*> removedFigures;
    std::vector<Figure*> changedFigures;

    std::vector<Field*> whiteFieldsInDanger;
    std::vector<Field*> blackFieldsInDanger;

public:

    /**
     * Inicializace objektu.
     */
    FiguresManager();

    /**
     * Deštruktor.
     */
    ~FiguresManager();


    /**
     * Základná metoda tejto triedy, volaná po uskutočnení každého ťahu. Jej úlohou je aktualizovať
     * štruktúry aktívnych/pasívnych figúrok ale najmä aktualizovať štruktúry pre políčka v ohrození požívajuce
     * sa na detekciu šachu a šachmatu.
     * @param whiteOnTheMove Informácia o tom ktorý hráč je na ťahu.
     * @param movingFigure Odkaz na figúrku ktorá sa pri ťahu presúva.
     * @param removedFigure Odkaz na figúrku ktorý bola vyhodená.
     * @return Úspešnosť operácie.
     */
    bool updateFigures(bool whiteOnTheMove, Figure *movingFigure, Figure *removedFigure);

    /**
     * Pridá figúrku figure do štruktúry aktívnych figúrok podľa jej farby.
     * @param figure
     */
    void addActiveFigure(Figure *figure);

    /**
     * Pridá vyhodenú figúrku figure do štruktúry pre vyhodené figúrky.
     * @param figure
     */
    void addRemovedFigure(Figure *figure);

    /**
      * Pridá zamenenú figúruku(pešiaka) figure do štruktúry pre zamenené figúrky.
      * @param figure
      */
    void addChangedFigure(Figure *figure);

    /**
     * Nastaví/aktualizuje štruktúru ohrozených políčok bielymi figúrkami.
     */
    void setWhiteFieldsInDanger();

    /**
     * Nastaví/aktualizuje štruktúru ohrozených políčok čiernymi figúrkami.
     */
    void setBlackFieldsInDanger();

    /**
     * Nastaví/aktualizuje štruktúru ohrozených políčok bielymi figúrkami okrem bieleho kráľa.
     * @return
     */
    std::vector<Field*> getWhiteFieldsInDangerWithoutKing();

    /**
    * Nastaví/aktualizuje štruktúru ohrozených políčok čiernymi figúrkami okrem čierneho kráľa.
    * @return
    */
    std::vector<Field*> getBlackFieldsInDangerWithoutKing();

    /**
     * Metóda kontroluje či je prítomny na šachovnici šach.
     * @param isWhiteOnTheMove Hrač na ťahu.
     * @param movingFigure Presúvaná figúrka.
     * @return Výsledok kontroly.
     */
    bool checkChess(Figure *movingFigure);

    /**
     * Metóda kontroluje či momentálny stav na šachovnici nespôsobuje šach mat.
     * @param isWhiteOnTheMove Hráč na ťahu.
     * @return Výsledok kotnroly.
     */
    bool checkChessMat(bool isWhiteOnTheMove);

    /**
     * Nastaví člena/premennu tejto triedy kráľa na kráľa daného parametrom.
     * @param king Kráľ ktorý má byť priradený objektu.
     */
    void setKing(FigureKing *king);

    /**
     * Vracia informáciu o tom či je na šachovnici stav - šachmat.
     * @return Pravdivostná hodnota.
     */
    bool getChess();

    /**
     * Vracia informáciu o tom či je na šachovnici stav - šachmat.
     * @return Pravdivostná hodnota.
     */
    bool getChessMat();

    /**
     * Vráti poslednú figúrku priradenú do štruktúry - zamenené figúrky.
     * @return Odkaz na figúrku.
     */
    Figure *getLastChangedFigure ();

    /**
     * Odstráni poseldnú figúrku zo štruktúry - zamenené figúrky.
     */
    void removeLastChangedFigure ();

    /**
     * Vráti štruktúru aktívnych bielych figúrok.
     * @return Štruktúru figúrok.
     */
    std::vector<Figure*> getActiveWhiteFigures ();

    /**
     * Vráti štruktúru aktívnych čiernych figúrok.
     * @return Štruktúru figúrok.
     */
    std::vector<Figure*> getActiveBlackFigures ();

    /**
     * Vráti poslednú figúrku priradenú do štruktúry - vyhodené figúrky.
     * @return Odkaz na figúrku.
     */
    Figure *getLastRemovedFigure();

    /**
     * Odstráni poseldnú figúrku zo štruktúry - vyhodené figúrky.
     */
    void removeLastRemovedFigure();

    /**
     * Odstráni z aktívnych figúrok figurkú danú parametrom.
     * @param figure Odkaz na danú figúrku.
     */
    void removeActiveFigure(Figure *figure);

    /**
     * Nastaví člena tiredy šachmat podľa daného parametru.
     * @param is Pravdivostná hotnota.
     */
    void setChessMat(bool is);
};


#endif //ICP_FIGURESMANAGER_H
