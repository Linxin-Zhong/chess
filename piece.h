#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>
#include <memory>
#include <vector>
using namespace std;

class Board;

class Piece {
protected:
    shared_ptr<vector<vector<shared_ptr<Piece>>>> boardmap;
    int value;  // determine the value of a piece
    char color;
    int *Wkingrow;
    int *Wkingcol;
    int *Bkingrow;
    int *Bkingcol;
public:

    //copy content of a to b, b should be empty
    void boardcopy2(vector<vector<shared_ptr<Piece>>> &a, vector<vector<shared_ptr<Piece>>> &b);

    bool isCheck(vector<vector<shared_ptr<Piece>>> &b, char kingcolor, int kingrow,
                 int kingcol, int *checkrow, int *checkcol);

    Piece(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol, char color, int value,
          shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap);

    virtual bool check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol) = 0;

    virtual vector<pair<int, int>> legalMoves(int r, int c) = 0;
    virtual vector<pair<int, int>> captureMoves(int r, int c) = 0;
    virtual vector<pair<int, int>> avoidMoves(int r, int c) = 0;
    virtual vector<pair<int, int>> checkMoves(int r, int c) = 0;
    
//    virtual void move(char c, int i) = 0;
    virtual ~Piece() = default;

    char type(); //return what type of piece is that, one of: k, q, b, r, n, p
    char getColor(); // return the color of the piece
    friend class Board;
};

#endif
