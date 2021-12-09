#ifndef LEVEL3_H
#define LEVEL3_H


#include "strategy.h"

class Level3 : public Strategy {
public:
    std::pair<int, int> generateMove(string input) override;

    Level3(int *Wpiececount, int *Bpiececount, shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) : Strategy(
            Wpiececount, Bpiececount, boardmap) {};
};


#endif
