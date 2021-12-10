#ifndef HUMAN_H
#define HUMAN_H

#include "strategy.h"

class Human : public Strategy {
public:
    pair<pair<int, int>, pair<int, int>> generateMove(string input) override;

    Human(char *currentPlayer, int *Wpiececount, int *Bpiececount,
          shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) : Strategy(
            currentPlayer, Wpiececount, Bpiececount, boardmap) {};
};

#endif
