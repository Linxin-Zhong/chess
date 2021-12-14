#ifndef LEVEL1_H
#define LEVEL1_H

#include "strategy.h"
using namespace std;

class Level1 : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>>
    generateMove(vector<vector<shared_ptr<Piece>>> &boardmap, string input) override;

    Level1(char *currentPlayer, int *Wpiececount, int *Bpiececount) :
            Strategy(currentPlayer, Wpiececount, Bpiececount) {};


};

#endif //LEVEL1_H
