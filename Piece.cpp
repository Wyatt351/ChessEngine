#include "Piece.h"
#include <cstddef>
#include <string>

//Used to move the piece
void Piece::move(string m)
{ position = m; }
//returns ID of piece
char Piece::getID() const
{ return id; }
//returns side/color of piece
char Piece::getSide() const
{ return side; }
//returns position of piece
string Piece::getPos()
{ return position; }
//
void Piece::setPos(string pos)
{ position = pos; }
float Piece::getVal()
{ return value; }
int Piece::getCenterControl()
{
    centerControl = 0;
    if (tolower(id) != 'p')
    {
        for (int i = 0; i < numLegalmoves(); i++)
        {
            if (getLegalMoveAt(i) == 28 || getLegalMoveAt(i) == 29 || getLegalMoveAt(i) == 36 || getLegalMoveAt(i) == 37)
            {
                centerControl++;
            }
        }
    }

    if (id == 'P')
    {
        for (int i = 0; i < numLegalmoves(); i++)
        {
            if ((getLegalMoveAt(i) == 28 || getLegalMoveAt(i) == 29 || getLegalMoveAt(i) == 36 || getLegalMoveAt(i) == 37) && (getLegalMoveAt(i) == notationToNum(position)+9 || getLegalMoveAt(i) == notationToNum(position)+7))
                centerControl++;
        }
    }

    if (id == 'p')
    {
        for (int i = 0; i < numLegalmoves(); i++)
        {
            if ((getLegalMoveAt(i) == 28 || getLegalMoveAt(i) == 29 || getLegalMoveAt(i) == 36 || getLegalMoveAt(i) == 37) && (getLegalMoveAt(i) == notationToNum(position)-9 || getLegalMoveAt(i) == notationToNum(position)-7))
                centerControl++;
        }
    }
    return centerControl;
}

void Piece::addLegalMove(int sq)
{ legalMoves.push_back(sq); }
int Piece::numLegalmoves()
{ return legalMoves.size(); }
int Piece::getLegalMoveAt(int index)
{ return legalMoves[index]; }
void Piece::eraseLegalmMoves()
{ legalMoves.clear(); }
void Piece::whiteKing(string pos)
{
    id = 'K';
    side = 'w';
    value = 318;
    position = pos;
}
void Piece::blackKing(string pos)
{
    id = 'k';
    side = 'b';
    value = -318;
    position = pos;
}
void Piece::whiteQueen(string pos)
{
    id = 'Q';
    side = 'w';
    value = 9;
    position = pos;
}
void Piece::blackQueen(string pos)
{
    id = 'q';
    side = 'b';
    value = -9;
    position = pos;
}
void Piece::whiteRook(string pos)
{
    id = 'R';
    side = 'w';
    value = 5;
    position = pos;
}
void Piece::blackRook(string pos)
{
    id = 'r';
    side = 'b';
    value = -5;
    position = pos;
}
void Piece::whiteBishop(string pos)
{
    id = 'B';
    side = 'w';
    value = 3;
    position = pos;
}
void Piece::blackBishop(string pos)
{
    id = 'b';
    side = 'b';
    value = -3;
    position = pos;
}
void Piece::whiteKnight(string pos)
{
    id = 'N';
    side = 'w';
    value = 3;
    position = pos;
}
void Piece::blackKnight(string pos)
{
    id = 'n';
    side = 'b';
    value = -3;
    position = pos;
}
void Piece::whitePawn(string pos)
{
    id = 'P';
    side = 'w';
    value = 1;
    position = pos;
}
void Piece::blackPawn(string pos)
{
    id = 'p';
    side = 'b';
    value = -1;
    position = pos;
}
void Piece::null(string pos)
{
    id = '\0';
    side = '\0';
    value = 0;
    position = pos;
}
string Piece::numToNotation(int i)
{
    char letter, number;
    string notation = "";
    letter = char((i-1)%8 + 97);
    if (letter == 'h')
    {
        number = char(i/8-1 + '1');
    }
    else
        number = char(i/8 + '1');

    notation += letter;
    notation += number;
    return notation;
}

int Piece::notationToNum(string str)
{
    int num;
    num = int(str[0]) - int('a') + 1 + (int(str[1] - '0') - 1)*8;
    return num;
}