/**
 * Trieda obsahuje reprezentáciu políčka šachovnice.
 * @author Jozef Ondria
 * @author Jan Holásek
 */

#ifndef ICP_FIELD_H
#define ICP_FIELD_H




#define DIRECTIONCOUNT 8
class Figure;

/**
 * Trieda reprezentujúca jedno políčko na šachovníci.
 * Implementuje rozhranie Field.
 */
class Field
{
private:
    int row;
    int col;
    Figure *figure;
    Field **nextFields;

public:
    enum Direction {D, L, LD, LU, R, RD, RU, U, NONE};
    static Direction *myValues()
    {
        static Direction directions[] = {D, L, LD, LU, R, RD, RU, U};
        return  directions;
    }

    /**
     * Inicializuje políčko.
     * @param col Stlpec políčka na šachovnici.
     * @param row Riadok políčka na šachovnici.
     */
    Field(int col, int row);

    /**
     * Deštruktor.
     */
    ~Field();

    /**
     * Vráti pozíciu stlpca na šachovnici tohto políčka.
     * @return Hodnotu slpca.
     */
    int getColPos();

    /**
     * Vráti pozíciu riadka na šachovnici tohto políčka.
     * @return Hodnotu riadka.
     */
    int getRowPos();

    /**
     * Pridáva políčku susedné políčko v smere na šachovnici.
     * @param dirs Smer na šachovnici.
     * @param field Plíčko ktoré prídá ako susedné.
     */
    void addNextField(Direction dirs, Field *field);

    /**
     * Vráti figúrku ležiacu na danom políčku.
     * @return Odkaz na figúrku.
     */
    Figure *get();

    /**
     * Testovanie či je dané políčko prázdne.
     * @return Úspešnosť testu.
     */
    bool isEmpty();

    /**
     * Vracia susedné políčko tohto políčka v danom smere.
     * @param dirs Smer na šachovnici.
     * @return Odkaz na políčko.
     */
    Field *nextField(Direction dirs);

    /**
     * Vloží danú figúrku na toto políčko a testuje úspešnosť tohto úkonu.
     * @param figure Figúrka ktorá má byť vložená na políčko.
     * @return Úspešnosť testu.
     */
    bool put(Figure *figure);

    /**
     * Odstráni danú figúrku z tohto políčka a testuje úspešnosť tohto úkonu.
     * @param figure Figúrka ktorá má byť odstránená z políčka.
     * @return Úspešnosť testu.
     */
    bool remove(Figure *figure);
};


#endif //ICP_FIELD_H
