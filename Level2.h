#ifndef LEVEL2_H
#define LEVEL2_H

#include "strategy.h"

class level2 : public Strategy {
public:
    std::vector<std::pair<char, int>> generateMove() override;

    level2(std::shared_ptr<Board> b) : Strategy(b) {};
};


#endif //LEVEL2_H
