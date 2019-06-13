#include "header.h"

#define N 9

Board::Board(vector<string> _board, vector<string> *_end) {
    for (string letter : _board) {
        board.emplace_back(letter);
    }
    end = _end;
    g = 0;
    h = calcH();
    f = g + h;
}

Board::~Board() {
    board.clear();
}

bool Board::operator==(Board *b) {
    bool equal = true;
    for (unsigned i = 0; i < board.size(); i++) {
        if (board[i] != b->board[i]) {
            equal = false;
            break;
        }
    }
    return equal;
}

void Board::updateF() {
    g++;
    h = calcH();
    f = g + h;
}

unsigned Board::getF() {
    return f;
}

unsigned Board::getG() {
    return g;
}

unsigned Board::getH() {
    return h;
}

vector<string> Board::getBoard() {
    return board;
}

vector<string> *Board::getEnd() {
    return end;
}

void Board::printBoard() {
    cout << " " << board[0] << " " << board[1] << " " << board[2] << endl;
    cout << board[3] << "  " << board[4] << "  " << board[5] << endl;
    cout << " " << board[6] << " " << board[7] << " " << board[8] << endl;
    cout << endl;
}

bool Board::checkCellEmpty(unsigned i) {
    return board[i] == "+";
}

void Board::setCell(int i, string s) {
    board[i] = s;
}

unsigned Board::calcH() {
    unsigned newH = 0;

    int moves[N][N] = {
            // Л
            {
                    0,
                    1,
                    2,
                    1,
                    1,
                    3,
                    2,
                    3,
                    2,
            },
            // Ф
            {
                    1,
                    0,
                    1,
                    2,
                    2,
                    2,
                    3,
                    4,
                    3,
            },
            //  Я
            {
                    2,
                    1,
                    0,
                    3,
                    1,
                    1,
                    2,
                    3,
                    2,
            },
            // А
            {
                    1,
                    2,
                    3,
                    0,
                    2,
                    4,
                    1,
                    2,
                    3,
            },
            // +
            {
                    1,
                    2,
                    1,
                    2,
                    0,
                    2,
                    1,
                    2,
                    1,
            },
            // И
            {
                    3,
                    2,
                    1,
                    4,
                    2,
                    0,
                    3,
                    2,
                    1,
            },
            // Н
            {
                    2,
                    3,
                    2,
                    1,
                    1,
                    3,
                    0,
                    1,
                    2,
            },
            // Д
            {
                    3,
                    4,
                    3,
                    2,
                    2,
                    2,
                    1,
                    0,
                    1,
            },
            // Р
            {
                    2,
                    3,
                    2,
                    3,
                    1,
                    1,
                    2,
                    1,
                    0,
            },
    };

    for (int i = 0; i < N; i++) {
        string s = end->at(i);

        int pos;
        for (pos = 0; pos < N; pos++) {
            if (s == board[pos]) {
                break;
            }
        }

        newH += moves[i][pos];
    }

    return newH;
}

bool checkEnd(Board *board) {
    for (unsigned i = 0; i < board->getBoard().size(); i++) {
        if (board->getBoard()[i] != board->getEnd()->at(i)) {
            return false;
        }
    }

    return true;
}

Board *formVertex(unsigned i, unsigned j, Board *b) {
    auto newBoard = new Board(*b);

    newBoard->setCell(i, b->getBoard()[j]);
    newBoard->setCell(j, b->getBoard()[i]);

    newBoard->previous = b;
    newBoard->updateF();

    return newBoard;
}

void addVertex(unsigned i, unsigned j, Board *b, vector<Board *> *open, vector<Board *> *close) {
    Board *board = formVertex(i, j, b);

    bool shouldOpen = true;
    for (Board *_b : *open) {
        if (*board == _b) {
            shouldOpen = false;
            break;
        }
    }
    for (Board *_b : *close) {
        if (*board == _b) {
            shouldOpen = false;
            break;
        }
    }
    if (shouldOpen) {
        open->emplace_back(board);
    }
}

void formVertexes(Board *b, vector<Board *> *open, vector<Board *> *close) {
    vector<string> board = b->getBoard();

    int empty;

    for (empty = 0; empty < board.size(); empty++) {
        if (b->checkCellEmpty(empty)) {
            break;
        }
    }

    switch (empty) {
        case 0:
            addVertex(0, 1, b, open, close);
            addVertex(0, 3, b, open, close);
            addVertex(0, 4, b, open, close);
            break;

        case 1:
            addVertex(1, 0, b, open, close);
            addVertex(1, 2, b, open, close);
            break;

        case 2:
            addVertex(2, 1, b, open, close);
            addVertex(2, 4, b, open, close);
            addVertex(2, 5, b, open, close);
            break;

        case 3:
            addVertex(3, 0, b, open, close);
            addVertex(3, 6, b, open, close);
            break;

        case 4:
            addVertex(4, 0, b, open, close);
            addVertex(4, 2, b, open, close);
            addVertex(4, 6, b, open, close);
            addVertex(4, 8, b, open, close);
            break;

        case 5:
            addVertex(5, 2, b, open, close);
            addVertex(5, 8, b, open, close);
            break;

        case 6:
            addVertex(6, 3, b, open, close);
            addVertex(6, 4, b, open, close);
            addVertex(6, 7, b, open, close);
            break;

        case 7:
            addVertex(7, 6, b, open, close);
            addVertex(7, 8, b, open, close);
            break;

        case 8:
            addVertex(8, 4, b, open, close);
            addVertex(8, 5, b, open, close);
            addVertex(8, 7, b, open, close);
            break;

        default:
            exit(1);
    }
}

int main() {
    vector<string> start, end;

    start = {
            "А",
            "Н",
            "Д",
            "Л",
            "+",
            "Р",
            "Ф",
            "Я",
            "И",
    };
    end = {
            "Л",
            "Ф",
            "Я",
            "А",
            "+",
            "И",
            "Н",
            "Д",
            "Р",
    };

    vector<Board *> open;
    vector<Board *> close;
    open.emplace_back(new Board(start, &end));

    unsigned iteration = 0;

    int maxOpen = 0;

    while (true) {
        Board *x = nullptr;

        unsigned index = 0;

        for (unsigned i = 0; i < open.size(); i++) {
            Board *b = open[i];

            if (checkEnd(b)) {
                x = b;
                index = i;
                break;
            }
            if (x == nullptr) {
                x = b;
                index = i;
                continue;
            }

            if (x->getF() > b->getF()) {
                index = i;
                x = b;
            }
        }

        iteration++;

        if (x != nullptr) {
            open.erase(open.begin() + index);

            close.emplace_back(x);
            // x->printBoard();

            if (checkEnd(x)) {
                break;
            }

            formVertexes(x, &open, &close);
            if (open.size() > maxOpen) {
                maxOpen = open.size();
            }

        } else {
            cout << "No open vertexes" << endl;
            return 1;
        }
    }

    cout << "Result:" << endl;

    Board *x = close[close.size() - 1];
    vector<Board *> result;

    while (x != nullptr) {
        result.emplace_back(x);
        x = x->previous;
    }

    for (int i = result.size() - 1; i > -1; i--) {
        result.at(i)->printBoard();
    }

    cout << result.size() - 1 << " steps" << endl;

    cout << iteration << " iterations" << endl;

    cout << "Max open size: " << maxOpen << endl;

    return 0;
}
