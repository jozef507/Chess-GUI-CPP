//
// Created by Jozef on 5/3/2019.
//

#ifndef ICP_NOTATIONMOVEMENT_H
#define ICP_NOTATIONMOVEMENT_H

#include <string>
#include <vector>
class MovementManager;
class FiguresManager;
class Figure;
class Field;

/**
 * Trieda reprezentujúca jeden ťah a hlavne jeho informácii získanych z notácie šachovej partie.
 * Pri vlastných ťahoch užívateľa sa vytvarajú nové ťahy notácie.
 */
class NotationMovement
{
private:
    bool isLongNotation;

    int startFieldCol;
    int startFieldRow;
    int movementFigureID;
    int goalFieldCol;
    int goalFieldRow;
    int changingFigureID;

    bool isFigureRemoving;
    bool isChess;
    bool isChessMat;

    /**
     * Vráti ID typu figúrky zo stringoveho označenia figúrky.
     * @param s Označenie figúrky.
     * @return ID figúrky.
     */
    int getFigureID(std::string s);

    /**
     * Vratia stringove označenie figúrky z ID figúrky.
     * @param id ID figúrky.
     * @return Označenie figúrky.
     */
    std::string getStrFigureID(int id);

    /**
     * Vráti poradie stlpca políčka na šachovnici.
     * @param s Označenie stlpca.
     * @return Poradie stlpca.
     */
    int getIntFieldColumn(std::string s);

    /**
     * Vráti označenie stlpca políčka z jeho poradia označenia.
     * @param i Poradie stlpca.
     * @return Označenie stlpca.
     */
    std::string  getStrFieldColumn(int i);

public:

    /**
     * Inicializuje ťah notácie.
     */
    NotationMovement();

    /**
     * Deštruktor.
     */
    ~NotationMovement() = default;

    /**
     * Nastaví ťah notácie z uživateľoveho ťahu. Je to dôležite pre budúce volanie ťahov spať.
     * @param isLongNotation Informacia či ide o krátku/dlhú formu zápisu.
     * @param figuresManager Manažer aktivných/pasívnych figúrok.
     * @param movementManager Manažer realneo ťahu.
     */
    void setNotationMovementFromUserMov(bool isLongNotation, FiguresManager *figuresManager, MovementManager *movementManager);

    /**
     * Nastavuje ťah notácie zo zápisu z notácie.
     * @param s Reťazec zápisu ťahu.
     * @return Úspešnosť operácie.
     */
    bool setNotationMovementFromString(std::string s);


    /**
     * Vracia infomáciu o tom či ide o dlhý zápis ťahu v notácii.
     * @return Pravdivostna hodnota.
     */
    bool getIsLongNotation();

    /**
     * Vygeneruje string/zapis ťahu z tohto ťahu notácie.
     * @param activeFigures Aktívne figúrky na šachovnici - štruktúra.
     * @param movementFigure Posúvacia figúrka.
     * @param startFieldOfMovementFig Štartovacie políčko ťahu.
     * @return Vygenerovaný string.
     */
    std::string getGeneratedStrOfNotMov(std::vector<Figure*> activeFigures, Figure *movementFigure, Field *startFieldOfMovementFig);

    /**
     * Vracia stlpec štartovaciaho políčka.
     * @return
     */
    int getStartFieldCol();

    /**
     * Vracia riadok štartovaciaho políčka.
     * @return
     */
    int getStartFieldRow();

    /**
     * Vracia stlpec cieľoveho políčka.
     * @return
     */
    int getGoalFieldCol();

    /**
     * Vracia riadok cieľoveho políčka.
     * @return
     */
    int getGoalFieldRow();

    /**
     * Vracia ID figúrky kotorá je pri ťahu posúvaná.
     * @return ID figúrky.
     */
    int getMovementFigureID();

    /**
     * Vracia ID figúrky kotorá je zamenená za pešiaka.
     * @return ID figúrky.
     */
    int getChangingFigureID();

    /**
     * Vracia ID figúrky kotorá je vyhodená.
     * @return ID figúrky.
     */
    bool getIsFigureRemoving();

    /**
     * Vráti informáciu o tom či je v tomto ťahu šach.
     * @return Pravdivostna hodnota.
     */
    bool getIsChess();

    /**
     * Vráti informáciu o tom či je v tomto ťahu šachmat.
     * @return Pravdivostna hodnota.
     */
    bool getIsChessMat();

    /**
     * Zkompletuje ťah notácie z ťahu užívateľa.
     * @param movementManager Manážer realneho ťahu.
     */
    void completeNotationMovement(MovementManager *movementManager);

};


#endif //ICP_NOTATIONMOVEMENT_H
