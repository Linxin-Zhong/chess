#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:

    Knight(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    bool check(int torow, int tocol, int kingrow, int kingcol);
};

#endif