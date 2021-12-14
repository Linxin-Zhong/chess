#ifndef LEVEL4_H
#define LEVEL4_H


#include "strategy.h"

class Level4 : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>> generateMove(string input) override;

    Level4(char *currentPlayer, int *Wpiececount, int *Bpiececount,
           shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) :
            Strategy(currentPlayer, Wpiececount, Bpiececount, boardmap) {};
};


#endif
