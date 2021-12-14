#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include "piece.h"
using namespace std;

class Board;

class Strategy {
protected:
    char *currentPlayer;
    int *Wpiececount;
    int *Bpiececount;
    shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap;
public:
    virtual pair<pair<int, int>, pair<int, int>> generateMove(string input) = 0;

    vector<pair<pair<int, int>, pair<int, int>>> findIntersection(vector<pair<pair<int, int>, pair<int, int>>> v1,
                                                                  vector<pair<pair<int, int>, pair<int, int>>> v2);

    Strategy(char *currentPlayer, int *Wpiececount, int *Bpiececount,
             shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) : currentPlayer{currentPlayer},
                                                                       Wpiececount{Wpiececount},
                                                                       Bpiececount{Bpiececount}, boardmap(boardmap) {};
};

#endif
