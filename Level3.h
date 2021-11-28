#ifndef LEVEL3_H
#define LEVEL3_H


#include "strategy.h"

class level3 : public Strategy {
public:
    std::vector<std::pair<char, int>> generateMove() override;

    level3(std::shared_ptr<Board> b) : Strategy(b) {};
};


#endif
