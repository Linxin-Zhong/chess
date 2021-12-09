#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include "piece.h"
using namespace std;

class Board;

class Strategy {
protected:
    int *Wpiececount;
    int *Bpiececount;
    shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap;
public:
    virtual pair<int, int> generateMove(string input) = 0;

    Strategy(int *Wpiececount, int *BPiececount, shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) : Wpiececount{
            Wpiececount}, Bpiececount{Bpiececount}, boardmap(boardmap) {};
};


#endif
