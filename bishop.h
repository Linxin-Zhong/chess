#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:

    Bishop(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    bool check(int tocol, int torow, int kingcol, int kingrow);
};

#endif
