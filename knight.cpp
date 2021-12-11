#include "knight.h"
#include <iostream>

using namespace std;;

Knight::Knight(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
               char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) :
        Piece(Wkingrow, Wkingcol, Bkingrow, Bkingcol, color, 9, boardmap) {}


bool Knight::check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol) {
    int w = abs(kingcol - tocol);
    int h = abs(kingrow - torow);
    if ((w == 2 && h == 1) || (w == 1 && h == 2)) {
        return true;
    } else {
        return false;
    }
}


vector<pair<int, int>> Knight::legalMoves(int r, int c) {
    vector<pair<int, int>> listOfLegalMoves;
    vector<pair<int, int>> dir = {{1,  2},
                                  {1,  -2},
                                  {-1, 2},
                                  {-1, -2},
                                  {2,  1},
                                  {2,  -1},
                                  {-2, 1},
                                  {-2, -1}};
    for (int i = 0; i < 8; i++) {
        int newrow = r + dir[i].first;
        int newcol = c + dir[i].second;
        if ((newrow >= 0 && newrow < 8 && newcol >= 0 && newcol < 8) &&
            (!(*boardmap)[newrow][newcol] || ((*boardmap)[newrow][newcol]->getColor() != this->color))) {
            pair<int, int> temp = {newrow, newcol};
            listOfLegalMoves.emplace_back(temp);
        } else {
            continue;
        }
    }

    int kingrow, kingcol;
    if (color == 'W') {
        kingrow = *Wkingrow;
        kingcol = *Wkingcol;
    } else {
        kingrow = *Bkingrow;
        kingcol = *Bkingcol;
    }

    int checkcol, checkrow;

    vector<pair<int, int>> movesSavingKing;
    for (int i = 0; i < listOfLegalMoves.size(); i++) {
        //check if making that move would eliminate the check on king
        vector<vector<shared_ptr<Piece>>> newboard;
        boardcopy2((*boardmap), newboard);
        int fromrow, fromcol, torow, tocol;
        fromrow = r;
        fromcol = c;
        torow = listOfLegalMoves[i].first;
        tocol = listOfLegalMoves[i].second;
        newboard[torow][tocol] = newboard[fromrow][fromcol];
        newboard[fromrow][fromcol] = nullptr;
        if (!isCheck(newboard, color, kingrow, kingcol, &checkrow, &checkcol)) {
            movesSavingKing.emplace_back(listOfLegalMoves[i]);
        }
    }
    return movesSavingKing;
}

vector<pair<int, int>> Knight::captureMoves(int r, int c) {
    vector<pair<int, int>> listofCaptureMoves;
    vector<pair<int, int>> legalMoves = this->legalMoves(r, c);
    for (int i = 0; i < legalMoves.size(); i++) {
        if ((*boardmap)[legalMoves[i].first][legalMoves[i].second]) {
            listofCaptureMoves.emplace_back(legalMoves[i]);
        }
    }
    return listofCaptureMoves;
}

vector<pair<int, int>> Knight::avoidMoves(int r, int c) {
    vector<pair<int, int>> listOfAvoidMoves;
    int checkrow, checkcol;
    if (!(*boardmap)[r][c]->isCheck((*boardmap), this->color, r, c, &checkrow, &checkcol)) {
        return listOfAvoidMoves;
    }

    vector<pair<int, int>> legalmoves = (*boardmap)[r][c]->legalMoves(r, c);
    for (int i = 0; i < legalmoves.size(); i++) {
        int newrow = legalmoves[i].first;
        int newcol = legalmoves[i].second;
        vector<vector<shared_ptr<Piece>>> boardAfterMove;
        boardcopy2(*boardmap, boardAfterMove);
        boardAfterMove[newrow][newcol] = boardAfterMove[r][c];
        boardAfterMove[r][c] = nullptr;
        int checkrow, checkcol;
        if (!isCheck(boardAfterMove, color, newrow, newcol, &checkrow, &checkcol)) {
            pair<int, int> temp = {newrow, newcol};
            listOfAvoidMoves.emplace_back(temp);
        }
    }
    return listOfAvoidMoves;
}

vector<pair<int, int>> Knight::checkMoves(int r, int c) {
    vector<pair<int, int>> listofchecks;
    vector<pair<int, int>> legalmoves = (*boardmap)[r][c]->legalMoves(r, c);

    for (int i = 0; i < legalmoves.size(); i++) {
        int newrow = legalmoves[i].first;
        int newcol = legalmoves[i].second;
        if ((*boardmap)[newrow][newcol] && (*boardmap)[newrow][newcol]->getColor() != color &&
            ((*boardmap)[newrow][newcol]->type() == 'k' || (*boardmap)[newrow][newcol]->type() == 'K')) {
            pair<int, int> temp = {newrow, newcol};
            listofchecks.emplace_back(temp);
        }
    }
    return listofchecks;
}