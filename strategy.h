#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
using namespace std;

class Board;

class Strategy {
protected:
    vector<vector<shared_ptr<Piece>>> boardmap;
public:
    virtual vector<pair<char, int>> generateMove() = 0;

    Strategy(vector<vector<shared_ptr<Piece>>> &boardmap) : boardmap(boardmap) {};
};


#endif
