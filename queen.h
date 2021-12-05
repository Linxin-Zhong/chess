#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    bool check(int tocol, int torow, int kingcol, int kingrow);
};

#endif
