#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
    void move(char c, int i);

    Knight(char color);
};

#endif
