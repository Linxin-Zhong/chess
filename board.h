#ifndef BOARD_H
#define BOARD_H

#include "strategy.h"
#include "human.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"
#include "subject.h"
#include <vector>

const int cola = 0;
const int colb = 1;
const int colc = 2;
const int cold = 3;
const int cole = 4;
const int colf = 5;
const int colg = 6;
const int colh = 7;

const int row1 = 0;
const int row2 = 1;
const int row3 = 2;
const int row4 = 3;
const int row5 = 4;
const int row6 = 5;
const int row7 = 6;
const int row8 = 7;

class Board : public Subject {
    /* bool isrunning;
     int WScore;
     int BScore;
     */
    char currentPlayer;
    std::shared_ptr<Strategy> WPlayer;
    std::shared_ptr<Strategy> BPlayer;
    int Wpiececount;
    int Bpiececount;
    int Bkingcol;
    int Bkingrow;
    int Wkingcol;
    int Wkingrow;

public:
    std::vector<std::vector<std::shared_ptr<Piece>>> boardmap;

    Board(char w, char b);

    void move(char fromc, int fromr, char toc, int tor);

    void print();

    bool isCheck(int tocol, int torow);

    /*bool isCheckMate();

    bool isStalemate();

    void update(char c, int i);

    bool isRun();

    void resign();

    void render();*/

};


#endif //CHESS_BOARD_H
