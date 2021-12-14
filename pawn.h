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

    Pawn(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
         char color);

    bool check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol);

    vector<pair<int, int>> legalMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);

    vector<pair<int, int>> captureMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);

    vector<pair<int, int>> avoidMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);

    vector<pair<int, int>> checkMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c);
};

#endif
