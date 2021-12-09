#ifndef LEVEL1_H
#define LEVEL1_H

#include "strategy.h"
using namespace std;

class Level1 : public Strategy {
public:
    std::pair<int, int> generateMove(string input) override;

    Level1(int *Wpiececount, int *Bpiececount, shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) : Strategy(
            Wpiececount, Bpiececount, boardmap) {};
};

#endif //LEVEL1_H
