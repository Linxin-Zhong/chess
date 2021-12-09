#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:

    Knight(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap);

    bool check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol);

    vector<pair<int, int>> legalMoves(int r, int c);
    vector<pair<int, int>> captureMoves(int r, int c);
    vector<pair<int, int>> avoidMoves(int r, int c);
    vector<pair<int, int>> checkMoves(int r, int c);
};

#endif
