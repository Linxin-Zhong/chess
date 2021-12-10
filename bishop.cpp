#include "bishop.h"

Bishop::Bishop(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
               char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) :
        Piece(Wkingrow, Wkingcol, Bkingrow, Bkingcol, color, 9, boardmap) {}

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
                if (b[kingrow + i][tocol + i] != nullptr) {
                    return false;
                }
            }
            return check;
        } else {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (b[torow + i][kingcol + i] != nullptr) {
                    return false;
                }
            }
            return check;
        }
    } else {
        return false;
    }
}

vector<pair<int, int>> Bishop::legalMoves(int r, int c) {
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
            if (!(*boardmap)[newrow][newcol]) {
                temp = {newrow, newcol};
                listofLegalMoves.emplace_back(temp);
            } else if ((*boardmap)[newrow][newcol]->getColor() == this->color) {
                break;
            } else if ((*boardmap)[newrow][newcol]->getColor() != this->color) {
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

    bool kinginCheck = false;

    if (isCheck((*boardmap), color, kingrow, kingcol, &checkrow, &checkcol)) {
        kinginCheck = true;
    }

    if (kinginCheck) {
        vector<pair<int, int>> movesSavingKing;
        for (int i = 0; i < listofLegalMoves.size(); i++) {
            //check if making that move would eliminate the check on king
            vector<vector<shared_ptr<Piece>>> newboard;
            boardcopy2((*boardmap), newboard);
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

    return listofLegalMoves;
}

vector<pair<int, int>> Bishop::captureMoves(int r, int c) {
    vector<pair<int, int>> listofCaptureMoves;
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
            if (!(*boardmap)[newrow][newcol]) {
                continue;
            } else if ((*boardmap)[newrow][newcol]->getColor() == this->color) {
                break;
            } else if ((*boardmap)[newrow][newcol]->getColor() != this->color) {
                temp = {newrow, newcol};
                listofCaptureMoves.emplace_back(temp);
                break;
            }
            j++;
        }
    }
    return listofCaptureMoves;
}

vector<pair<int, int>> Bishop::avoidMoves(int r, int c) {
    vector<pair<int, int>> a;
    return a;
}

vector<pair<int, int>> Bishop::checkMoves(int r, int c) {
    vector<pair<int, int>> a;
    return a;
}
