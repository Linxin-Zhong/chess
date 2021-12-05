#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>
#include <memory>
#include <vector>


class Board;

class Piece {
protected:
    std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap;
    int value;  // determine the value of a piece
    char color;
public:
    Piece(char color, int value, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    virtual bool check(int tocol, int torow, int kingcol, int kingrow) = 0;

//    virtual void move(char c, int i) = 0;
    virtual ~Piece() = default;

    char type(); //return what type of piece is that, one of: k, q, b, r, n, p
    friend class Board;
};

#endif
