#include <iostream>
#include "board.h"

using namespace std;


bool Board::isCheck(int torow, int tocol) {
    char type = boardmap[torow][tocol]->type();
    if (currentPlayer == 'W') {
        //white just moved
        return boardmap[torow][tocol]->check(tocol, torow, Bkingcol, Bkingrow);
    } else {
        return boardmap[torow][tocol]->check(tocol, torow, Wkingcol, Wkingrow);
    }
}

/*bool Board::isCheckMate() {

}

bool Board::isStalemate() {

}

void Board::update(char c, int i) {

}

bool Board::isRun() {

}*/

Board::Board(char w, char b) {
    currentPlayer = 'W';
    Bkingcol = 4;
    Bkingrow = 7;
    Wkingcol = 4;
    Wkingrow = 0;
    Wpiececount = 16;
    Bpiececount = 16;
    switch (w) {
        case 'h':
            this->WPlayer = make_shared<Human>(Human(make_shared<Board>(*this)));
        case '1':
            this->WPlayer = make_shared<Level1>(Level1(make_shared<Board>(*this)));
        case '2':
            this->WPlayer = make_shared<Level2>(Level2(make_shared<Board>(*this)));
        case '3':
            this->WPlayer = make_shared<Level3>(Level3(make_shared<Board>(*this)));
    }
    switch (b) {
        case 'h':
            this->BPlayer = make_shared<Human>(Human(make_shared<Board>(*this)));
        case '1':
            this->BPlayer = make_shared<Level1>(Level1(make_shared<Board>(*this)));
        case '2':
            this->BPlayer = make_shared<Level2>(Level2(make_shared<Board>(*this)));
        case '3':
            this->BPlayer = make_shared<Level3>(Level3(make_shared<Board>(*this)));
    }

    for (int row = 1; row <= 8; row++) {
        vector<shared_ptr<Piece>> newrow;
        for (char col = 'a'; col <= 'h'; col++) {
            if ((row == 1) && ((col == 'a') || (col == 'h'))) {
                //place a white rook
                shared_ptr<Piece> newpiece = make_shared<Rook>(Rook('W', boardmap));
                newrow.emplace_back(newpiece);
            } else if ((row == 8) && ((col == 'a') || (col == 'h'))) {
                //place a black rook
                shared_ptr<Piece> newpiece = make_shared<Rook>(Rook('B', boardmap));
                newrow.emplace_back(newpiece);
            } else if ((row == 1) && ((col == 'b') || (col == 'g'))) {
                //place a white knight
                shared_ptr<Piece> newpiece = make_shared<Knight>(Knight('W', boardmap));
                newrow.emplace_back(newpiece);
            } else if ((row == 8) && ((col == 'b') || (col == 'g'))) {
                //place a black knight
                shared_ptr<Piece> newpiece = make_shared<Knight>(Knight('B', boardmap));
                newrow.emplace_back(newpiece);
            } else if ((row == 1) && ((col == 'c') || (col == 'f'))) {
                //place a white bishop
                shared_ptr<Piece> newpiece = make_shared<Bishop>(Bishop('W', boardmap));
                newrow.emplace_back(newpiece);
            } else if ((row == 8) && ((col == 'c') || (col == 'f'))) {
                //place a black bishop
                shared_ptr<Piece> newpiece = make_shared<Bishop>(Bishop('B', boardmap));
                newrow.emplace_back(newpiece);
            } else if (row == 1 && col == 'd') {
                //place a white queen
                shared_ptr<Piece> newpiece = make_shared<Queen>(Queen('W', boardmap));
                newrow.emplace_back(newpiece);
            } else if (row == 8 && col == 'd') {
                //place a black queen
                shared_ptr<Piece> newpiece = make_shared<Queen>(Queen('B', boardmap));
                newrow.emplace_back(newpiece);
            } else if (row == 1 && col == 'e') {
                //place a white  king
                shared_ptr<Piece> newpiece = make_shared<King>(King('W', boardmap));
                newrow.emplace_back(newpiece);
            } else if (row == 8 && col == 'e') {
                //place a black king
                shared_ptr<Piece> newpiece = make_shared<King>(King('B', boardmap));
                newrow.emplace_back(newpiece);
            } else if (row == 2) {
                //place a white pawn
                shared_ptr<Piece> newpiece = make_shared<Pawn>(Pawn('W', boardmap));
                newrow.emplace_back(newpiece);
            } else if (row == 7) {
                //place a black pawn
                shared_ptr<Piece> newpiece = make_shared<Pawn>(Pawn('B', boardmap));
                newrow.emplace_back(newpiece);
            } else {
                //empty spot
                newrow.emplace_back(nullptr);
            }
        }
        boardmap.emplace_back(newrow);
    }
};

void Board::move(char fromc, int fromr, char toc, int tor) {
    int fromcol = fromc - 'a';
    int tocol = toc - 'a';
    int fromrow = fromr - 1;
    int torow = tor - 1;
    if (boardmap[torow][tocol] != nullptr) {
        if (boardmap[torow][tocol]->color == 'W') {
            Wpiececount--;
        } else {
            Bpiececount--;
        }
        boardmap[torow][tocol] = nullptr;
    }
    boardmap[torow][tocol] = boardmap[fromrow][fromcol];
    boardmap[fromrow][fromcol] = nullptr;

    if (boardmap[torow][tocol]->type() == 'k' || boardmap[torow][tocol]->type() == 'K') {
        if (boardmap[torow][tocol]->color == 'B') {
            Bkingcol = tocol;
            Bkingrow = torow;
        } else {
            Wkingcol = tocol;
            Wkingrow = torow;
        }
    }

    //check for situations that will end the game
    bool check;
    bool checkmate;
    bool stalemate;
    check = this->isCheck(torow, tocol);
    if (check) {
        cout << "Check";
    }
    //checkmate = this->isCheckMate();
    //stalemate = this->isStalemate();


    //change player, at the very end of the move
    if (currentPlayer = 'W') {
        currentPlayer = 'B';
    } else {
        currentPlayer = 'W';
    }
}

void Board::print() {
    cout << "Wpiececount: " << Wpiececount << endl;
    cout << "Bpiececount: " << Bpiececount << endl;
    for (int i = row8; i >= row1; i--) {
        for (int j = cola; j <= colh; j++) {
            cout << this->boardmap[i][j]->type() << " ";
        }
        cout << endl;
    }
}
/*
void Board::resign() {

}

void Board::render() {

}*/



