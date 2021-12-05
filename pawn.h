#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    void move(char c, int i);

    Pawn(char color);
};

#endif
