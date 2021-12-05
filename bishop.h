#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    void move(char c, int i);

    Bishop(char color);
};

#endif
