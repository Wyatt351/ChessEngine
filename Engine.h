#ifndef ENGINE_H
#define ENGINE_H
#include <string>
#include <memory>
#include "Board.h"

class Engine
{
private:
    Board board;
    struct Node
    {
        vector<shared_ptr<Node>> next;
        Node* prev;
        shared_ptr<Node> best;
        Board nodeBoard;
        int mat = 0, mob = 0, center = 0, bestFrom = 0, bestDepth = 0;
        bool eval = false;

        Node()
        {
            this->prev = NULL;
            this->best = NULL;
        }

        Node(const Node* node)
        {
            this->next = node->next;
            this->prev = node->prev;
            this->best = node->best;
            this->nodeBoard = node->nodeBoard;
            this->mat = node->mat;
            this->mob = node->mob;
            this->center = node->center;
            this->bestFrom = node->bestFrom;
            this->bestDepth = node->bestDepth;
        }
        Node(const shared_ptr<Node> node)
        {
            this->next = node->next;
            this->prev = node->prev;
            this->best = node->best;
            this->nodeBoard = node->nodeBoard;
            this->mat = node->mat;
            this->mob = node->mob;
            this->center = node->center;
            this->bestFrom = node->bestFrom;
            this->bestDepth = node->bestDepth;
        }
    };
    shared_ptr<Node> head;
public:
    Engine();
    Engine(std::string);
    //~Engine();
    Board getBoard()
    { return board; }
    shared_ptr<Node> getHead()
    { return head; }
    bool movePieceNode(std::string, std::string, shared_ptr<Node>);
    bool movePiece(std::string, std::string);
    void displayBoard();
    void deleteBoards();
    void search(int, shared_ptr<Node>);
    void evaluate(int, int, shared_ptr<Node>);
    void playBest();
    Node* Montecarlo(shared_ptr<Node>, int, int);
    void clearMemory(shared_ptr<Node>);
};

#endif