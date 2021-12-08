#include "queen.h"

Queen::Queen(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap) : Piece(color, 9, boardmap) {}

bool Queen::check(int torow, int tocol, int kingrow, int kingcol) {
    if (tocol == kingcol) {
        bool check = true;
        if (torow < kingrow) {
            for (int i = torow + 1; i < kingrow; i++) {
                if (boardmap[i][tocol] != nullptr) {
                    check = false;
                    break;
                }
            }
            return check;
        } else {
            for (int i = kingrow + 1; i < torow; i++) {
                if (boardmap[i][tocol] != nullptr) {
                    check = false;
                    break;
                }
            }
            return check;
        }
    } else if (torow == kingrow) {
        bool check = true;
        if (tocol < kingcol) {
            for (int i = tocol + 1; i < kingcol; i++) {
                if (boardmap[torow][i] != nullptr) {
                    check = false;
                    break;
                }
            }
            return check;
        } else {
            for (int i = kingcol + 1; i < tocol; i++) {
                if (boardmap[torow][i] != nullptr) {
                    check = false;
                    break;
                }
            }
            return check;
        }
    } else if (abs(torow - kingrow) == abs(tocol - kingcol)) {
        bool check = true;
        if (kingrow > torow && kingcol > tocol) {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (boardmap[torow + i][tocol + i] != nullptr) {
                    return false;
                }
            }
            return check;
        } else if (kingrow < torow && kingcol < tocol) {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (boardmap[kingrow + i][kingcol + i] != nullptr) {
                    return false;
                }
            }
            return check;

        } else if (torow > kingrow && tocol < kingcol) {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (boardmap[kingrow + i][tocol + i] != nullptr) {
                    return false;
                }
            }
            return check;
        } else {
            for (int i = 1; i < abs(torow - kingrow); i++) {
                if (boardmap[torow + i][kingcol + i] != nullptr) {
                    return false;
                }
            }
            return check;
        }
    }
}

pair<int, int> Queen::legalMove(int r, int c) {
    /*vector<pair<int, int>> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1} };
    pair<int, int> temp = {-1, -1};
    
    for (int i = 0; i < 8; ++i) {
        j = 1;
        while (true) {
            int newrow = r + j * dir[i].first;
            int newcol = c + j * dir[i].second;
            if (newrow > 8 || newrow < 0 || newcol > 8 || newcol < 0) {
                break;
            }
            if (boardmap[newrow][newcol]->color == currentPlayer) {
                break;
            } else {
                temp = {newrow, newcol};
                return temp;
            }
            j++;
        }
    }
    return temp;*/

    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Queen::capture(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Queen::avoid(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Queen::checks(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}
