#include "rook.h"
#include "king.h"

Rook::Rook(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) : Piece(color, 5,
                                                                                                      boardmap) {}

bool Rook::check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol) {
    if (tocol == kingcol) {
        bool check = true;
        if (torow < kingrow) {
            for (int i = torow + 1; i < kingrow; i++) {
                if (b[i][tocol] != nullptr) {
                    check = false;
                    break;
                }
            }
            return check;
        } else {
            for (int i = kingrow + 1; i < torow; i++) {
                if (b[i][tocol] != nullptr) {
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
                if (b[torow][i] != nullptr) {
                    check = false;
                    break;
                }
            }
            return check;
        } else {
            for (int i = kingcol + 1; i < tocol; i++) {
                if (b[torow][i] != nullptr) {
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

vector<pair<int, int>> Rook::legalMoves(int r, int c) {

    //normal moves
    vector<pair<int, int>> listofLegalMoves;
    vector<pair<int, int>> dir = {{1,  0},
                                  {0,  1},
                                  {-1, 0},
                                  {0,  -1}};
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

    //王车 里加haventmoved bool
    //左右有车，中间不能有其他棋子，王在王车易位过程中不能被check
    //只考虑同一row
    //R _ _ _ K -----> _ _ K R _
    //K _ _ R  ---> _ R K _

    if (this->color == 'W') {
        if ((c + 4) >= 0 && (c + 4) < 8) {
            if (this->haventMoved && (*boardmap)[r][c + 4] && (*boardmap)[r][c + 4]->type() == 'K') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((*boardmap)[r][c + 4]);
                if (king->getHaventMoved() && !(*boardmap)[r][c + 1]
                    && !(*boardmap)[r][c + 2] && !(*boardmap)[r][c + 3]) {
                    int checkrow, checkcol;
                    if (!isCheck(*boardmap, 'W', r, c + 4, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'W', r, c + 3, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'W', r, c + 2, &checkrow, &checkcol)) {
                        temp = {r, c + 2};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
        }

        if ((c - 3) >= 0 && (c - 3) < 8) {
            if (this->haventMoved && (*boardmap)[r][c - 3] && (*boardmap)[r][c - 3]->type() == 'K') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((*boardmap)[r][c - 3]);
                if (king->getHaventMoved() && !(*boardmap)[r][c - 1] && !(*boardmap)[r][c - 2]) {
                    int checkrow, checkcol;
                    if (!isCheck(*boardmap, 'W', r, c - 1, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'W', r, c - 2, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'W', r, c - 3, &checkrow, &checkcol)) {
                        temp = {r, c - 1};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
        }
    } else {
        if ((c + 4) >= 0 && (c + 4) < 8) {
            if (this->haventMoved && (*boardmap)[r][c + 4] && (*boardmap)[r][c + 4]->type() == 'k') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((*boardmap)[r][c + 4]);
                if (king->getHaventMoved() && !(*boardmap)[r][c + 1]
                    && !(*boardmap)[r][c + 2] && !(*boardmap)[r][c + 3]) {
                    int checkrow, checkcol;
                    if (!isCheck(*boardmap, 'B', r, c + 4, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'B', r, c + 3, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'B', r, c + 2, &checkrow, &checkcol)) {
                        temp = {r, c + 2};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
        }

        if ((c - 3) >= 0 && (c - 3) < 8) {
            if (this->haventMoved && (*boardmap)[r][c - 3] && (*boardmap)[r][c - 3]->type() == 'k') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((*boardmap)[r][c - 3]);
                if (king->getHaventMoved() && !(*boardmap)[r][c - 1] && !(*boardmap)[r][c - 2]) {
                    int checkrow, checkcol;
                    if (!isCheck(*boardmap, 'B', r, c - 1, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'B', r, c - 2, &checkrow, &checkcol)
                        && !isCheck(*boardmap, 'B', r, c - 3, &checkrow, &checkcol)) {
                        temp = {r, c - 1};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
        }
    }

    return listofLegalMoves;
}

bool Rook::getHaventMoved() {
    return haventMoved;
}

void Rook::setHaventMoved(bool b) {
    haventMoved = b;
}

vector<pair<int, int>> Rook::captureMoves(int r, int c) {
    vector<pair<int, int>> a;
    return a;
}

vector<pair<int, int>> Rook::avoidMoves(int r, int c) {
    vector<pair<int, int>> a;
    return a;
}

vector<pair<int, int>> Rook::checkMoves(int r, int c) {
    vector<pair<int, int>> a;
    return a;
}
