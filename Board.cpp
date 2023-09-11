#include "Board.h"
#include "Piece.h"
#include <map>
#include <string>
#include <ctype.h>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;



Board::Board()
{
    fen = "RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr w KQkq - 0 1";

    Piece whiteKing;
    whiteKing.whiteKing("");
    Piece blackKing;
    blackKing.blackKing("");
    Piece whiteQueen;
    whiteQueen.whiteQueen("");
    Piece blackQueen;
    blackQueen.blackQueen("");
    Piece whiteRook;
    whiteRook.whiteRook("");
    Piece blackRook;
    blackRook.blackRook("");
    Piece whiteBishop;
    whiteBishop.whiteBishop("");
    Piece blackBishop;
    blackBishop.blackBishop("");
    Piece whiteKnight;
    whiteKnight.whiteKnight("");
    Piece blackKnight;
    blackKnight.blackKnight("");
    Piece whitePawn;
    whitePawn.whitePawn("");
    Piece blackPawn;
    blackPawn.blackPawn("");
    Piece pNull;
    pNull.null("");

    FENtoPiece['K'] = whiteKing;
    FENtoPiece['k'] = blackKing;
    FENtoPiece['Q'] = whiteQueen;
    FENtoPiece['q'] = blackQueen;
    FENtoPiece['R'] = whiteRook;
    FENtoPiece['r'] = blackRook;
    FENtoPiece['B'] = whiteBishop;
    FENtoPiece['b'] = blackBishop;
    FENtoPiece['N'] = whiteKnight;
    FENtoPiece['n'] = blackKnight;
    FENtoPiece['P'] = whitePawn;
    FENtoPiece['p'] = blackPawn;
    
    PieceToFEN[whiteKing] = 'K';
    PieceToFEN[blackKing] = 'k';
    PieceToFEN[whiteQueen] = 'Q';
    PieceToFEN[blackQueen] = 'q';
    PieceToFEN[whiteRook] = 'R';
    PieceToFEN[blackRook] = 'r';
    PieceToFEN[whiteBishop] = 'B';
    PieceToFEN[blackBishop] = 'b';
    PieceToFEN[whiteKnight] = 'N';
    PieceToFEN[blackKnight] = 'n';
    PieceToFEN[whitePawn] = 'P';
    PieceToFEN[blackPawn] = 'p';

    readFEN(fen);
}

Board::Board(string f)
{
    fen = f;

    Piece whiteKing;
    whiteKing.whiteKing("");
    Piece blackKing;
    blackKing.blackKing("");
    Piece whiteQueen;
    whiteQueen.whiteQueen("");
    Piece blackQueen;
    blackQueen.blackQueen("");
    Piece whiteRook;
    whiteRook.whiteRook("");
    Piece blackRook;
    blackRook.blackRook("");
    Piece whiteBishop;
    whiteBishop.whiteBishop("");
    Piece blackBishop;
    blackBishop.blackBishop("");
    Piece whiteKnight;
    whiteKnight.whiteKnight("");
    Piece blackKnight;
    blackKnight.blackKnight("");
    Piece whitePawn;
    whitePawn.whitePawn("");
    Piece blackPawn;
    blackPawn.blackPawn("");
    Piece pNull;
    pNull.null("");

    FENtoPiece['K'] = whiteKing;
    FENtoPiece['k'] = blackKing;
    FENtoPiece['Q'] = whiteQueen;
    FENtoPiece['q'] = blackQueen;
    FENtoPiece['R'] = whiteRook;
    FENtoPiece['r'] = blackRook;
    FENtoPiece['B'] = whiteBishop;
    FENtoPiece['b'] = blackBishop;
    FENtoPiece['N'] = whiteKnight;
    FENtoPiece['n'] = blackKnight;
    FENtoPiece['P'] = whitePawn;
    FENtoPiece['p'] = blackPawn;
    
    PieceToFEN[whiteKing] = 'K';
    PieceToFEN[blackKing] = 'k';
    PieceToFEN[whiteQueen] = 'Q';
    PieceToFEN[blackQueen] = 'q';
    PieceToFEN[whiteRook] = 'R';
    PieceToFEN[blackRook] = 'r';
    PieceToFEN[whiteBishop] = 'B';
    PieceToFEN[blackBishop] = 'b';
    PieceToFEN[whiteKnight] = 'N';
    PieceToFEN[blackKnight] = 'n';
    PieceToFEN[whitePawn] = 'P';
    PieceToFEN[blackPawn] = 'p';

    readFEN(fen);
}

