#include "king.h"
#include "rook.h"

King::King(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) : Piece(color, 10,
                                                                                                      boardmap) {}

bool King::check(int torow, int tocol, int kingrow, int kingcol) {
    return false;
}


bool isCheck(vector<vector<shared_ptr<Piece>>> &b, char kingcolor, int kingrow,
             int kingcol, int *checkrow, int *checkcol) {
    *checkcol = -1;
    *checkrow = -1;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (b[r][c] && b[r][c]->check(r, c, kingrow, kingcol)) {
                if (b[r][c]->getColor() != kingcolor) {
                    *checkrow = r;
                    *checkcol = c;
                    return true;
                }
            }
        }
    }
    return false;
}

vector<pair<int, int>> King::legalMoves(int r, int c) {
    vector<pair<int, int>> listOfLegalMoves;
    //王车 里加haventmoved bool
    //左右有车，中间不能有其他棋子，王在王车易位过程中不能被check
    //只考虑同一row
    //R _ _ _ K -----> _ _ K R _
    //K _ _ R  ---> _ R K _

    //normal moves
    vector<pair<int, int>> directions = {{0,  1},
                                         {0,  -1},
                                         {1,  0},
                                         {-1, 0},
                                         {1,  1},
                                         {-1, 1},
                                         {1,  -1},
                                         {-1, -1}};
    for (int i = 0; i < 8; i++) {
        int newrow = r + directions[i].first;
        int newcol = c + directions[i].second;

        if (newrow < 8 && newrow >= 0 && newcol < 8 && newcol >= 0) {
            if ((!(*boardmap)[newrow][newcol]) || (*boardmap)[newrow][newcol]->getColor() != this->color) {
                int checkrow, checkcol;
                if (!isCheck((*boardmap), this->color, newrow, newcol, &checkrow, &checkcol)) {
                    pair<int, int> temp = {newrow, newcol};
                    listOfLegalMoves.emplace_back(temp);
                }
            }
        }
    }



    //castling moves
    if (this->color == 'W') {
        //white king castling
        if (this->haventMoved) {
            if ((c - 4) >= 0 && (c - 4) < 8 &&
                (*boardmap)[r][c - 4] && (*boardmap)[r][c - 4]->type() == 'R') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((*boardmap)[r][c - 4]);
                if (rook->getHaventMoved()) {
                    if ((!(*boardmap)[r][c - 3]) && (!(*boardmap)[r][c - 2]) && (!(*boardmap)[r][c - 1])) {
                        int checkrow, checkcol;
                        if ((!isCheck((*boardmap), 'W', r, c - 3, &checkrow, &checkcol))
                            && (!isCheck((*boardmap), 'W', r, c - 2, &checkrow, &checkcol))) {
                            pair<int, int> temp = {r, c - 2};
                            listOfLegalMoves.emplace_back(temp);
                        }
                    }
                }
            }

            if ((c + 3) >= 0 && (c + 3) < 8 &&
                (*boardmap)[r][c + 3] && (*boardmap)[r][c + 3]->type() == 'R') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((*boardmap)[r][c + 3]);
                if (rook->getHaventMoved()) {
                    if ((!(*boardmap)[r][c + 1]) && (!(*boardmap)[r][c + 2])) {
                        int checkrow, checkcol;
                        if ((!isCheck((*boardmap), 'W', r, c + 1, &checkrow, &checkcol))
                            && (!isCheck((*boardmap), 'W', r, c + 2, &checkrow, &checkcol))) {
                            pair<int, int> temp = {r, c + 2};
                            listOfLegalMoves.emplace_back(temp);
                        }
                    }
                }
            }
        }
    } else {
        //black king castling
        if (this->haventMoved) {
            if ((c - 4) >= 0 && (c - 4) < 8 &&
                (*boardmap)[r][c - 4] && (*boardmap)[r][c - 4]->type() == 'r') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((*boardmap)[r][c - 4]);
                if (rook->getHaventMoved()) {
                    if ((!(*boardmap)[r][c - 3]) && (!(*boardmap)[r][c - 2]) && (!(*boardmap)[r][c - 1])) {
                        int checkrow, checkcol;
                        if ((!isCheck((*boardmap), 'B', r, c - 3, &checkrow, &checkcol))
                            && (!isCheck((*boardmap), 'B', r, c - 2, &checkrow, &checkcol))) {
                            pair<int, int> temp = {r, c - 2};
                            listOfLegalMoves.emplace_back(temp);
                        }
                    }
                }
            }

            if ((c + 3) >= 0 && (c + 3) < 8 &&
                (*boardmap)[r][c + 3] && (*boardmap)[r][c + 3]->type() == 'r') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((*boardmap)[r][c + 3]);
                if (rook->getHaventMoved()) {
                    if ((!(*boardmap)[r][c + 1]) && (!(*boardmap)[r][c + 2])) {
                        int checkrow, checkcol;
                        if ((!isCheck((*boardmap), 'B', r, c + 1, &checkrow, &checkcol))
                            && (!isCheck((*boardmap), 'B', r, c + 2, &checkrow, &checkcol))) {
                            pair<int, int> temp = {r, c + 2};
                            listOfLegalMoves.emplace_back(temp);
                        }
                    }
                }
            }
        }
    }

    return listOfLegalMoves;
}

pair<int, int> King::capture(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> King::avoid(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> King::checks(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

bool King::getHaventMoved() {
    return haventMoved;
}

void King::setHaventMoved(bool b) {
    haventMoved = b;
}