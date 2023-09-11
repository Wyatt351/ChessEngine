#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include "Engine.h"
#include "Board.h"
#include "Piece.h"
using namespace std;

Engine::Engine()
{
    Node* ptr;
    ptr = new Node;
    //materialCount = board.calculateMaterial();
    head = make_unique<Node>(ptr);
    head->nodeBoard.readFEN("RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr w KQkq - 0 1");
}

Engine::Engine(string a)
{
    board.readFEN(a);
    //materialCount = board.calculateMaterial();
    Node* ptr;
    ptr = new Node;
    ptr->nodeBoard.readFEN(a);
    //materialCount = board.calculateMaterial();
    head = make_unique<Node>(ptr);
    head->nodeBoard.readFEN(a);
}

/**Engine::Node::~Node()
{
    for (int i = 0; i < next.size(); i++)
        next[i]->~Node();

    for (int i = 0; i < next.size(); i++)
        delete next[i];
}*/

/**Engine::~Engine()
{

    delete head;
}*/

bool Engine::movePieceNode(string startingSquare, string newSquare, shared_ptr<Engine::Node> b)
{
    bool inCheck = false;
    Board alt(b->nodeBoard.getFEN());

    if (!alt.movePiece(startingSquare, newSquare))
        return false;

    alt.calculateLegalMoves();

    for (int i = 1; i < 65; i++)
    {
        if (alt.getPieceAt(i).getSide() == alt.getSide())
        {
            for (int j = 0; j < alt.getPieceAt(i).numLegalmoves(); j++)
            {
                if (tolower(alt.getPieceAt(alt.getPieceAt(i).getLegalMoveAt(j)).getID()) == 'k' && alt.getSide() != alt.getPieceAt(alt.getPieceAt(i).getLegalMoveAt(j)).getSide())
                    inCheck = true;
            }
        }
    }

    if (inCheck)
    {
        return false;
    }

    else
    {
        b->nodeBoard.movePiece(startingSquare, newSquare);
    }

    return true;
}

bool Engine::movePiece(string startingSquare, string newSquare)
{
    bool inCheck = false;
    Board alt(board.getFEN());

    if (!alt.movePiece(startingSquare, newSquare))
        return false;

    alt.calculateLegalMoves();

    for (int i = 1; i < 65; i++)
    {
        if (alt.getPieceAt(i).getSide() == alt.getSide())
        {
            for (int j = 0; j < alt.getPieceAt(i).numLegalmoves(); j++)
            {
                if (tolower(alt.getPieceAt(alt.getPieceAt(i).getLegalMoveAt(j)).getID()) == 'k' && alt.getSide() != alt.getPieceAt(alt.getPieceAt(i).getLegalMoveAt(j)).getSide())
                    inCheck = true;
            }
        }
    }

    if (inCheck)
    {
        return false;
    }

    else
    {
        board.movePiece(startingSquare, newSquare);
    }

    return true;
}

void Engine::displayBoard()
{
    board.displayBoard();
}

