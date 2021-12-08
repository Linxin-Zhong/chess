#include <iostream>
#include "board.h"

using namespace std;


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
            if (b[r][c] && b[r][c]->check(r, c, kingrow, kingcol)) {
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

bool Board::checkmateRecursion(std::vector<std::vector<std::shared_ptr<Piece>>> &currentboard,
                               char kingcolor, int checkrow, int checkcol) {
    int kingcol;
    int kingrow;
    if (kingcolor == 'W') {
        kingcol = Wkingcol;
        kingrow = Wkingrow;
    } else {
        kingcol = Bkingcol;
        kingrow = Bkingrow;
    }

    //check if the piece that is currently checking on the king can be eaten by the king
    int a, b; //dummy variables
    if ((abs(kingcol - checkcol) <= 1 && abs(kingrow - checkrow) <= 1) &&
        (!this->isCheck(currentboard, kingcolor, checkrow, checkcol, &a, &b))) {
        return false; // not checkmate
    }
    //check if the pieces that is currently checking on the king can be eaten by other pieces on the king's side
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (currentboard[r][c] && currentboard[r][c]->color == kingcolor &&
                currentboard[r][c]->check(r, c, checkrow, checkcol)) {
                vector<vector<shared_ptr<Piece>>> newboard;
                boardcopy(currentboard, newboard);
                newboard[checkrow][checkcol] = newboard[r][c];
                newboard[r][c] = nullptr;
                int newcheckcol;
                int newcheckrow;
                if (!isCheck(newboard, kingcolor, kingrow, kingcol, &newcheckrow, &newcheckcol)) {
                    return false;
                } else {
                    return (!checkmateRecursion(newboard, kingcolor, newcheckrow, newcheckcol));
                }
            }
        }
    }
    //check if there is other ways that the king could escape
    int escaperow[8];
    int escapecol[8];
    escaperow[1] = kingrow - 1;
    escapecol[1] = kingcol - 1;
    escaperow[2] = kingrow - 1;
    escapecol[2] = kingcol;
    escaperow[3] = kingrow - 1;
    escapecol[3] = kingcol + 1;
    escaperow[4] = kingrow;
    escapecol[4] = kingcol - 1;
    escaperow[5] = kingrow;
    escapecol[5] = kingcol + 1;
    escaperow[6] = kingrow + 1;
    escapecol[6] = kingcol - 1;
    escaperow[7] = kingrow + 1;
    escapecol[7] = kingcol;
    escaperow[8] = kingrow + 1;
    escapecol[8] = kingcol + 1;

    bool escapeway[8];
    for (int i = 0; i < 8; i++) {
        escapeway[i] = true;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (currentboard[i][j] == nullptr) {
                continue;
            }
            for (int k = 0; k < 8; k++) {
                if (currentboard[i][j]->color != currentPlayer) {
                    //pieces with same color as the king, check if they block king's way
                    if (i == escaperow[k] && j == escapecol[k]) {
                        escapeway[k] = false;
                    }
                } else if (currentboard[i][j]->color == currentPlayer) {
                    if (currentboard[i][j]->check(i, j, escaperow[k], escapecol[k])) {
                        escapeway[k] = false;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        if (escapeway[i] == true) {
            return false;
        }
    }
    return true;

}

bool Board::isCheckMate(char kingcolor, int checkrow, int checkcol) {
    return checkmateRecursion(boardmap, kingcolor, checkrow, checkcol);
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
        case 'K':
            Wkingcol = col;
            Wkingrow = row;
            newpiece = make_shared<King>(King('W', boardmap));
            Wpiececount++;
            break;
        case 'Q':
            newpiece = make_shared<Queen>(Queen('W', boardmap));
            Wpiececount++;
            break;
        case 'B':
            newpiece = make_shared<Bishop>(Bishop('W', boardmap));
            Wpiececount++;
            break;
        case 'R':
            newpiece = make_shared<Rook>(Rook('W', boardmap));
            Wpiececount++;
            break;
        case 'N':
            newpiece = make_shared<Knight>(Knight('W', boardmap));
            Wpiececount++;
            break;
        case 'P':
            newpiece = make_shared<Pawn>(Pawn('W', boardmap));
            Wpiececount++;
            break;
        case 'k':
            Bkingcol = col;
            Bkingrow = row;
            newpiece = make_shared<King>(King('B', boardmap));
            Bpiececount++;
            break;
        case 'q':
            newpiece = make_shared<Queen>(Queen('B', boardmap));
            Bpiececount++;
            break;
        case 'b':
            Bkingcol = col;
            Bkingrow = row;
            newpiece = make_shared<Bishop>(Bishop('B', boardmap));
            Bpiececount++;
            break;
        case 'r':
            newpiece = make_shared<Rook>(Rook('B', boardmap));
            Bpiececount++;
            break;
        case 'n':
            newpiece = make_shared<Knight>(Knight('B', boardmap));
            Bpiececount++;
            break;
        case 'p':
            newpiece = make_shared<Pawn>(Pawn('B', boardmap));
            Bpiececount++;
            break;
        default:
            return false;
    }

    char type = boardmap[row][col]->type();
    if (type >= 'a' && type <= 'z') {
        Bpiececount--;
    }
    if (type >= 'A' && type <= 'Z') {
        Wpiececount--;
    }
    boardmap[row][col] = newpiece;
    return true;
}

bool Board::remPiece(string coord) {
    int col = coord[0] - 'a';
    int row = coord[1] - '1';
    if (col >= 8 || row >= 8) {
        return false;
    } else {
        char type = boardmap[row][col]->type();
        if (type >= 'a' && type <= 'z') {
            Bpiececount--;
        }
        if (type >= 'A' && type <= 'Z') {
            Wpiececount--;
        }
        boardmap[row][col] = nullptr;
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
            boardmap.emplace_back(newrow);
        }
    }
}

Board::Board(char w, char b) {
    this->PlayersInit(w, b);
};

void Board::default_init() {
    currentPlayer = 'W';
    Bkingcol = 4;
    Bkingrow = 7;
    Wkingcol = 4;
    Wkingrow = 0;
    Wpiececount = 16;
    Bpiececount = 16;
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
}

void Board::PlayersInit(char w, char b) {
    switch (w) {
        case 'h':
            this->WPlayer = make_shared<Human>(Human(boardmap));
        case '1':
            this->WPlayer = make_shared<Level1>(Level1(boardmap));
        case '2':
            this->WPlayer = make_shared<Level2>(Level2(boardmap));
        case '3':
            this->WPlayer = make_shared<Level3>(Level3(boardmap));
    }
    switch (b) {
        case 'h':
            this->BPlayer = make_shared<Human>(Human(boardmap));
        case '1':
            this->BPlayer = make_shared<Level1>(Level1(boardmap));
        case '2':
            this->BPlayer = make_shared<Level2>(Level2(boardmap));
        case '3':
            this->BPlayer = make_shared<Level3>(Level3(boardmap));
    }
}

void Board::move(char fromc, int fromr, char toc, int tor) {
    int fromcol = fromc - 'a';
    int tocol = toc - 'a';
    int fromrow = fromr - 1;
    int torow = tor - 1;

    if (boardmap[fromrow][fromcol] != nullptr) {
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
        int checkrow;
        int checkcol;
        char kingcolor;
        if (currentPlayer == 'W') {
            kingcolor = 'B';
            check = this->isCheck(boardmap, 'B', Bkingrow, Bkingcol, &checkrow, &checkcol);
        } else {
            kingcolor = 'W';
            check = this->isCheck(boardmap, 'W', Wkingrow, Wkingcol, &checkrow, &checkcol);
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
