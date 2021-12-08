#ifndef HUMAN_H
#define HUMAN_H

#include "strategy.h"

class Human : public Strategy {
public:
    std::vector<std::pair<char, int>> generateMove() override;

    Human(vector<vector<shared_ptr<Piece>>> &boardmap) : Strategy(boardmap) {};
};

#endif
