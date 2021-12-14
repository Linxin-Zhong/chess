#include "bishop.h"

Bishop::Bishop(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
               char color) :
        Piece(Wkingrow, Wkingcol, Bkingrow, Bkingcol, color, 3) {}

bool Bishop::check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol) {
    if (abs(torow - kingrow) == abs(tocol - kingcol)) {
        bool check = true;
        if (kingrow > torow && kingcol > tocol) {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (b[torow + i][tocol + i] != nullptr) {
                    return false;
                }
            }
            return check;
        } else if (kingrow < torow && kingcol < tocol) {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (b[kingrow + i][kingcol + i] != nullptr) {
                    return false;
                }
            }
            return check;
        } else if (torow > kingrow && tocol < kingcol) {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (b[kingrow + i][kingcol - i] != nullptr) {
                    return false;
                }
            }
            return check;
        } else {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (b[torow + i][tocol - i] != nullptr) {
                    return false;
                }
            }
            return check;
        }
    } else {
        return false;
    }
}

vector<pair<int, int>> Bishop::legalMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofLegalMoves;
    vector<pair<int, int>> dir = {{1,  1},
                                  {1,  -1},
                                  {-1, 1},
                                  {-1, -1}};
    pair<int, int> temp;
    for (int i = 0; i < 4; ++i) {
        int j = 1;
        while (true) {
            int newrow = r + j * dir[i].first;
            int newcol = c + j * dir[i].second;
            if (newrow >= 8 || newrow < 0 || newcol >= 8 || newcol < 0) {
                break;
            }
            if (!(boardmap)[newrow][newcol]) {
                temp = {newrow, newcol};
                listofLegalMoves.emplace_back(temp);
            } else if ((boardmap)[newrow][newcol]->getColor() == this->color) {
                break;
            } else if ((boardmap)[newrow][newcol]->getColor() != this->color) {
                temp = {newrow, newcol};
                listofLegalMoves.emplace_back(temp);
                break;
            }
            j++;
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
    for (size_t i = 0; i < listofLegalMoves.size(); i++) {
        //check if making that move would eliminate the check on king
        vector<vector<shared_ptr<Piece>>> newboard;
        boardcopy2((boardmap), newboard);
        int fromrow, fromcol, torow, tocol;
        fromrow = r;
        fromcol = c;
        torow = listofLegalMoves[i].first;
        tocol = listofLegalMoves[i].second;
        newboard[torow][tocol] = newboard[fromrow][fromcol];
        newboard[fromrow][fromcol] = nullptr;
        if (!isCheck(newboard, color, kingrow, kingcol, &checkrow, &checkcol)) {
            movesSavingKing.emplace_back(listofLegalMoves[i]);
        }
    }
    return movesSavingKing;
}

vector<pair<int, int>> Bishop::captureMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofCaptureMoves;
    vector<pair<int, int>> legalMoves = this->legalMoves(boardmap, r, c);
    for (size_t i = 0; i < legalMoves.size(); i++) {
        if ((boardmap)[legalMoves[i].first][legalMoves[i].second]) {
            listofCaptureMoves.emplace_back(legalMoves[i]);
        }
    }
    return listofCaptureMoves;
}

vector<pair<int, int>> Bishop::avoidMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listOfAvoidMoves;
    // check if the current piece is under attack
    int checkrow, checkcol;
    if (!(boardmap)[r][c]->isCheck((boardmap), this->color, r, c, &checkrow, &checkcol)) {
        return listOfAvoidMoves;
    }

    vector<pair<int, int>> legalmoves = (boardmap)[r][c]->legalMoves(boardmap, r, c);
    for (size_t i = 0; i < legalmoves.size(); i++) {
        int newrow = legalmoves[i].first;
        int newcol = legalmoves[i].second;
        vector<vector<shared_ptr<Piece>>> boardAfterMove;
        boardcopy2(boardmap, boardAfterMove);
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

vector<pair<int, int>> Bishop::checkMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofchecks;
    vector<pair<int, int>> legalmoves = (boardmap)[r][c]->legalMoves(boardmap, r, c);

    for (size_t i = 0; i < legalmoves.size(); i++) {
        int newrow = legalmoves[i].first;
        int newcol = legalmoves[i].second;
        if ((boardmap)[newrow][newcol] && (boardmap)[newrow][newcol]->getColor() != color &&
            ((boardmap)[newrow][newcol]->type() == 'k' || (boardmap)[newrow][newcol]->type() == 'K')) {
            pair<int, int> temp = {newrow, newcol};
            listofchecks.emplace_back(temp);
        }
    }
    return listofchecks;
}
