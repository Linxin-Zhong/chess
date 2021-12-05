#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>
#include <memory>


class Board;

class Piece {
protected:
//    std::shared_ptr<Board> b;
    int value;  // determine the value of a piece
    char color;
public:
    Piece(char color, int value);

//    virtual void move(char c, int i) = 0;
    virtual ~Piece() = default;

    char type(); //return what type of piece is that, one of: k, q, b, r, n, p
    friend class Board;
};

#endif
