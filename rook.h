#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:

    Rook(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    bool check(int tocol, int torow, int kingcol, int kingrow);
};

#endif