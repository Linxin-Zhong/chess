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

    char currentPlayer;
    std::shared_ptr<Strategy> WPlayer;
    std::shared_ptr<Strategy> BPlayer;
    int Wpiececount;
    int Bpiececount;
    int Bkingcol;
    int Bkingrow;
    int Wkingcol;
    int Wkingrow;
    bool check = false;
    bool checkmate = false;
    bool stalemate = false;
    bool resign = false;
    int fromrow = -1;
    int fromcol = -1;
    int torow = -1;
    int tocol = -1;
    bool init = false;


public:

    void clearCheck();

    void clearCheckStaleMate();

    void makeMove(string input);

    void clear();

    bool addPiece(char p, string coord);

    bool remPiece(string coord);

    bool setNextPlayer(char color);

    void PlayersInit(char w, char b);

    shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap;

    void default_init();

    Board(string i); //for temporary board in setup purpose

    void move(int fromrow, int fromcol, int torow, int tocol);

    void print();

    bool isCheck(std::vector<std::vector<std::shared_ptr<Piece>>> &b, char kingcolor, int kingrow, int kingcol,
                 int *checkrow, int *checkcol);

    bool isCheckMate(char kingcolor, int checkrow, int checkcol);

    pair<pair<int, int>, pair<int, int>> getKingcoord();

    bool isStalemate(char kingcolor);

    char getCurrentPlayer();

    void setResign();

    bool isResign();

    bool ischeck();

    bool ischeckmate();

    bool isstalemate();

    vector<pair<int, int>> getInput();

    void setInput();

    void setInit(bool b);

    bool getInit();

};


#endif //CHESS_BOARD_H
