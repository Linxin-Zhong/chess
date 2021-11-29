#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

class Board;

class Piece {
    std::shared_ptr<Board> b;
    int value;  // determine the value of a piece
    char color;
public:
    char getx();

    char gety();

    virtual void move(char c, int i);

    virtual ~Piece() = default;
};

#endif //CHESS_PIECE_H
