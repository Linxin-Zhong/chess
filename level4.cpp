#include "level4.h"
#include <string>
#include <vector>
#include <algorithm>


int partition(vector<int> &points, vector<pair<pair<int, int>, pair<int, int>>> &move,
              int begin, int end) {
    int pivot = points[begin];
    pair<pair<int, int>, pair<int, int>> pivot2 = move[begin];
    int left = begin + 1;
    int right = end;
    while (true) {
        while (left < right && points[right] >= pivot)
            right--;
        while (left < right && points[left] < pivot)
            left++;
        if (left == right)
            break;
        swap(points[left], points[right]);
        swap(move[left], move[right]);
    }
    if (points[left] >= pivot)
        return begin;
    points[begin] = points[left];
    move[begin] = move[left];
    points[left] = pivot;
    move[left] = pivot2;
    return left;
}

void quickSort(vector<int> &points, vector<pair<pair<int, int>, pair<int, int>>> &move,
               int begin, int end) {
    if (begin >= end) return;
    int boundary = partition(points, move, begin, end);
    quickSort(points, move, begin, boundary - 1);
    quickSort(points, move, boundary + 1, end);
}


bool isCheck(vector<vector<shared_ptr<Piece>>> &b, char kingcolor, int kingrow,
             int kingcol, int *checkrow, int *checkcol) {
    *checkcol = -1;
    *checkrow = -1;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (b[r][c] && b[r][c]->check(b, r, c, kingrow, kingcol)) {
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

void boardcopy(vector<vector<shared_ptr<Piece>>> &a, vector<vector<shared_ptr<Piece>>> &b) {
    for (int i = 0; i < 8; i++) {
        vector<shared_ptr<Piece>> newrow;
        for (int j = 0; j < 8; j++) {
            newrow.emplace_back(a[i][j]);
        }
        b.emplace_back(newrow);
    }
}


bool isCheckMate(vector<vector<shared_ptr<Piece>>> &boardmap, char kingcolor, int kingrow, int kingcol, int checkrow,
                 int checkcol) {

    //1. king can escape directlly (one legal move)
    vector<pair<int, int>> escapeMoves = boardmap[kingrow][kingcol]->legalMoves(boardmap, kingrow, kingcol);
    if (escapeMoves.size() > 0) {
        return false;
    }

    //2. move of other pieces can eliminate the check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardmap[i][j] && boardmap[i][j]->getColor() == kingcolor) {
                vector<pair<int, int>> legalmoves = boardmap[i][j]->legalMoves(boardmap, i, j);
                if (legalmoves.size() > 0) {
                    for (size_t k = 0; k < legalmoves.size(); k++) {
                        vector<vector<shared_ptr<Piece>>> newboard;
                        boardcopy(boardmap, newboard);
                        newboard[legalmoves[k].first][legalmoves[k].second] = newboard[i][j];
                        newboard[i][j] = nullptr;
                        int checkrow2, checkcol2;
                        if (!isCheck(newboard, kingcolor, kingrow, kingcol, &checkrow2, &checkcol2)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}


using namespace std;

pair<pair<int, int>, pair<int, int>> Level4::generateMove(vector<vector<shared_ptr<Piece>>> &boardmap, string input) {



    //读取legalmoves，capmoves，checkmoves，avoidmoves
    vector<pair<pair<int, int>, pair<int, int>>> legalmoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((boardmap)[i][j] && (boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> legalmove = (boardmap)[i][j]->legalMoves(boardmap, i, j);
                for (size_t k = 0; k < legalmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {legalmove[k].first, legalmove[k].second}};
                    legalmoves.emplace_back(temp);
                }
            }
        }
    }

    if (legalmoves.size() <= 0) {
        return {{-1, -1},
                {-1, -1}};
    }

    vector<pair<pair<int, int>, pair<int, int>>> capmoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((boardmap)[i][j] && (boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> capmove = (boardmap)[i][j]->captureMoves(boardmap, i, j);
                for (size_t k = 0; k < capmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                j},
                                                                 {capmove[k].first, capmove[k].second}};
                    capmoves.emplace_back(temp);
                }
            }
        }
    }

    vector<pair<pair<int, int>, pair<int, int>>> checkmoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((boardmap)[i][j] && (boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> checkmove = (boardmap)[i][j]->checkMoves(boardmap, i, j);
                for (size_t k = 0; k < checkmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {checkmove[k].first, checkmove[k].second}};
                    checkmoves.emplace_back(temp);
                }
            }
        }
    }

    vector<pair<pair<int, int>, pair<int, int>>> avoidmoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((boardmap)[i][j] && (boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> avoidmove = (boardmap)[i][j]->avoidMoves(boardmap, i, j);
                for (size_t k = 0; k < avoidmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {avoidmove[k].first, avoidmove[k].second}};
                    avoidmoves.emplace_back(temp);
                }
            }
        }
    }

    vector<int> movepoints = {0};
    for (size_t i = 0; i < legalmoves.size(); i++) {
        if (i == 0) {
            continue;
        }
        movepoints.emplace_back(0);
    }

    //calculate points for each move
    for (int i = 0; i < legalmoves.size(); i++) {
        if (find(capmoves.begin(), capmoves.end(), legalmoves[i]) != capmoves.end()) {
            //inside capmoves
            movepoints[i] += (boardmap)[legalmoves[i].second.first][legalmoves[i].second.second]->getValue();
        }
        if (find(avoidmoves.begin(), avoidmoves.end(), legalmoves[i]) != avoidmoves.end()) {
            //inside avoidmoves
            movepoints[i] += (boardmap)[legalmoves[i].first.first][legalmoves[i].first.second]->getValue();
        }
        if (find(checkmoves.begin(), checkmoves.end(), legalmoves[i]) != checkmoves.end()) {
            //inside checkmoves
            movepoints[i] += 4;
        }

        int newmovefromrow = legalmoves[i].first.first;
        int newmovefromcol = legalmoves[i].first.second;
        int newmovetorow = legalmoves[i].second.first;
        int newmovetocol = legalmoves[i].second.second;
        vector<vector<shared_ptr<Piece>>> newboard;
        boardcopy((boardmap), newboard);
        newboard[newmovetorow][newmovetocol] = newboard[newmovefromrow][newmovefromcol];
        newboard[newmovefromrow][newmovefromcol] = nullptr;
        int checkrow, checkcol;

        //if moving this would win the game, assign highest priority
        int otherkingrow, otherkingcol;
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                if (((boardmap)[j][k]->type() == 'k' || (boardmap)[j][k]->type() == 'K')
                    && (boardmap)[j][k]->getColor() != *currentPlayer) {
                    otherkingrow = j;
                    otherkingcol = k;
                }
            }
        }

        char otherkingcolor = (*currentPlayer == 'W') ? ('B') : ('W');

        if (isCheck(newboard, otherkingcolor, otherkingrow, otherkingcol, &checkrow, &checkcol)) {
            if (isCheckMate(newboard, otherkingcolor, otherkingrow, otherkingcol, checkrow, checkcol)) {
                return {{newmovefromrow, newmovefromcol},
                        {newmovetorow,   newmovetocol}};
            }
        }


        //If moving would cause it being captured, minus points
        if (isCheck(newboard, *currentPlayer, newmovetorow, newmovetocol, &checkrow, &checkcol)) {
            movepoints[i] -= newboard[newmovetorow][newmovetocol]->getValue();
        }
    }
    quickSort(movepoints, legalmoves, 0, movepoints.size());
    int highestNumofMoves = 0;
    for (int ind = movepoints.size() - 2; ind >= 0; ind--) {
        if (movepoints[ind] == movepoints[movepoints.size() - 1]) {
            highestNumofMoves++;
        } else {
            break;
        }
    }

    srand(time(NULL));
    int index = (highestNumofMoves) ? rand() % highestNumofMoves : 0;
    int a = legalmoves.size() - index - 1;

    return legalmoves[legalmoves.size() - index - 1];

}