Piece Board::getPiece(char fen) const
{
    return FENtoPiece.at(fen);
}

string Board::getFEN()
{ return fen; }

char Board::getSide()
{ return sideToMove; }

int Board::getLegalMoves()
{
    int lm = 0;

    for (int i = 1; i < 65; i++)
    {
        lm += pieceLoc[i].numLegalmoves();
    }

    legalMoves = lm;

    return lm;
}

void Board::readFEN(string fen)
{
    this->fen = fen;
    int count = 0;
    pieceCount = 0;

    Piece piece;
    for (int i = 0; i < fen.size(); i++)
    {

        if (isalpha(fen[i]))
        {
            pieceLoc[i+count+1] = FENtoPiece[fen[i]];
            pieceLoc[count+i+1].setPos(numToNotation(count+1+i));
            if (tolower(fen[i]) != 'p')
                pieceCount++;
        }

        else if (isdigit(fen[i]))
        {
            for (int j = 0; j < fen[i]; j++)
            {
                piece.null(numToNotation(i+j+count+1));
                pieceLoc[i+j+count+1] = piece;
            }
            count += int(fen[i] - '0') - 1;
        }

        else if(fen[i] == '/')
            count--;
    }

    int i = fen.find(" ");

    i++;
    sideToMove = fen[i];
    i += 2;
    while (fen[i] != ' ')
    {
        if (fen[i] == 'K')
            whiteKingsideCastle = true;

        else if (fen[i] == 'k')
            blackKingsideCastle = true;

        else if (fen[i] == 'Q')
            whiteQueensideCastle = true;

        else if (fen[i] == 'q')
            BlackQueensideCastle = true;

        i++;
    }

    i++;

    if (fen[i] != '-')
    {
        enPassant = fen[i] + fen[i+1];
        i++;
    }

    i += 2;

    halfMove = int(fen[i] - '0');

    i += 2;

    fullMove = int(fen[i] - '0');

    updatePieceCount();
    calculateLegalMoves();
    getLegalMoves();
}


void Board::updateFENAfterMove()
{
    string partFEN = "";
    int count = 0;

    for (int i = 1; i < 65; i++)
    {
        if (pieceLoc[i].getID() != '\0')
        {
            if (count == 0)
                partFEN += pieceLoc[i].getID();

            else
            {
                partFEN += char(count + 48);
                partFEN += pieceLoc[i].getID();
                count = 0;
            }
        }

        else
        {
            count++;
        }

        if (count == 8)
        {
            partFEN += "8/";
            count = 0;
        }

        else if ((i % 8) == 0)
        {
            if (count == 0 && i != 64)
                partFEN += '/';

            else if (i != 64)
            {
                partFEN += char(count + 48);
                partFEN += '/';
                count = 0;
            }

            else if (count != 0)
                partFEN += char(count + 48);
        }
    }

    if (sideToMove == 'w')
        sideToMove = 'b';
    
    else if (sideToMove == 'b')
    {
        sideToMove = 'w';
        fullMove++;
    }

    fen[fen.find(' ')+1] = sideToMove;

    count = 1;
    int i = fen.find(' ')+1;
    while (count != 3)
    {
        if (fen[i] == ' ')
            count++;

        i++;
    }

    fen = fen.substr(0, i);

    string str = fen;

    if (enPassant == "-")
        str = fen + '-' + ' ' + char(halfMove + '0') + ' ' + char(fullMove + '0');

    else
        str = fen + char(enPassant[0]) + char(enPassant[1]) + ' ' + char(halfMove + '0') + ' ' + char(fullMove + '0');

    fen = str;
    string f = fen.substr(fen.find(' '), fen.size()-1);
    fen = partFEN + f;
    getLegalMoves();
}

