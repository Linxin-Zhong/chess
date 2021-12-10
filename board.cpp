#include <iostream>
#include "board.h"
#include <sstream>
#include <string>

using namespace std;


void Board::makeMove(string input) {
    //call generate move
    //return tor, toc
    pair<pair<int, int>, pair<int, int>> wantmove;
    if (currentPlayer == 'W') {
        wantmove = this->WPlayer->generateMove(input);
    } else {
        wantmove = this->BPlayer->generateMove(input);
    }

    if (wantmove.second.first != -1 && wantmove.second.second != -1) {
        move(wantmove.first.first, wantmove.first.second, wantmove.second.first, wantmove.second.second);
    } else {
        cout << "Invalid move! plz try again" << endl;
    }

}

pair<pair<int, int>, pair<int, int>> Board::getKingcoord() {
    pair<pair<int, int>, pair<int, int>> kingcoord;
    kingcoord.first.first = Wkingrow;
    kingcoord.first.second = Wkingcol;
    kingcoord.second.first = Bkingrow;
    kingcoord.second.second = Bkingcol;
    return kingcoord;
}


bool Board::isCheck(vector<vector<shared_ptr<Piece>>> &b, char kingcolor, int kingrow,
                    int kingcol, int *checkrow, int *checkcol) {
    *checkcol = -1;
    *checkrow = -1;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (b[r][c] && b[r][c]->check(b, r, c, kingrow, kingcol)) {
                if (b[r][c]->color != kingcolor) {
                    *checkrow = r;
                    *checkcol = c;
                    return true;
                }
            }
        }
    }
    return false;
}

//copy content of a to b, b should be empty
void boardcopy(vector<vector<shared_ptr<Piece>>> &a, vector<vector<shared_ptr<Piece>>> &b) {
    for (int i = 0; i < 8; i++) {
        vector<shared_ptr<Piece>> newrow;
        for (int j = 0; j < 8; j++) {
            newrow.emplace_back(a[i][j]);
        }
        b.emplace_back(newrow);
    }
}


