#ifndef LEVEL1_H
#define LEVEL1_H

#include "strategy.h"
using namespace std;

class Level1 : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>> generateMove(string input) override;

    Level1(char *currentPlayer, int *Wpiececount, int *Bpiececount,
           shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) :
            Strategy(currentPlayer, Wpiececount, Bpiececount, boardmap) {};
};

#endif //LEVEL1_H
