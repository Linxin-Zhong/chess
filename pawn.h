#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    bool check(int torow, int tocol, int kingrow, int kingcol);
    pair<char, int> legalMove(int r, int c);
    pair<char, int> capture(int r, int c);
    pair<char, int> avoid(int r, int c);
    pair<char, int> checks(int r, int c);
};

#endif
