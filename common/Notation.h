//
// Created by Jozef on 4/24/2019.
//

#ifndef ICP_NOTATION_H
#define ICP_NOTATION_H


#include <vector>
#include <string>
class NotationMovement;
class FiguresManager;
class MovementManager;
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

    void removeUselessNotMovs();
    void removeUselessLines();
    void addNotMovToNotationLines(FiguresManager *figuresManager, MovementManager *movementManager,
                                  NotationMovement *mov);
    bool getFileContent();

    void ltrim(std::string &s);
    void rtrim(std::string &s);
    void trim(std::string &s);
    void removeSpaces(std::vector<std::string> &vec);
    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);



public:
    Notation(std::string path);
    ~Notation();
    void processNotation();
    void addPlayerNotationMovement(FiguresManager *figuresManager, MovementManager *movementManager);
    bool saveNotation();
    bool saveNotationToAnotherFile(std::string path);
    bool isFirstIndex();
    bool isLastIndex();
    std::vector<std::string> getGameNotationLines();
    int getIndexProcNotMov();
    bool getIsEmpty();
    NotationMovement *getActualNotMov();
    void incrementIndexOfNotationLines();
    void decrementIndexOfNotationLines();
    int getChangingFigureID();
    void completeNotationMovement(MovementManager *movementManager);
    NotationMovement *getPrevNotationMovement();
    bool getIsRight ();
    void setWrongNotation();



};


#endif //ICP_NOTATION_H
