#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <vector>
using namespace std;

class Piece
{
private:
    char id, side;
    float value;
    string position;
    vector<int> legalMoves;
    int centerControl;
public:
    void move(string);
    char getID() const;
    char getSide() const;
    float getVal();
    string getPos();
    int getCenterControl();
    int numLegalmoves();
    int getLegalMoveAt(int);
    void eraseLegalmMoves();
    void addLegalMove(int);
    void setPos(string);
    void whiteKing(string);
    void blackKing(string);
    void whiteQueen(string);
    void blackQueen(string);
    void whiteRook(string);
    void blackRook(string);
    void whiteBishop(string);
    void blackBishop(string);
    void whiteKnight(string);
    void blackKnight(string);
    void whitePawn(string);
    void blackPawn(string);
    void null(string);  
    struct compare
    {
        bool operator() (const Piece& left, const Piece& right) const
        {
            return left.getID() < right.getID();
        }
    };
    string numToNotation(int);
    int notationToNum(string);
};

#endif