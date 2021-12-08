#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:

    Rook(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap);

    bool check(int torow, int tocol, int kingrow, int kingcol);

    pair<int, int> legalMove(int r, int c);

    pair<int, int> capture(int r, int c);

    pair<int, int> avoid(int r, int c);

    pair<int, int> checks(int r, int c);
};

#endif
