/**
 * chesstypes.h
 *
 * Typy pro šachové figury
 *
 * @author Jan Holásek (xholas09)
 */

#ifndef CHESSTYPES_H
#define CHESSTYPES_H

enum class TeamColor
{
    white,
    black
};

enum class FigureType
{
    pawn,
    rook,
    knight,
    bishop,
    queen,
    king,

    invalid
};

#endif // CHESSTYPES_H
