#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>

class Board;

class Strategy {
protected:
    std::shared_ptr<Board> b;
public:
    virtual std::vector<std::pair<char, int>> generateMove() = 0;

    Strategy(std::shared_ptr<Board> b) : b(b) {};
};


#endif
