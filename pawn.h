#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(char color, std::vector<std::vector<std::shared_ptr<Piece>>> boardmap);

    bool check(int tocol, int torow, int kingcol, int kingrow);
};

#endif
