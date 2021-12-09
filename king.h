#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {

    bool haventMoved = true;

public:

    bool getHaventMoved();

    void setHaventMoved(bool b);

    King(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap);

    bool check(int torow, int tocol, int kingrow, int kingcol);

    vector<pair<int, int>> legalMoves(int r, int c);

    pair<int, int> capture(int r, int c);

    pair<int, int> avoid(int r, int c);

    pair<int, int> checks(int r, int c);
};

#endif
