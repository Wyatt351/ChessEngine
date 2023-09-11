#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
#include <map>
using namespace std;

class Board
{
private:
    map<int, Piece> pieceLoc;
    map<char, Piece> FENtoPiece;
    map<Piece, char, Piece::compare> PieceToFEN;
    char sideToMove;
    bool whiteKingsideCastle = false, blackKingsideCastle = false, whiteQueensideCastle = false, BlackQueensideCastle = false;
    string enPassant, fen;
    int halfMove, fullMove, pieceCount, legalMoves;
public:
    Board();
    Board(string);
    Piece getPiece(char) const;
    string getFEN();
    char getSide();
    int getLegalMoves();
    void readFEN(string);
    void updateFENAfterMove();
    void displayBoard();
    bool movePiece(string, string);
    void movePieceNotation(string);
    void castle(char);
    void calculateLegalMoves();
    bool checkLegalMoves(string, string);
    int updatePieceCount();
    int calculateMaterial(int num = 64);
    Piece getPieceAt(int);
    string numToNotation(int);
    int notationToNum(string);
};

#endif