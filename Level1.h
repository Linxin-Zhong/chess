#ifndef LEVEL1_H
#define LEVEL1_H

#include "strategy.h"

class level1 : public Strategy {
public:
    std::vector<std::pair<char, int>> generateMove() override;

    level1(std::shared_ptr<Board> b) : Strategy(b) {};
};

#endif //LEVEL1_H
