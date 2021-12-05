#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    void move(char c, int i);

    Queen(char color);
};

#endif
