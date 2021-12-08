#ifndef LEVEL2_H
#define LEVEL2_H

#include "strategy.h"

class Level2 : public Strategy {
public:
    std::vector<std::pair<char, int>> generateMove() override;

    Level2(vector<vector<shared_ptr<Piece>>> &boardmap) : Strategy(boardmap) {};
};


#endif //LEVEL2_H
