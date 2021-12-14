#ifndef LEVEL3_H
#define LEVEL3_H


#include "strategy.h"

class Level3 : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>>
    generateMove(vector<vector<shared_ptr<Piece>>> &boardmap, string input) override;

    Level3(char *currentPlayer, int *Wpiececount, int *Bpiececount) :
            Strategy(currentPlayer, Wpiececount, Bpiececount) {};


};


#endif
