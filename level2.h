#ifndef LEVEL2_H
#define LEVEL2_H

#include "strategy.h"

class Level2 : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>>
    generateMove(vector<vector<shared_ptr<Piece>>> &boardmap, string input) override;

    Level2(char *currentPlayer, int *Wpiececount, int *Bpiececount) :
            Strategy(currentPlayer, Wpiececount, Bpiececount) {};


};


#endif //LEVEL2_H
