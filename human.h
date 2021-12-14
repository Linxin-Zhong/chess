#ifndef HUMAN_H
#define HUMAN_H

#include "strategy.h"

class Human : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>>
    generateMove(vector<vector<shared_ptr<Piece>>> &boardmap, string input) override;

    Human(char *currentPlayer, int *Wpiececount, int *Bpiececount) : Strategy(
            currentPlayer, Wpiececount, Bpiececount) {};
};

#endif