void Board::displayBoard()
{
    int i = 0;
    string reverseFEN = fen;
    stack<char> stack;
    reverse(reverseFEN.begin(), reverseFEN.end());

    while (reverseFEN[i] != 'w' && !(reverseFEN[i] == 'b' && reverseFEN[i-1] == ' '))
        i++;

    i += 2;

    std::cout << "---------------------------------\n";

    while (i < reverseFEN.size())
    {
        if (reverseFEN[i] == '/')
        {
            while (!stack.empty())
            {
                if (isalpha(stack.top()))
                    std::cout << "| " << stack.top() << " ";

                else if (isdigit(stack.top()))
                {
                    for (int j = 0; j < int(stack.top() - '0'); j++)
                        std::cout << "|   ";
                }

                stack.pop();
            }

            std::cout << "|\n---------------------------------\n";
        }

        else 
        {
            stack.push(reverseFEN[i]);
        }

        i++;
    }

    while (!stack.empty())
            {
                if (isalpha(stack.top()))
                    std::cout << "| " << stack.top() << " ";

                else if (isdigit(stack.top()))
                {
                    for (int j = 0; j < int(stack.top() - '0'); j++)
                        std::cout << "|   ";
                }

                stack.pop();
            }

    std::cout << "|\n---------------------------------\n\n";
}

bool Board::movePiece(string startingSquare, string newSquare)
{
    if (!checkLegalMoves(startingSquare, newSquare) || pieceLoc[notationToNum(startingSquare)].getSide() != sideToMove)
    {
        return false;
    }

    int originalPieceCount;
    originalPieceCount = pieceCount;

    Piece piece;
    piece.null(startingSquare);

    pieceLoc[notationToNum(newSquare)] = pieceLoc[notationToNum(startingSquare)];
    pieceLoc[notationToNum(startingSquare)] = piece;
    pieceLoc[notationToNum(newSquare)].setPos(newSquare);
    pieceLoc[notationToNum(newSquare)].eraseLegalmMoves();

    if (pieceLoc[notationToNum(newSquare)].getID() == 'P' && notationToNum(newSquare) == notationToNum(enPassant))
        pieceLoc[notationToNum(newSquare)-8].null(numToNotation(notationToNum(newSquare)-8));

    else if (pieceLoc[notationToNum(newSquare)].getID() == 'p' && notationToNum(newSquare) == notationToNum(enPassant))
        pieceLoc[notationToNum(newSquare)+8].null(numToNotation(notationToNum(newSquare)+8));

    updatePieceCount();

    if (tolower(pieceLoc[notationToNum(newSquare)].getID()) == 'p' || originalPieceCount != pieceCount)
        halfMove = 0;

    else
        halfMove++;

    if (pieceLoc[notationToNum(newSquare)].getID() == 'P' && notationToNum(newSquare)-notationToNum(startingSquare) == 16)
        enPassant = numToNotation(notationToNum(newSquare)-8);

    else if (pieceLoc[notationToNum(newSquare)].getID() == 'p' && notationToNum(newSquare)-notationToNum(startingSquare) == -16)
        enPassant = numToNotation(notationToNum(newSquare)+8);
    
    else
        enPassant = '-';

    updateFENAfterMove();

    return true;
}

void Board::movePieceNotation(string n)
{
    calculateLegalMoves();

    if (n.size() == 2)
    {
        for (int i = 1; i < 65; i++)
        {
            if (tolower(pieceLoc[i].getID()) == 'p')
            {
                for (int j = 0; j < pieceLoc[i].numLegalmoves(); j++)
                {
                    if (pieceLoc[i].getLegalMoveAt(j) == notationToNum(n))
                    {
                        movePiece(numToNotation(i), n);
                        return;
                    }
                }
            }
        }
    }

    else if (n == "O-O")
    {
        if (sideToMove == 'w')
            castle('K');
        
        else if (sideToMove == 'b')
            castle('k');
    }

    else if (n.size() == 3)
    {
        string loc = "";
        loc += n[1];
        loc += n[2];

        for (int i = 1; i < 65; i++)
        {
            if (toupper(pieceLoc[i].getID()) == n[0] && sideToMove == pieceLoc[i].getSide())
            {
                for (int j = 0; j < pieceLoc[i].numLegalmoves(); j++)
                {
                    if (pieceLoc[i].getLegalMoveAt(j) == notationToNum(loc))
                    {
                        movePiece(numToNotation(i), loc);
                    }
                }
            }
        }
    }

    else if (n.size() == 4 && n[1] == 'x' && islower(n[0]))
    {
        string oNot = "", taken = "";
        int oNotInt;
        bool found = false;

        taken += n[2];
        taken += n[3];
        oNot += n[0];
        
        if (sideToMove == 'w')
        {
            oNot += char(n[3] - 1);
        }

        else if (sideToMove == 'b')
        {
            oNot += char(n[3] + 1);
        }

        movePiece(oNot, taken);
    }

    else if (n.size() == 4 && n[1] == 'x' && isupper(n[0]))
    {
        string loc = "";
        loc += n[2];
        loc += n[3];

        for (int i = 1; i < 65; i++)
        {
            if (toupper(pieceLoc[i].getID()) == n[0] && sideToMove == pieceLoc[i].getSide())
            {
                for (int j = 0; j < pieceLoc[i].numLegalmoves(); j++)
                {
                    if (pieceLoc[i].getLegalMoveAt(j) == notationToNum(loc))
                    {
                        movePiece(numToNotation(i), loc);
                    }
                }
            }
        }
    }

    else if (n == "O-O-O")
    {
        if (sideToMove == 'w')
            castle('Q');

        else if (sideToMove == 'b')
            castle('q');
    }
}