void Engine::evaluate(int depth, int montDepth, shared_ptr<Node> node)
{
    shared_ptr<Node> nextNode;

    cout << depth << endl;

    if (depth == -1)
    {
        node->mob = 0;
        for (int i = 1; i < 65; i++)
        { 
            if (node->nodeBoard.getPieceAt(i).getID() != '\0' && node->nodeBoard.getPieceAt(i).getSide() == node->nodeBoard.getSide())
            {
                for (int j = 0; j < node->nodeBoard.getPieceAt(i).numLegalmoves(); j++)
                {
                    board.readFEN(node->nodeBoard.getFEN());
                    //node->next[node->next.size()-1]->prev = node;
                    if (movePiece(node->nodeBoard.numToNotation(i), node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j))))
                    {
                        node->mob++;
                        //cout << node->nodeBoard.numToNotation(i) << ' ' << node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)) << endl;       
                    }
                }
            }
        }
        node->eval = true;

        return;
    }

    else if (depth == 0 && node->eval == false)
    {
        node->mob = 0;
        node->center = 0;
        for (int i = 1; i < 65; i++)
        {
            if (node->nodeBoard.getPieceAt(i).getID() != '\0' && node->nodeBoard.getPieceAt(i).getSide() == node->nodeBoard.getSide())
            {
                for (int j = 0; j < node->nodeBoard.getPieceAt(i).numLegalmoves(); j++)
                {
                    node->next.push_back(make_unique<Node>(node));
                    nextNode = make_unique<Node>(node->next[node->next.size()-1]);
                    if (movePieceNode(node->nodeBoard.numToNotation(i), node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)), nextNode) && node->nodeBoard.getPieceAt(i).getCenterControl() < nextNode->nodeBoard.getPieceAt(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)).getCenterControl())
                    {
                        node->mob++;
                        //cout << node->nodeBoard.numToNotation(i) << ' ' << node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)) << endl;                    
                        if (nextNode->nodeBoard.getSide() == 'w')
                            nextNode->mat = nextNode->nodeBoard.calculateMaterial();

                        else
                            nextNode->mat = -nextNode->nodeBoard.calculateMaterial();

                        for (int a = 1; a < 65; a++)
                        {
                            nextNode->center += nextNode->nodeBoard.getPieceAt(a).getCenterControl();
                        }
                    }
                    else if (movePieceNode(node->nodeBoard.numToNotation(i), node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)), nextNode))
                    {
                        node->mob++;
                        node->next.erase(node->next.begin()+node->next.size()-1);
                    }
                    else
                    {
                        node->next.erase(node->next.begin()+node->next.size()-1);
                    }
                }
            }
        }
        node->eval = true;
    }

    else if (depth != 0 && node->eval == false)
    {
        for (int i = 1; i < 65; i++)
        {
            if (node->nodeBoard.getPieceAt(i).getID() != '\0' && node->nodeBoard.getPieceAt(i).getSide() == node->nodeBoard.getSide())
            {
                for (int j = 0; j < node->nodeBoard.getPieceAt(i).numLegalmoves(); j++)
                {
                    node->next.push_back(make_unique<Node>(node));
                    nextNode = make_unique<Node>(node->next[node->next.size()-1]);
                    //node->next[node->next.size()-1]->prev = node;
                    if (!movePieceNode(node->nodeBoard.numToNotation(i), node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)), nextNode))
                    {
                        if (node->nodeBoard.getPieceAt(i).getCenterControl() >= nextNode->nodeBoard.getPieceAt(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)).getCenterControl())
                            node->next.erase(node->next.begin()+node->next.size()-1);   
                    }
                }
            }
        }
        node->eval = true;
    }

    for (int i = 0; i < node->next.size(); i++)
        evaluate(depth-1, montDepth, node->next[i]);

    if (depth == 0 && node->nodeBoard.getSide() == head->nodeBoard.getSide())
    {
        for (int i = 0; i < node->next.size(); i++)
        {
            if (node->next[i]->mat < node->next[node->bestFrom]->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->center < node->next[node->bestFrom]->center && node->next[i]->mat == node->next[node->bestFrom]->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->mob < node->next[node->bestFrom]->mob && node->next[i]->center == node->next[node->bestFrom]->center && node->next[i]->mat == node->next[node->bestFrom]->mat)
            {
                node->bestFrom = i;
            }
        }
        node->best = node->next[node->bestFrom];
        cout << '0' << endl;
    }

    else if (depth == 0)
    {
        for (int i = 0; i < node->next.size(); i++)
        {
            if (node->next[i]->mat > node->next[node->bestFrom]->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->center > node->next[node->bestFrom]->center && node->next[i]->mat == node->next[node->bestFrom]->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->mob > node->next[node->bestFrom]->mob && node->next[i]->center == node->next[node->bestFrom]->center && node->next[i]->mat == node->next[node->bestFrom]->mat)
            {
                node->bestFrom = i;
            }
        }
        node->best = node->next[node->bestFrom];

        cout << '0' << endl;
    }


    else if (depth != 0 && node->next[0]->best->nodeBoard.getSide() != head->nodeBoard.getSide())
    {
        for (int i = 0; i < node->next.size(); i++)
        {
            if (node->next[i]->best->mat < node->next[node->bestFrom]->best->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->best->center < node->next[node->bestFrom]->best->center && node->next[i]->best->mat == node->next[node->bestFrom]->best->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->best->mob < node->next[node->bestFrom]->best->mob && node->next[i]->best->center == node->next[node->bestFrom]->best->center && node->next[i]->best->mat == node->next[node->bestFrom]->best->mat)
            {
                node->bestFrom = i;
            }
        }
        cout << '1' << endl;
    }

    else if (depth != 0)
    {
        for (int i = 0; i < node->next.size(); i++)
        {
            if (node->next[i]->best->mat > node->next[node->bestFrom]->best->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->best->center > node->next[node->bestFrom]->best->center && node->next[i]->best->mat == node->next[node->bestFrom]->best->mat)
            {
                node->bestFrom = i;
            }

            else if (node->next[i]->best->mob > node->next[node->bestFrom]->best->mob && node->next[i]->best->center == node->next[node->bestFrom]->best->center && node->next[i]->best->mat == node->next[node->bestFrom]->best->mat)
            {
                node->bestFrom = i;
            }
        }
        cout << '1' << endl;
    }
}

