#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:

    King(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    bool check(int tocol, int torow, int kingcol, int kingrow);
};

#endif
