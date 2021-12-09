#ifndef HUMAN_H
#define HUMAN_H

#include "strategy.h"

class Human : public Strategy {
public:
    std::pair<int, int> generateMove(string input) override;

    Human(int *Wpiececount, int *Bpiececount, shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) : Strategy(
            Wpiececount, Bpiececount, boardmap) {};
};

#endif