void Board::castle(char c)
{
    switch (c)
    {
        case 'K': for (int i = 1; i < 65; i++) {
                if (pieceLoc[i].getSide() == 'b')
                {
                    for (int j = 0; j < pieceLoc[i].numLegalmoves(); j++)
                    {
                        if (pieceLoc[i].getLegalMoveAt(j) == 5 || pieceLoc[i].getLegalMoveAt(j) == 6 || pieceLoc[i].getLegalMoveAt(j) == 7 || pieceLoc[i].getLegalMoveAt(j) == 8 || pieceLoc[8].getID() != 'R' || pieceLoc[5].getID() != 'K' || pieceLoc[6].getID() != '\0' || pieceLoc[7].getID() != '\0')
                        {
                            cout << "Not a legal move\n";
                            return;
                        } 
                    }
                }
            }
            pieceLoc[notationToNum("g1")].whiteKing("g1");
            pieceLoc[notationToNum("e1")].null("e1");
            pieceLoc[notationToNum("f1")].whiteRook("f1");
            pieceLoc[notationToNum("h1")].null("h1");
            break;

        case 'k': for (int i = 1; i < 65; i++) {
                if (pieceLoc[i].getSide() == 'w')
                {
                    for (int j = 0; j < pieceLoc[i].numLegalmoves(); j++)
                    {
                        if (pieceLoc[i].getLegalMoveAt(j) == 64 || pieceLoc[i].getLegalMoveAt(j) == 63 || pieceLoc[i].getLegalMoveAt(j) == 62 || pieceLoc[i].getLegalMoveAt(j) == 61 || pieceLoc[64].getID() != 'r' || pieceLoc[61].getID() != 'k')
                        {
                            cout << "Not a legal move\n";
                            return;
                        } 
                    }
                }
            }
            pieceLoc[notationToNum("g8")].whiteKing("g8");
            pieceLoc[notationToNum("e8")].null("e8");
            pieceLoc[notationToNum("f8")].whiteRook("f8");
            pieceLoc[notationToNum("h8")].null("h8");
            break;

        case 'Q': for (int i = 1; i < 65; i++) {
                if (pieceLoc[i].getSide() == 'b')
                {
                    for (int j = 0; j < pieceLoc[i].numLegalmoves(); j++)
                    {
                        if (pieceLoc[i].getLegalMoveAt(j) == 1 || pieceLoc[i].getLegalMoveAt(j) == 2 || pieceLoc[i].getLegalMoveAt(j) == 3 || pieceLoc[i].getLegalMoveAt(j) == 4 || pieceLoc[i].getLegalMoveAt(j) == 5 || pieceLoc[1].getID() != 'R' || pieceLoc[5].getID() != 'K')
                        {
                            cout << "Not a legal move\n";
                            return;
                        } 
                    }
                }
            }
            pieceLoc[notationToNum("c1")].whiteKing("c1");
            pieceLoc[notationToNum("e1")].null("e1");
            pieceLoc[notationToNum("d1")].whiteRook("d1");
            pieceLoc[notationToNum("a1")].null("a1");
            break;

        case 'q': for (int i = 1; i < 65; i++) {
                if (pieceLoc[i].getSide() == 'w')
                {
                    for (int j = 0; j < pieceLoc[i].numLegalmoves(); j++)
                    {
                        if (pieceLoc[i].getLegalMoveAt(j) == 57 || pieceLoc[i].getLegalMoveAt(j) == 58 || pieceLoc[i].getLegalMoveAt(j) == 59 || pieceLoc[i].getLegalMoveAt(j) == 60 || pieceLoc[i].getLegalMoveAt(j) == 61 || pieceLoc[57].getID() != 'r' || pieceLoc[61].getID() != 'k')
                        {
                            cout << "Not a legal move\n";
                            return;
                        } 
                    }
                }
            }
            pieceLoc[notationToNum("c8")].whiteKing("c8");
            pieceLoc[notationToNum("e8")].null("e8");
            pieceLoc[notationToNum("d8")].whiteRook("d8");
            pieceLoc[notationToNum("a8")].null("a8");
    }
    

    updateFENAfterMove();
}

