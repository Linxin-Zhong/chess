#ifndef BOARD_H
#define BOARD_H

#include "strategy.h"
#include "Human.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Piece.h"
#include "subject.h"
#include <vector>

class Board : public Subject {
    bool isrunning;
    int Wpiececount;
    int Bpiececount;
    int WScore;
    int BScore;
    char currentPlayer;
    std::shared_ptr<Strategy> WPlayer;
    std::shared_ptr<Strategy> BPlayer;
    std::vector<std::vector<std::shared_ptr<Piece>>> boardmap;

public:
    bool isCheck();

    bool isCheckMate();

    bool isStalemate();

    void update(char c, int i);

    bool isRun();

    Board(char w, char b);

    void resign();

    void render();

};


#endif //CHESS_BOARD_H
