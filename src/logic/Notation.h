//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_NOTATION_H
#define ICP_NOTATION_H


#include <vector>
#include <string>
#include <cctype>
class NotationMovement;
class FiguresManager;
class MovementManager;

/**
 * Trieda ktorá reprezentuje celú notáciu šachovej partie.
 */
class Notation
{
private:
    std::string filePath;
    std::vector<std::string> gameNotationLines;
    std::vector<NotationMovement*> notationMovements;

    int indexProcNotMov;
    bool isLongNotation;
    bool isEmpty;
    bool isRight;

    /**
     * Pomocná funkcia pre odstranenie všetkých už nepotrebných ťahov zo štrúktúry pre NotationMovements.
     */
    void removeUselessNotMovs();

    /**
     * Odstráni zo zápisu notácie (stringovo) už nepotrebne riadky tejto notácie.
     */
    void removeUselessLines();

    /**
     * Pridá jeden ťah reprezentovaný NotationMovementom do zápisu notácie.
     * @param figuresManager Manžer aktívnych/pasívnych figúrok.
     * @param movementManager Manažer logického ťahu.
     * @param mov Ťah notácie.
     */
    void addNotMovToNotationLines(FiguresManager *figuresManager, MovementManager *movementManager,
                                  NotationMovement *mov);
    /**
     * Načíta riadky notácie zo súboru do vectoru pre zapis notacie.
     * @return Úspešnosť operácie.
     */
    bool getFileContent();

    /**
     * Vlastná funkcia pre odseknutie ľavých bielych znakov.
     * @param s Reťazec pre osekanie.
     */
    void ltrim(std::string &s);

    /**
     * Vlastná funkcia pre odseknutie pravých bielych znakov.
     * @param s Reťazec pre osekanie.
     */
    void rtrim(std::string &s);

    /**
     * Vlastná funkcia pre odseknutie bielych znakov z ľavej a pravej strany.
     * @param s Reťazec pre osekanie.
     */
    void trim(std::string &s);

    /**
     * Odstraňuje z vectoru notacie riadky ktoré sú prázdne.
     * @param vec Vector riadkov notácie.
     */
    void removeSpaces(std::vector<std::string> &vec);

    /**
     * Rozdelí string podľa oddeľovača.
     * @param txt Režazec na rozdelenie.
     * @param strs Vector pre naplnenie oddelených častí.
     * @param ch Oddeľovač
     * @return Počet oddelenych elementov.
     */
    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);



public:

    /**
    * Inicializuje notáciu.
    * @param path Cesta k súboru s obsahom notácie.
    */
    Notation(std::string path);

    /**
     * Deštruktor.
     */
    ~Notation();

    /**
    * Prechádza celú notáciu zo súboru a postupne spracováva riadok za riadkom a ťah za ťahom.
    * Každý ťah konvertuje na inštanciu triedy NotationMovement ktorý reprezentuje jeden ťah zápisu.
    * Zneho sa vyberajú najdôležitejšie informacie o ťahu a to pri prehrávaní partii.
    */
    void processNotation();

    /**
    * Pri vlastnom ťahu užívateľa táto metóda odstráni ďalšie už zbytočné ťahy z notácie
    * a prída ťah užívateľa v do tejto notácii.
    * @param figuresManager Manažer aktívnych/pasívnych figúrok.
    * @param movementManager Manažer ťahu.
    */
    void addPlayerNotationMovement(FiguresManager *figuresManager, MovementManager *movementManager);

    /**
     * Uloži notáciu do súboru z ktorého bola načítaná.
     * @return Úspešnosť uloženia.
     */
    bool saveNotation();

    /**
     * Uloži notáciu do súboru zadanom v parametri funkcie.
     * @param path Cesta k danému súboru.
     * @return Úspešnosť uloženia.
     */
    bool saveNotationToAnotherFile(std::string path);

    /**
    * Testuje či je index pre štruktúru ťahov notácie nulový ak áno znamena to že sme spracuvávame prvý prvok
    * štruktúry.
    * @return
    */
    bool isFirstIndex();

    /**
    * Testuje či je index pre štruktúru ťahov notácie poslený, či pracujeme s poslednym prvkom štruktúry.
    * @return
    */
    bool isLastIndex();

    /**
    * Vracia zápis notácie implementovanú riadok po riadku v štruktúre ArrayList.
    * @return Štruktúru notácie.
    */
    std::vector<std::string> getGameNotationLines();

    /**
    * Vracia index aktuálneho spracovaneho ťahu notácie ale prevedený na riadok notácie.
    * @return
    */
    int getIndexProcNotMov();

    /**
    * Testovanie či je notácia prázdna.
    * @return Výsledok testu.
    */
    bool getIsEmpty();

    /**
    * Vráti inštanciu/objekt triedy NotationMovement pre ťah ktorý sa aktuálne spracúváva.
    * @return
    */
    NotationMovement *getActualNotMov();

    /**
    * Inkrementuje index určujúci aktuálny spracovávaný ťah notácie.
    */
    void incrementIndexOfNotationLines();

    /**
    * Dekrementuje index určujúci aktuálny spracovávaný ťah notácie.
    */
    void decrementIndexOfNotationLines();

    /**
    * Vráti ID figúrky ktorá má v danom ťahu vymeniť pešiaka.
    * @return Hodnota ID.
    */
    int getChangingFigureID();

    /**
    * Pri postupnom prehrávani/hraní partie táto metóda doplnňuje chýbajúce informácie do
    * aktuálneho ťahu notácie. (napríklad pri krátkom formáte notácie to je štartovacie políčko,
    * využívane neskôr pri kroku spať)
    * @param movementManager Manažer ťahu.
    */
    void completeNotationMovement(MovementManager *movementManager);

    /**
    * Vracia inštanciu triedy NotationMovement pre ťah inštancie predchadzajúceho ťahu.
    * Využíívane pri kroku spať(undo).
    * @return
    */
    NotationMovement *getPrevNotationMovement();

    /**
    * Vracia informáciu o tom či je formát notácie šachovej partie správny.
    * @return Pravdivostná hodnota.
    */
    bool getIsRight ();

    /**
    * Nastaví notáciu ako nesprávnu chybovou hláškou.
    */
    void setWrongNotation();

    void setIsRight(bool is);


};


#endif //ICP_NOTATION_H