bool Board::isCheckMate(char kingcolor, int checkrow, int checkcol) {
    int kingcol, kingrow;
    if (kingcolor == 'W') {
        kingrow = Wkingrow;
        kingcol = Wkingcol;
    } else {
        kingrow = Bkingrow;
        kingcol = Bkingcol;
    }
    //1. king can escape directlly (one legal move)
    vector<pair<int, int>> escapeMoves = (*boardmap)[kingrow][kingcol]->legalMoves(kingrow, kingcol);
    if (escapeMoves.size() > 0) {
        return false;
    }

    //2. move of other pieces can eliminate the check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == kingcolor) {
                vector<pair<int, int>> legalmoves = (*boardmap)[i][j]->legalMoves(i, j);
                if (legalmoves.size() > 0) {
                    for (int k = 0; k < legalmoves.size(); k++) {
                        vector<vector<shared_ptr<Piece>>> newboard;
                        boardcopy((*boardmap), newboard);
                        newboard[legalmoves[k].first][legalmoves[k].second] = newboard[i][j];
                        newboard[i][j] = nullptr;
                        int checkrow2, checkcol2;
                        if (!isCheck(newboard, kingcolor, kingrow, kingcol, &checkrow2, &checkcol2)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;


}

/*bool Board::isStalemate() {

}

void Board::update(char c, int i) {

}

bool Board::isRun() {

}*/


bool Board::addPiece(char p, string coord) {
    shared_ptr<Piece> newpiece;
    int col = coord[0] - 'a';
    int row = coord[1] - '1';
    if (col >= 8 || row >= 8) {
        return false;
    }
    switch (p) {

        //Queen(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
        // char color, int value, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap);
        case 'K':
            Wkingcol = col;
            Wkingrow = row;
            newpiece = make_shared<King>(King(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W', boardmap));
            Wpiececount++;
            break;
        case 'Q':
            newpiece = make_shared<Queen>(Queen(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W', boardmap));
            Wpiececount++;
            break;
        case 'B':
            newpiece = make_shared<Bishop>(Bishop(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W', boardmap));
            Wpiececount++;
            break;
        case 'R':
            newpiece = make_shared<Rook>(Rook(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W', boardmap));
            Wpiececount++;
            break;
        case 'N':
            newpiece = make_shared<Knight>(Knight(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W', boardmap));
            Wpiececount++;
            break;
        case 'P':
            newpiece = make_shared<Pawn>(Pawn(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W', boardmap));
            Wpiececount++;
            break;
        case 'k':
            Bkingcol = col;
            Bkingrow = row;
            newpiece = make_shared<King>(King(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B', boardmap));
            Bpiececount++;
            break;
        case 'q':
            newpiece = make_shared<Queen>(Queen(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B', boardmap));
            Bpiececount++;
            break;
        case 'b':
            newpiece = make_shared<Bishop>(Bishop(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B', boardmap));
            Bpiececount++;
            break;
        case 'r':
            newpiece = make_shared<Rook>(Rook(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B', boardmap));
            Bpiececount++;
            break;
        case 'n':
            newpiece = make_shared<Knight>(Knight(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B', boardmap));
            Bpiececount++;
            break;
        case 'p':
            newpiece = make_shared<Pawn>(Pawn(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B', boardmap));
            Bpiececount++;
            break;
        default:
            return false;
    }

    char type = (*boardmap)[row][col]->type();
    if (type >= 'a' && type <= 'z') {
        Bpiececount--;
    }
    if (type >= 'A' && type <= 'Z') {
        Wpiececount--;
    }
    (*boardmap)[row][col] = newpiece;
    return true;
}


bool Board::remPiece(string coord) {
    int col = coord[0] - 'a';
    int row = coord[1] - '1';
    if (col >= 8 || row >= 8) {
        return false;
    } else {
        char type = (*boardmap)[row][col]->type();
        if (type >= 'a' && type <= 'z') {
            Bpiececount--;
        }
        if (type >= 'A' && type <= 'Z') {
            Wpiececount--;
        }
        (*boardmap)[row][col] = nullptr;
        return true;
    }
}

bool Board::setNextPlayer(char color) {
    if (color == 'W' || color == 'B') {
        currentPlayer = color;
    } else {
        return false;
    }
}

Board::Board(string i) {
    vector<vector<shared_ptr<Piece>>> b;
    boardmap = make_shared<vector<vector<shared_ptr<Piece>>>>(b);
    if (i == "empty") {
        currentPlayer = 'W';
        Wpiececount = 0;
        Bpiececount = 0;
        Bkingcol = -1;
        Bkingrow = -1;
        Wkingcol = -1;
        Wkingrow = -1;
        for (int i = 0; i < 8; i++) {
            vector<shared_ptr<Piece>> newrow;
            for (int j = 0; j < 8; j++) {
                newrow.emplace_back(nullptr);
            }
            (*boardmap).emplace_back(newrow);
        }
    }
}

void Board::clear() {
    currentPlayer = 'W';
    Wpiececount = 0;
    Bpiececount = 0;
    Bkingcol = -1;
    Bkingrow = -1;
    Wkingcol = -1;
    Wkingrow = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            (*boardmap)[i][j] = nullptr;
        }
    }
}

Board::Board(char w, char b) {
    vector<vector<shared_ptr<Piece>>> tempb;
    boardmap = make_shared<vector<vector<shared_ptr<Piece>>>>(tempb);
    this->PlayersInit(w, b);
};

void Board::default_init() {
    currentPlayer = 'W';
    Bkingcol = 4;
    Bkingrow = 7;
    Wkingcol = 4;
    Wkingrow = 0;
    //Wpiececount = 16;
    //Bpiececount = 16;
    for (int row = 1; row <= 8; row++) {
        //vector<shared_ptr<Piece>> newrow;
        for (char col = 'a'; col <= 'h'; col++) {
            stringstream stream;
            stream << col;
            string s = stream.str();
            if ((row == 1) && ((col == 'a') || (col == 'h'))) {
                //place a white rook
                /*shared_ptr<Piece> newpiece = make_shared<Rook>(Rook('W', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "1";
                addPiece('R', s);
            } else if ((row == 8) && ((col == 'a') || (col == 'h'))) {
                //place a black rook
                /*shared_ptr<Piece> newpiece = make_shared<Rook>(Rook('B', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "8";
                addPiece('r', s);
            } else if ((row == 1) && ((col == 'b') || (col == 'g'))) {
                //place a white knight
                /*shared_ptr<Piece> newpiece = make_shared<Knight>(Knight('W', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "1";
                addPiece('N', s);
            } else if ((row == 8) && ((col == 'b') || (col == 'g'))) {
                //place a black knight
                /*shared_ptr<Piece> newpiece = make_shared<Knight>(Knight('B', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "8";
                addPiece('n', s);
            } else if ((row == 1) && ((col == 'c') || (col == 'f'))) {
                //place a white bishop
                /*shared_ptr<Piece> newpiece = make_shared<Bishop>(Bishop('W', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "1";
                addPiece('B', s);
            } else if ((row == 8) && ((col == 'c') || (col == 'f'))) {
                //place a black bishop
                /*shared_ptr<Piece> newpiece = make_shared<Bishop>(Bishop('B', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "8";
                addPiece('b', s);
            } else if (row == 1 && col == 'd') {
                //place a white queen
                /*shared_ptr<Piece> newpiece = make_shared<Queen>(Queen('W', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "1";
                addPiece('Q', s);
            } else if (row == 8 && col == 'd') {
                //place a black queen
                /*shared_ptr<Piece> newpiece = make_shared<Queen>(Queen('B', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "8";
                addPiece('q', s);
            } else if (row == 1 && col == 'e') {
                //place a white  king
                /*shared_ptr<Piece> newpiece = make_shared<King>(King('W', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "1";
                addPiece('K', s);
            } else if (row == 8 && col == 'e') {
                //place a black king
                /*shared_ptr<Piece> newpiece = make_shared<King>(King('B', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "8";
                addPiece('k', s);
            } else if (row == 2) {
                //place a white pawn
                /*shared_ptr<Piece> newpiece = make_shared<Pawn>(Pawn('W', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "2";
                addPiece('P', s);
            } else if (row == 7) {
                //place a black pawn
                /*shared_ptr<Piece> newpiece = make_shared<Pawn>(Pawn('B', boardmap));
                newrow.emplace_back(newpiece);*/
                s += "7";
                addPiece('p', s);
            } else {
                //empty spot
                //newrow.emplace_back(nullptr);
            }
        }
        //(*boardmap).emplace_back(newrow);
    }
}

void Board::PlayersInit(char w, char b) {
    switch (w) {
        case 'h':
            this->WPlayer = make_shared<Human>(Human(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
        case '1':
            this->WPlayer = make_shared<Level1>(Level1(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
        case '2':
            this->WPlayer = make_shared<Level2>(Level2(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
        case '3':
            this->WPlayer = make_shared<Level3>(Level3(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
    }
    switch (b) {
        case 'h':
            this->BPlayer = make_shared<Human>(Human(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
        case '1':
            this->BPlayer = make_shared<Level1>(Level1(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
        case '2':
            this->BPlayer = make_shared<Level2>(Level2(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
        case '3':
            this->BPlayer = make_shared<Level3>(Level3(&currentPlayer, &Wpiececount, &Bpiececount, boardmap));
            break;
    }
}

void Board::move(int fromrow, int fromcol, int torow, int tocol) {

    //if doing castling, move the rook at the same time
    if ((*boardmap)[fromrow][fromcol]->type() == 'k' && abs(fromcol - tocol) == 2
        && tocol == 2) {
        //black king long castling
        (*boardmap)[7][3] = (*boardmap)[7][0];
        (*boardmap)[7][0] = nullptr;

    } else if ((*boardmap)[fromrow][fromcol]->type() == 'k' && abs(fromcol - tocol) == 2
               && tocol == 6) {
        //black king short castling
        (*boardmap)[7][5] = (*boardmap)[7][7];
        (*boardmap)[7][7] = nullptr;
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'K' && abs(fromcol - tocol) == 2
               && tocol == 2) {
        //white king long castling
        (*boardmap)[0][3] = (*boardmap)[0][0];
        (*boardmap)[0][0] = nullptr;

    } else if ((*boardmap)[fromrow][fromcol]->type() == 'K' && abs(fromcol - tocol) == 2
               && tocol == 6) {
        //white king short castling
        (*boardmap)[0][5] = (*boardmap)[0][7];
        (*boardmap)[0][7] = nullptr;
    }


    //eliminate the pawn in the situation of en passant
    if ((*boardmap)[fromrow][fromcol]->type() == 'P' && torow == fromrow + 1 && tocol == fromcol + 1) {
        //move white upperright
        if ((*boardmap)[fromrow][fromcol + 1]->type() == 'p') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol + 1]);
            if (p->getEnpassant()) {
                Bpiececount--;
                (*boardmap)[fromrow][fromcol + 1] = nullptr;
            }
        }
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'P' && torow == fromrow + 1 && tocol == fromcol - 1) {
        //move white upperleft
        if ((*boardmap)[fromrow][fromcol - 1]->type() == 'p') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol - 1]);
            if (p->getEnpassant()) {
                Bpiececount--;
                (*boardmap)[fromrow][fromcol - 1] = nullptr;
            }
        }
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'p' && torow == fromrow - 1 && tocol == fromcol + 1) {
        //move black upperright
        if ((*boardmap)[fromrow][fromcol + 1]->type() == 'P') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol + 1]);
            if (p->getEnpassant()) {
                Wpiececount--;
                (*boardmap)[fromrow][fromcol + 1] = nullptr;
            }
        }

    } else if ((*boardmap)[fromrow][fromcol]->type() == 'p' && torow == fromrow - 1 && tocol == fromcol - 1) {
        //move black upperleft
        if ((*boardmap)[fromrow][fromcol - 1]->type() == 'P') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol - 1]);
            if (p->getEnpassant()) {
                Wpiececount--;
                (*boardmap)[fromrow][fromcol - 1] = nullptr;
            }
        }

    }

    //make the pawn available to be eaten in the situation of enpassant after first move of two grids
    if ((*boardmap)[fromrow][fromcol]->type() == 'p'
        || (*boardmap)[fromrow][fromcol]->type() == 'P') {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol]);
        if (p->getHaventMoved()) {
            p->setHaventMoved(false);
            if (abs(torow - fromrow) == 2) {
                p->setEnpassant(true);
            }
        }
    }

    //make the actual move
    if ((*boardmap)[fromrow][fromcol] != nullptr) {
        if ((*boardmap)[torow][tocol] != nullptr) {
            if ((*boardmap)[torow][tocol]->color == 'W') {
                Wpiececount--;
            } else {
                Bpiececount--;
            }
            (*boardmap)[torow][tocol] = nullptr;
        }

        //move the
        (*boardmap)[torow][tocol] = (*boardmap)[fromrow][fromcol];
        (*boardmap)[fromrow][fromcol] = nullptr;


        if ((*boardmap)[torow][tocol]->type() == 'k' || (*boardmap)[torow][tocol]->type() == 'K') {
            if ((*boardmap)[torow][tocol]->color == 'B') {
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
        int checkrow;
        int checkcol;
        char kingcolor;
        if (currentPlayer == 'W') {
            kingcolor = 'B';
            check = this->isCheck(*boardmap, 'B', Bkingrow, Bkingcol, &checkrow, &checkcol);
        } else {
            kingcolor = 'W';
            check = this->isCheck(*boardmap, 'W', Wkingrow, Wkingcol, &checkrow, &checkcol);
        }

        if (check) {
            if (isCheckMate(kingcolor, checkrow, checkcol)) {
                cout << "Checkmate" << endl;
            } else {
                cout << "Check" << endl;
            }
        }
        //stalemate = this->isStalemate();


        //change player, at the very end of the move
        if (currentPlayer == 'W') {
            currentPlayer = 'B';
        } else {
            currentPlayer = 'W';
        }
        this->print();
    }




    //if move happens, en passant will be no longer valid
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j]->type() == 'p'
                || (*boardmap)[i][j]->type() == 'P') {
                shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[i][j]);
                if (p->getEnpassant()) {
                    p->setEnpassant(false);
                }
            }
        }
    }


    //if move two the king or rook happened, it's no longer available for castling
    if ((*boardmap)[torow][tocol]->type() == 'k'
        || (*boardmap)[torow][tocol]->type() == 'K') {
        shared_ptr<King> k = dynamic_pointer_cast<King>((*boardmap)[torow][tocol]);
        if (k->getHaventMoved()) {
            k->setHaventMoved(false);
        }
    }

    if ((*boardmap)[torow][tocol]->type() == 'r'
        || (*boardmap)[torow][tocol]->type() == 'R') {
        shared_ptr<Rook> r = dynamic_pointer_cast<Rook>((*boardmap)[torow][tocol]);
        if (r->getHaventMoved()) {
            r->setHaventMoved(false);
        }
    }

}

void Board::print() {
    cout << "Wpiececount: " << Wpiececount << endl;
    cout << "Bpiececount: " << Bpiececount << endl;
    cout << "NextMove: " << currentPlayer << endl;
    for (int i = row8; i >= row1; i--) {
        cout << i + 1 << " ";
        for (int j = cola; j <= colh; j++) {
            cout << (*boardmap)[i][j]->type() << " ";
        }
        cout << endl;
    }
    cout << "  ";
    for (char c = 'a'; c <= 'h'; c++) {
        cout << c << " ";
    }
    cout << endl;
}

/*
void Board::resign() {

}
*/

void Board::render() {
    notifyObservers();
}

char Board::getCurrentPlayer() {
    return currentPlayer;
}
