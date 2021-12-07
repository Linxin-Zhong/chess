#include "rook.h"

Rook::Rook(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap) : Piece(color, 5, boardmap) {}

bool Rook::check(int torow, int tocol, int kingrow, int kingcol) {
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

    } else {
        return false;
    }
}

pair<int, int> legalMove(int r, int c) {
    vector<pair<int, int>> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    pair<int, int> temp = {-1, -1};
    for (int i = 0; i < 4; ++i) {
        if (r + dir[i].first > 8 || r + dir[i].first < 0 || c + dir[i].second > 8 || c + dir[i].second < 0) {
            continue;
        }
        if (boardmap[r + dir[i].first][c + dir[i].second]->color == currentPlayer) {
            continue;
        } else {
            temp = {r + dir[i].first, c + dir[i].second};
            return temp;
        }
    }
    return temp;
}

<pair<int, int> capture(int r, int c) {
}
<pair<int, int> avoid(int r, int c) {
}
<pair<int, int> checks(int r, int c) {
}
