#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {

    bool haventMoved = true;

public:

    bool getHaventMoved();

    void setHaventMoved(bool b);

    Rook(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
         char color);

    bool check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol);

    vector<pair<int, int>> legalMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);

    vector<pair<int, int>> captureMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);

    vector<pair<int, int>> avoidMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);

    vector<pair<int, int>> checkMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);
};

#endif