void Engine::playBest()
{
    head = head->next[head->bestFrom];
    board.readFEN(head->nodeBoard.getFEN());
}

/**
void Engine::search(int depth, Node *b)
{
    Node *node, *cNext;
    node = b;
    int count = -1;

    node->nodeBoard.calculateLegalMoves();

    if (depth == 0)
    {
        for (int i = 1; i < 65; i++)
        {
            if (node->nodeBoard.getPieceAt(i).getID() != '\0')
            {
                for (int j = 0; j < node->nodeBoard.getPieceAt(i).numLegalmoves(); j++)
                {
                    node = b;
                    node->next.push_back(new Node(*b));
                    count++;
                    if (movePiece(node->nodeBoard.numToNotation(i), node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)), cNext->nodeBoard))
                    {
                        node->mob++;
                    }
                    else
                    {
                        node->next.erase(node->next.begin()+count);
                        count--;
                    }
                }
            }
        }
        b->next.erase(b->next.begin()+count);

        return;
    }

    node->mat = node->nodeBoard.calculateMaterial();
    node->nodeBoard.calculateLegalMoves();
    for (int a = 1; a < 65; a++)
    {
        for (int c = 0; c < node->nodeBoard.getPieceAt(a).numLegalmoves(); c++)
        {
            if ((node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 29 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 30 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 36 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 37) && node->nodeBoard.getPieceAt(a).getID() == node->nodeBoard.getSide())
                node->center++;
            else if ((node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 29 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 30 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 36 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 37) && node->nodeBoard.getPieceAt(a).getID() != node->nodeBoard.getSide())
                node->center--;
        }
    }

    for (int i = 1; i < 65; i++)
    {
        if (node->nodeBoard.getPieceAt(i).getID() != '\0' && node->nodeBoard.getPieceAt(i).getSide() == node->nodeBoard.getSide())
        {
            for (int j = 0; j < node->nodeBoard.getPieceAt(i).numLegalmoves(); j++)
            {
                node = b;
                node->next.push_back(new Node(*b));
                count++;
                cNext = node->next[count];
                if (movePiece(node->nodeBoard.numToNotation(i), node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j)), cNext->nodeBoard))
                {
                    cout << node->nodeBoard.numToNotation(node->nodeBoard.getPieceAt(i).getLegalMoveAt(j));
                    node->mob++;
                    node = cNext;
                    node->mat = node->nodeBoard.calculateMaterial();
                    node->nodeBoard.calculateLegalMoves();
                    for (int a = 1; a < 65; a++)
                    {
                        for (int c = 0; c < node->nodeBoard.getPieceAt(a).numLegalmoves(); c++)
                        {
                            if ((node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 29 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 30 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 36 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 37) && node->nodeBoard.getPieceAt(a).getID() == node->nodeBoard.getSide())
                                node->center++;
                            else if ((node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 29 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 30 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 36 || node->nodeBoard.getPieceAt(a).getLegalMoveAt(c) == 37) && node->nodeBoard.getPieceAt(a).getID() != node->nodeBoard.getSide())
                                node->center--;
                        }
                    }
                }
                else
                {
                    node->next.erase(node->next.begin()+count);
                    count--;
                }
            }
        }
    }

    b->next.erase(b->next.begin()+count);

    for (int i = 0; i < b->next.size(); i++)
    {
        node = b->next[i];
        search(depth-1, node);
    }
}
*/

/**Engine::Node* Engine::Montecarlo(Node *node, int depth, int random)
{
    Node* node = node;
    srand(random);

    if (depth == 0)
        return node;

    return (Montecarlo(node->next[rand() % node->next.size()], depth-1, random));
}

void Engine::clearMemory(Node* node)
{
    if (node->next[0]->next.size() == 0)
        node->next.clear();
        

    else
    {
        for (int i = 0; i < node->next.size(); i++)
            clearMemory(node->next[i]);
    }

    //delete node;
}*/
