#include "king.h"
#include "rook.h"

King::King(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
           char color) :
        Piece(Wkingrow, Wkingcol, Bkingrow, Bkingcol, color, 100) {}

bool King::check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol) {
    if ((abs(torow - kingrow) == 1 || abs(torow - kingrow) == 0) &&
        (abs(tocol - kingcol) == 1 || abs(tocol - kingcol) == 0)) {
        return true;
    }
    return false;
}


vector<pair<int, int>> King::legalMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listOfLegalMoves;

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
            if ((!(boardmap)[newrow][newcol]) || (boardmap)[newrow][newcol]->getColor() != this->color) {
                int checkrow, checkcol;
                vector<vector<shared_ptr<Piece>>> newboard;
                boardcopy2((boardmap), newboard);
                newboard[newrow][newcol] = newboard[r][c];
                newboard[r][c] = nullptr;
                if (!isCheck(newboard, this->color, newrow, newcol, &checkrow, &checkcol)) {
                    pair<int, int> temp = {newrow, newcol};
                    listOfLegalMoves.emplace_back(temp);
                }
            }
        }
    }


    //王车 里加haventmoved bool
    //左右有车，中间不能有其他棋子，王在王车易位过程中不能被check
    //只考虑同一row
    //R _ _ _ K -----> _ _ K R _
    //K _ _ R  ---> _ R K _

    //castling moves
    if (this->color == 'W') {
        //white king castling
        if (this->haventMoved) {
            if ((c - 4) >= 0 && (c - 4) < 8 &&
                (boardmap)[r][c - 4] && (boardmap)[r][c - 4]->type() == 'R') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((boardmap)[r][c - 4]);
                if (rook->getHaventMoved()) {
                    if ((!(boardmap)[r][c - 3]) && (!(boardmap)[r][c - 2]) && (!(boardmap)[r][c - 1])) {
                        int checkrow, checkcol;
                        if ((!isCheck((boardmap), 'W', r, c - 2, &checkrow, &checkcol))
                            && (!isCheck((boardmap), 'W', r, c - 1, &checkrow, &checkcol))
                            && (!isCheck((boardmap), 'W', r, c, &checkrow, &checkcol))) {
                            pair<int, int> temp = {r, c - 2};
                            listOfLegalMoves.emplace_back(temp);
                        }
                    }
                }
            }

            if ((c + 3) >= 0 && (c + 3) < 8 &&
                (boardmap)[r][c + 3] && (boardmap)[r][c + 3]->type() == 'R') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((boardmap)[r][c + 3]);
                if (rook->getHaventMoved()) {
                    if ((!(boardmap)[r][c + 1]) && (!(boardmap)[r][c + 2])) {
                        int checkrow, checkcol;
                        if (!isCheck((boardmap), 'W', r, c, &checkrow, &checkcol)
                            && (!isCheck((boardmap), 'W', r, c + 1, &checkrow, &checkcol))
                            && (!isCheck((boardmap), 'W', r, c + 2, &checkrow, &checkcol))) {
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
                (boardmap)[r][c - 4] && (boardmap)[r][c - 4]->type() == 'r') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((boardmap)[r][c - 4]);
                if (rook->getHaventMoved()) {
                    if ((!(boardmap)[r][c - 3]) && (!(boardmap)[r][c - 2]) && (!(boardmap)[r][c - 1])) {
                        int checkrow, checkcol;
                        if ((!isCheck((boardmap), 'B', r, c - 2, &checkrow, &checkcol))
                            && (!isCheck((boardmap), 'B', r, c - 1, &checkrow, &checkcol))
                            && (!isCheck((boardmap), 'B', r, c, &checkrow, &checkcol))) {
                            pair<int, int> temp = {r, c - 2};
                            listOfLegalMoves.emplace_back(temp);
                        }
                    }
                }
            }

            if ((c + 3) >= 0 && (c + 3) < 8 &&
                (boardmap)[r][c + 3] && (boardmap)[r][c + 3]->type() == 'r') {
                shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>((boardmap)[r][c + 3]);
                if (rook->getHaventMoved()) {
                    if ((!(boardmap)[r][c + 1]) && (!(boardmap)[r][c + 2])) {
                        int checkrow, checkcol;
                        if ((!isCheck((boardmap), 'B', r, c + 1, &checkrow, &checkcol))
                            && (!isCheck((boardmap), 'B', r, c + 2, &checkrow, &checkcol))
                            && (!isCheck((boardmap), 'B', r, c, &checkrow, &checkcol))) {
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

vector<pair<int, int>> King::captureMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofCaptureMoves;
    vector<pair<int, int>> legalMoves = this->legalMoves(boardmap, r, c);
    for (size_t i = 0; i < legalMoves.size(); i++) {
        if ((boardmap)[legalMoves[i].first][legalMoves[i].second]) {
            listofCaptureMoves.emplace_back(legalMoves[i]);
        }
    }
    return listofCaptureMoves;
}


vector<pair<int, int>> King::avoidMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
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

vector<pair<int, int>> King::checkMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    //no checkmoves
    vector<pair<int, int>> a;
    return a;
}

bool King::getHaventMoved() {
    return haventMoved;
}

void King::setHaventMoved(bool b) {
    haventMoved = b;
}
