#include "rook.h"
#include "king.h"
#include "board.h"

Rook::Rook(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
           char color) :
        Piece(Wkingrow, Wkingcol, Bkingrow, Bkingcol, color, 5) {}

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

vector<pair<int, int>> Rook::legalMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {


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

    //王车 里加haventmoved bool
    //左右有车，中间不能有其他棋子，王在王车易位过程中不能被check
    //只考虑同一row
    //R _ _ _ K -----> _ _ K R _
    //K _ _ R  ---> _ R K _

    if (this->color == 'W') {
        if ((c + 4) >= 0 && (c + 4) < 8) {
            if (this->haventMoved && (boardmap)[r][c + 4] && (boardmap)[r][c + 4]->type() == 'K') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((boardmap)[r][c + 4]);
                if (king->getHaventMoved() && !(boardmap)[r][c + 1]
                    && !(boardmap)[r][c + 2] && !(boardmap)[r][c + 3]) {
                    int checkrow, checkcol;
                    if (!isCheck(boardmap, 'W', r, c + 4, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'W', r, c + 3, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'W', r, c + 2, &checkrow, &checkcol)) {
                        temp = {r, c + 2};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
        }

        if ((c - 3) >= 0 && (c - 3) < 8) {
            if (this->haventMoved && (boardmap)[r][c - 3] && (boardmap)[r][c - 3]->type() == 'K') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((boardmap)[r][c - 3]);
                if (king->getHaventMoved() && !(boardmap)[r][c - 1] && !(boardmap)[r][c - 2]) {
                    int checkrow, checkcol;
                    if (!isCheck(boardmap, 'W', r, c - 1, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'W', r, c - 2, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'W', r, c - 3, &checkrow, &checkcol)) {
                        temp = {r, c - 1};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
        }
    } else {
        if ((c + 4) >= 0 && (c + 4) < 8) {
            if (this->haventMoved && (boardmap)[r][c + 4] && (boardmap)[r][c + 4]->type() == 'k') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((boardmap)[r][c + 4]);
                if (king->getHaventMoved() && !(boardmap)[r][c + 1]
                    && !(boardmap)[r][c + 2] && !(boardmap)[r][c + 3]) {
                    int checkrow, checkcol;
                    if (!isCheck(boardmap, 'B', r, c + 4, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'B', r, c + 3, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'B', r, c + 2, &checkrow, &checkcol)) {
                        temp = {r, c + 2};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
        }

        if ((c - 3) >= 0 && (c - 3) < 8) {
            if (this->haventMoved && (boardmap)[r][c - 3] && (boardmap)[r][c - 3]->type() == 'k') {
                shared_ptr<King> king = dynamic_pointer_cast<King>((boardmap)[r][c - 3]);
                if (king->getHaventMoved() && !(boardmap)[r][c - 1] && !(boardmap)[r][c - 2]) {
                    int checkrow, checkcol;
                    if (!isCheck(boardmap, 'B', r, c - 1, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'B', r, c - 2, &checkrow, &checkcol)
                        && !isCheck(boardmap, 'B', r, c - 3, &checkrow, &checkcol)) {
                        temp = {r, c - 1};
                        listofLegalMoves.emplace_back(temp);
                    }
                }
            }
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

bool Rook::getHaventMoved() {
    return haventMoved;
}

void Rook::setHaventMoved(bool b) {
    haventMoved = b;
}

vector<pair<int, int>> Rook::captureMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofCaptureMoves;
    vector<pair<int, int>> legalMoves = this->legalMoves(boardmap, r, c);
    for (size_t i = 0; i < legalMoves.size(); i++) {
        if ((boardmap)[legalMoves[i].first][legalMoves[i].second]) {
            listofCaptureMoves.emplace_back(legalMoves[i]);
        }
    }
    return listofCaptureMoves;
}

vector<pair<int, int>> Rook::avoidMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
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

vector<pair<int, int>> Rook::checkMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
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

