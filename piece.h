#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>
#include <memory>
#include <vector>
using namespace std;

class Board;

class Piece {
protected:
    vector<vector<shared_ptr<Piece>>> &boardmap;
    int value;  // determine the value of a piece
    char color;
public:

    Piece(char color, int value, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    virtual bool check(int torow, int tocol, int kingrow, int kingcol) = 0;
    virtual <pair<int, int> legalMove(int r, int c) = 0;
    virtual <pair<int, int> capture(int r, int c) = 0;
    virtual <pair<int, int> avoid(int r, int c) = 0;
    virtual <pair<int, int> checks(int r, int c) = 0;
    
//    virtual void move(char c, int i) = 0;
    virtual ~Piece() = default;

    char type(); //return what type of piece is that, one of: k, q, b, r, n, p
    friend class Board;
};

#endif
