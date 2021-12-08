#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    bool Enpassant = false; //刚走了第一步，两格步长
    bool haventmoved = true;
public:
    bool getHaventMoved();

    bool getEnpassant();

    void setHaventMoved(bool b);

    void setEnpassant(bool b);

    Pawn(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap);

    bool check(int torow, int tocol, int kingrow, int kingcol);

    vector<pair<int, int>> legalMoves(int r, int c);

    pair<int, int> capture(int r, int c);

    pair<int, int> avoid(int r, int c);

    pair<int, int> checks(int r, int c);
};

#endif
