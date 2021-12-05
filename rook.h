#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    void move(char c, int i);

    Rook(char color);
};

#endif