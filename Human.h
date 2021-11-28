#ifndef HUMAN_H
#define HUMAN_H

#include "strategy.h"

class human : public Strategy {
public:
    std::vector<std::pair<char, int>> generateMove() override;

    human(std::shared_ptr<Board> b) : Strategy(b) {};
};

#endif
