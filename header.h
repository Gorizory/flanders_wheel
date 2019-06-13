#ifndef FLANDER_WHEEL_HEADER_H
#define FLANDER_WHEEL_HEADER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>

using namespace std;

class Board {
private:
    vector<string> board;
    vector<string>* end;
    unsigned g;
    unsigned h;
    unsigned f;

public:

    Board* previous = nullptr;

    Board(vector<string>, vector<string>*);

    ~Board();

    bool operator==(Board*);

    vector<string> getBoard();

    vector<string>* getEnd();

    void updateF();

    unsigned getG();

    unsigned getF();

    unsigned getH();

    void printBoard();

    bool checkCellEmpty(unsigned);

    void setCell(int, string);

    unsigned calcH();
};

Board* formVertex(unsigned, unsigned, Board*);

void addVertex(unsigned, unsigned, Board*, vector<Board*>*, vector<Board*>*);

void formVertexes(Board*, vector<Board*>*, vector<Board*>*);

#endif
