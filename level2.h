#ifndef LEVEL2_H
#define LEVEL2_H

#include "strategy.h"

class Level2 : public Strategy {
public:
    std::pair<int, int> generateMove(string input) override;

    Level2(int *Wpiececount, int *Bpiececount, shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap) : Strategy(
            Wpiececount, Bpiececount, boardmap) {};
};


#endif //LEVEL2_H
