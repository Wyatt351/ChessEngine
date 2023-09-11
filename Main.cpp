#include "Piece.h"
#include "Board.h"
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{ 
    Board board;
    string start, end, cont;

    while (cont != "n")
    {
        cout << "Enter start: ";
        cin >> start;
        cout << "Enter end: ";
        cin >> end;

        if (board.movePiece(start, end))
            board.displayBoard();
        else
            cout << "\nNot legal Move\n\n";

        cout << "Continue? (y/n): ";
        cin >> cont;

        while (cont != "n" && cont != "y") 
        {
            cout << "Not a valid input\nContinue? (y/n):";
            cin >> cont;
        } 
    }

    return 0;
}