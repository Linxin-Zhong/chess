#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap);

    bool check(int torow, int tocol, int kingrow, int kingcol);
    pair<int, int> legalMove(int r, int c);
    pair<int, int> capture(int r, int c);
    pair<int, int> avoid(int r, int c);
    pair<int, int> checks(int r, int c);
};

#endif
