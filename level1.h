#ifndef LEVEL1_H
#define LEVEL1_H

#include "strategy.h"
using namespace std;

class Level1 : public Strategy {
public:
    vector<pair<char, int>> generateMove() override;

    Level1(vector<vector<shared_ptr<Piece>>> &boardmap) : Strategy(boardmap) {};
};

#endif //LEVEL1_H
