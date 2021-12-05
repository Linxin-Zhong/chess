#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    void move(char c, int i);

    King(char color);
};

#endif
