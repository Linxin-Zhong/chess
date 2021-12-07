#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:

    Rook(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap);

    bool check(int torow, int tocol, int kingrow, int kingcol);
    vector<pair<char, int>> legalMove();
    vector<pair<char, int>> capture();
    vector<pair<char, int>> avoid();
    vector<pair<char, int>> checks();
};

#endif