void Board::calculateLegalMoves()
{
    int count = 0;

    for (int i = 1; i < 65; i++)
    {
        pieceLoc[i].eraseLegalmMoves();
        switch (pieceLoc[i].getID())
        {
            case 'P': if (pieceLoc[i+8].getID() == '\0') pieceLoc[i].addLegalMove(i+8);
                if (i > 8 && i < 17 && pieceLoc[i+16].getID() == '\0' && pieceLoc[i+8].getID() == '\0') pieceLoc[i].addLegalMove(i+16);
                if (pieceLoc[i+7].getSide() == 'b' && i % 8 != 1) pieceLoc[i].addLegalMove(i+7);
                if (pieceLoc[i+9].getSide() == 'b' && i % 8 != 0) pieceLoc[i].addLegalMove(i+9);
                if (notationToNum(enPassant) == i+7) pieceLoc[i].addLegalMove(i+7);
                if (notationToNum(enPassant) == i+9) pieceLoc[i].addLegalMove(i+9);
                break;

            case 'p': if (pieceLoc[i-8].getID() == '\0') pieceLoc[i].addLegalMove(i-8);
                if (i < 57 && i > 48 && pieceLoc[i-16].getID() == '\0' && pieceLoc[i-8].getID() == '\0') pieceLoc[i].addLegalMove(i-16);
                if (pieceLoc[i-7].getSide() == 'w' && i % 8 != 0) pieceLoc[i].addLegalMove(i-7);
                if (pieceLoc[i-9].getSide() == 'w' && i % 8 != 1) pieceLoc[i].addLegalMove(i-9);
                if (notationToNum(enPassant) == i-7) pieceLoc[i].addLegalMove(i-7);
                if (notationToNum(enPassant) == i-9) pieceLoc[i].addLegalMove(i-9);
                break;

            case 'K': if (pieceLoc[i+7].getSide() != 'w' && i+7 < 65 && i % 8 != 1) pieceLoc[i].addLegalMove(i+7);
                if (pieceLoc[i+8].getSide() != 'w' && i+8 < 65) pieceLoc[i].addLegalMove(i+8);
                if (pieceLoc[i+9].getSide() != 'w' && i+9 < 65 && i % 8 != 0) pieceLoc[i].addLegalMove(i+9);
                if (pieceLoc[i+1].getSide() != 'w' && i+1 < 65 && i % 8 != 0) pieceLoc[i].addLegalMove(i+1);
                if (pieceLoc[i-1].getSide() != 'w' && i-1 > 0 && i % 8 != 1) pieceLoc[i].addLegalMove(i-1);
                if (pieceLoc[i-7].getSide() != 'w' && i-7 > 0 && i % 8 != 0) pieceLoc[i].addLegalMove(i-7);
                if (pieceLoc[i-8].getSide() != 'w' && i-8 > 0) pieceLoc[i].addLegalMove(i-8);
                if (pieceLoc[i-9].getSide() != 'w' && i-9 > 0 && i % 8 != 1) pieceLoc[i].addLegalMove(i-9);
                break;

            case 'k': if (pieceLoc[i+7].getSide() != 'b' && i+7 < 65 && i % 8 != 1) pieceLoc[i].addLegalMove(i+7);
                if (pieceLoc[i+8].getSide() != 'b' && i+8 < 65) pieceLoc[i].addLegalMove(i+8);
                if (pieceLoc[i+9].getSide() != 'b' && i+9 < 65 && i % 8 != 0) pieceLoc[i].addLegalMove(i+9);
                if (pieceLoc[i+1].getSide() != 'b' && i+1 < 65 && i % 8 != 0) pieceLoc[i].addLegalMove(i+1);
                if (pieceLoc[i-1].getSide() != 'b' && i-1 > 0 && i % 8 != 1) pieceLoc[i].addLegalMove(i-1);
                if (pieceLoc[i-7].getSide() != 'b' && i-7 > 0 && i % 8 != 0) pieceLoc[i].addLegalMove(i-7);
                if (pieceLoc[i-8].getSide() != 'b' && i-8 > 0) pieceLoc[i].addLegalMove(i-8);
                if (pieceLoc[i-9].getSide() != 'b' && i-9 > 0 && i % 8 != 1) pieceLoc[i].addLegalMove(i-9);
                break;

            case 'N': if (pieceLoc[i+6].getSide() != 'w' && i+6 < 65 && i % 8 != 2 && i % 8 != 1) pieceLoc[i].addLegalMove(i+6);
                if (pieceLoc[i+15].getSide() != 'w' && i+15 < 65 && i % 8 != 1) pieceLoc[i].addLegalMove(i+15);
                if (pieceLoc[i+17].getSide() != 'w' && i+17 < 65 && i % 8 != 0) pieceLoc[i].addLegalMove(i+17);
                if (pieceLoc[i+10].getSide() != 'w' && i+10 < 65 && i % 8 < 7 && i % 8 != 0) pieceLoc[i].addLegalMove(i+10);
                if (pieceLoc[i-10].getSide() != 'w' && i-10 > 0 && i % 8 != 2 && i % 8 != 1) pieceLoc[i].addLegalMove(i-10);
                if (pieceLoc[i-6].getSide() != 'w' && i-6 > 0 && i % 8 < 7 && i % 8 != 0) pieceLoc[i].addLegalMove(i-6);
                if (pieceLoc[i-15].getSide() != 'w' && i-15 > 0 && i % 8 != 0) pieceLoc[i].addLegalMove(i-15);
                if (pieceLoc[i-17].getSide() != 'w' && i-17 > 0 && i % 8 != 1) pieceLoc[i].addLegalMove(i-17);
                break;

            case 'n': if (pieceLoc[i+6].getSide() != 'b' && i+6 < 65 && i % 8 != 2 && i % 8 != 1) pieceLoc[i].addLegalMove(i+6);
                if (pieceLoc[i+15].getSide() != 'b' && i+15 < 65 && i % 8 != 1) pieceLoc[i].addLegalMove(i+15);
                if (pieceLoc[i+17].getSide() != 'b' && i+17 < 65 && i % 8 != 0) pieceLoc[i].addLegalMove(i+17);
                if (pieceLoc[i+10].getSide() != 'b' && i+10 < 65 && i % 8 < 7 && i % 8 != 0) pieceLoc[i].addLegalMove(i+10);
                if (pieceLoc[i-10].getSide() != 'b' && i-10 > 0 && i % 8 != 2 && i % 8 != 1) pieceLoc[i].addLegalMove(i-10);
                if (pieceLoc[i-6].getSide() != 'b' && i-6 > 0 && i % 8 < 7 && i % 8 != 0) pieceLoc[i].addLegalMove(i-6);
                if (pieceLoc[i-15].getSide() != 'b' && i-15 > 0 && i % 8 != 0) pieceLoc[i].addLegalMove(i-15);
                if (pieceLoc[i-17].getSide() != 'b' && i-17 > 0 && i % 8 != 1) pieceLoc[i].addLegalMove(i-17);
                break;

            case 'B': count = i;
                while (count+9 < 65 && pieceLoc[count+9].getSide() != 'w' && count+9 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count+9);

                    if (pieceLoc[count+9].getSide() == 'b')
                        break;
                    
                    count += 9;
                }
                count = i;
                while (count+7 < 65 && pieceLoc[count+7].getSide() != 'w' && count+7 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count+7);

                    if (pieceLoc[count+7].getSide() == 'b')
                        break;
                    
                    count += 7;
                }
                count = i;
                while (count-7 > 0 && pieceLoc[count-7].getSide() != 'w' && count-7 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count-7);

                    if (pieceLoc[count-7].getSide() == 'b')
                        break;
                    
                    count -= 7;
                }
                count = i;
                while (count-9 > 0 && pieceLoc[count-9].getSide() != 'w' && count-9 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count-9);

                    if (pieceLoc[count-9].getSide() == 'b')
                        break;
                    
                    count -= 9;
                }
                count = 0;
                break;

            case 'b': count = i;
                while (count+9 < 65 && pieceLoc[count+9].getSide() != 'b' && count+9 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count+9);

                    if (pieceLoc[count+9].getSide() == 'w')
                        break;
                    
                    count += 9;
                }
                count = i;
                while (count+7 < 65 && pieceLoc[count+7].getSide() != 'b' && count+7 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count+7);

                    if (pieceLoc[count+7].getSide() == 'w')
                        break;
                    
                    count += 7;
                }
                count = i;
                while (count-7 > 0 && pieceLoc[count-7].getSide() != 'b' && count-7 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count-7);

                    if (pieceLoc[count-7].getSide() == 'w')
                        break;
                    
                    count -= 7;
                }
                count = i;
                while (count-9 > 0 && pieceLoc[count-9].getSide() != 'b' && count-9 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count-9);

                    if (pieceLoc[count-9].getSide() == 'w')
                        break;
                    
                    count -= 9;
                }
                count = 0;
                break;

            case 'R': count = i;
                while (count+8 < 65 && pieceLoc[count+8].getSide() != 'w')
                {
                    pieceLoc[i].addLegalMove(count+8);

                    if (pieceLoc[count+8].getSide() == 'b')
                        break;
                    
                    count += 8;
                }
                count = i;
                while (count+1 < 65 && pieceLoc[count+1].getSide() != 'w' && count+1 != 0)
                {
                    pieceLoc[i].addLegalMove(count+1);

                    if (pieceLoc[count+1].getSide() == 'b')
                        break;
                    
                    count += 1;
                }
                count = i;
                while (count-1 > 0 && pieceLoc[count-1].getSide() != 'w' && count-1 != 1)
                {
                    pieceLoc[i].addLegalMove(count-1);

                    if (pieceLoc[count-1].getSide() == 'b')
                        break;
                    
                    count -= 1;
                }
                count = i;
                while (count-8 > 0 && pieceLoc[count-8].getSide() != 'w')
                {
                    pieceLoc[i].addLegalMove(count-8);

                    if (pieceLoc[count-8].getSide() == 'b')
                        break;
                    
                    count -= 8;
                }
                count = 0;
                break;

            case 'r': count = i;
                while (count+8 < 65 && pieceLoc[count+8].getSide() != 'b')
                {
                    pieceLoc[i].addLegalMove(count+8);

                    if (pieceLoc[count+8].getSide() == 'w')
                        break;
                    
                    count += 8;
                }
                count = i;
                while (count+1 < 65 && pieceLoc[count+1].getSide() != 'b' && count+1 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count+1);

                    if (pieceLoc[count+1].getSide() == 'w')
                        break;
                    
                    count += 1;
                }
                count = i;
                while (count-1 > 0 && pieceLoc[count-1].getSide() != 'b' && count-1 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count-1);

                    if (pieceLoc[count-1].getSide() == 'w')
                        break;
                    
                    count -= 1;
                }
                count = i;
                while (count-8 > 0 && pieceLoc[count-8].getSide() != 'b')
                {
                    pieceLoc[i].addLegalMove(count-8);

                    if (pieceLoc[count-8].getSide() == 'w')
                        break;
                    
                    count -= 8;
                }
                count = 0;
                break;

            case 'Q': count = i;
                while (count+8 < 65 && pieceLoc[count+8].getSide() != 'w')
                {
                    pieceLoc[i].addLegalMove(count+8);

                    if (pieceLoc[count+8].getSide() == 'b')
                        break;
                    
                    count += 8;
                }
                count = i;
                while (count+1 < 65 && pieceLoc[count+1].getSide() != 'w' && count+1 != 0)
                {
                    pieceLoc[i].addLegalMove(count+1);

                    if (pieceLoc[count+1].getSide() == 'b')
                        break;
                    
                    count += 1;
                }
                count = i;
                while (count-1 > 0 && pieceLoc[count-1].getSide() != 'w' && count-1 != 1)
                {
                    pieceLoc[i].addLegalMove(count-1);

                    if (pieceLoc[count-1].getSide() == 'b')
                        break;
                    
                    count -= 1;
                }
                count = i;
                while (count-8 > 0 && pieceLoc[count-8].getSide() != 'w')
                {
                    pieceLoc[i].addLegalMove(count-8);

                    if (pieceLoc[count-8].getSide() == 'b')
                        break;
                    
                    count -= 8;
                }
                count = i;
                while (count+9 < 65 && pieceLoc[count+9].getSide() != 'w' && count+9 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count+9);

                    if (pieceLoc[count+9].getSide() == 'b')
                        break;
                    
                    count += 9;
                }
                count = i;
                while (count+7 < 65 && pieceLoc[count+7].getSide() != 'w' && count+7 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count+7);

                    if (pieceLoc[count+7].getSide() == 'b')
                        break;
                    
                    count += 7;
                }
                count = i;
                while (count-7 > 0 && pieceLoc[count-7].getSide() != 'w' && count-7 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count-7);

                    if (pieceLoc[count-7].getSide() == 'b')
                        break;
                    
                    count -= 7;
                }
                count = i;
                while (count-9 > 0 && pieceLoc[count-9].getSide() != 'w' && count-9 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count-9);

                    if (pieceLoc[count-9].getSide() == 'b')
                        break;
                    
                    count -= 9;
                }
                break;

            case 'q': count = i;
                while (count+8 < 65 && pieceLoc[count+8].getSide() != 'b')
                {
                    pieceLoc[i].addLegalMove(count+8);

                    if (pieceLoc[count+8].getSide() == 'w')
                        break;
                    
                    count += 8;
                }
                count = i;
                while (count+1 < 65 && pieceLoc[count+1].getSide() != 'b' && count+1 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count+1);

                    if (pieceLoc[count+1].getSide() == 'w')
                        break;
                    
                    count += 1;
                }
                count = i;
                while (count-1 > 0 && pieceLoc[count-1].getSide() != 'b' && count-1 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count-1);

                    if (pieceLoc[count-1].getSide() == 'w')
                        break;
                    
                    count -= 1;
                }
                count = i;
                while (count-8 > 0 && pieceLoc[count-8].getSide() != 'b')
                {
                    pieceLoc[i].addLegalMove(count-8);

                    if (pieceLoc[count-8].getSide() == 'w')
                        break;
                    
                    count -= 8;
                }
                count = i;
                while (count+9 < 65 && pieceLoc[count+9].getSide() != 'b' && count+9 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count+9);

                    if (pieceLoc[count+9].getSide() == 'w')
                        break;
                    
                    count += 9;
                }
                count = i;
                while (count+7 < 65 && pieceLoc[count+7].getSide() != 'b' && count+7 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count+7);

                    if (pieceLoc[count+7].getSide() == 'w')
                        break;
                    
                    count += 7;
                }
                count = i;
                while (count-7 > 0 && pieceLoc[count-7].getSide() != 'b' && count-7 % 8 != 1)
                {
                    pieceLoc[i].addLegalMove(count-7);

                    if (pieceLoc[count-7].getSide() == 'w')
                        break;
                    
                    count -= 7;
                }
                count = i;
                while (count-9 > 0 && pieceLoc[count-9].getSide() != 'b' && count-9 % 8 != 0)
                {
                    pieceLoc[i].addLegalMove(count-9);

                    if (pieceLoc[count-9].getSide() == 'w')
                        break;
                    
                    count -= 9;
                }
                break; 
        }
    }
}

bool Board::checkLegalMoves(string startingSquare, string newSquare)
{
    calculateLegalMoves();

    for (int i = 0; i < pieceLoc[notationToNum(startingSquare)].numLegalmoves(); i++)
    {
        if (pieceLoc[notationToNum(startingSquare)].getLegalMoveAt(i) == notationToNum(newSquare))
            return true;
    }

    return false;
}

Piece Board::getPieceAt(int i)
{ return pieceLoc[i]; }

int Board::updatePieceCount()
{
    int count = 0;
    for (int i = 1; i < 65; i++)
    {
        if (tolower(pieceLoc[i].getID()) != 'p' && pieceLoc[i].getID() != '\0')
            count++;
    }
    pieceCount = count;
    return pieceCount;
}

int Board::calculateMaterial(int num)
{
    if (num == 1)
        return pieceLoc[num].getVal();

    else   
        return pieceLoc[num].getVal() + calculateMaterial(num-1);
}

string Board::numToNotation(int i)
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

int Board::notationToNum(string str)
{
    int num;
    num = int(str[0]) - int('a') + 1 + (int(str[1] - '0') - 1)*8;
    return num;
}