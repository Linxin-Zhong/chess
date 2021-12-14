#ifndef LEVEL4_H
#define LEVEL4_H


#include "strategy.h"

class Level4 : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>>
    generateMove(vector<vector<shared_ptr<Piece>>> &boardmap, string input) override;

    Level4(char *currentPlayer, int *Wpiececount, int *Bpiececount) :
            Strategy(currentPlayer, Wpiececount, Bpiececount) {};


};


#endif
