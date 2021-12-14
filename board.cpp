#include <iostream>
#include "board.h"
#include <sstream>
#include <string>

using namespace std;


void Board::makeMove(string input) {
    string i = input;
    //call generate move
    //return tor, toc
    pair<pair<int, int>, pair<int, int>> wantmove;
    if (currentPlayer == 'W') {
        wantmove = this->WPlayer->generateMove(*boardmap, input);
    } else {
        wantmove = this->BPlayer->generateMove(*boardmap, input);
    }
    
    if (wantmove.first.first == -1) { // if wantmove is invalid
        return;
    }

    bool invalidpromotion = false;
    if ((*boardmap)[wantmove.first.first][wantmove.first.second]->type() == 'P') {
        if (wantmove.second.first == 7) {
            char a = wantmove.first.second + 'a';
            char b = wantmove.first.first + '1';
            string coord = "";
            coord += a;
            coord += b;

            if (dynamic_pointer_cast<Human>(WPlayer) != nullptr) {
                stringstream ss(i);
                string command;
                string movefrom;
                string moveto;
                string type;
                ss >> command;
                ss >> movefrom;
                ss >> moveto;
                ss >> type;
                if (type != "") {
                    if (type[0] != 'B' && type[0] != 'Q' && type[0] != 'R' &&
                        type[0] != 'N') {
                        cout << "Invalid promotion!" << endl;
                        invalidpromotion = true;
                    } else {
                        remPiece(coord);
                        addPiece(type[0], coord);
                    }
                }
            } else {
                remPiece(coord);
                addPiece('Q', coord);
            }
        }
    } else if ((*boardmap)[wantmove.first.first][wantmove.first.second]->type() == 'p') {
        if (wantmove.second.first == 0) {
            char a = wantmove.first.second + 'a';
            char b = wantmove.first.first + '1';
            string coord = "";
            coord += a;
            coord += b;
            if (dynamic_pointer_cast<Human>(BPlayer) != nullptr) {
                stringstream ss(i);
                string command;
                string movefrom;
                string moveto;
                string type;
                ss >> command;
                ss >> movefrom;
                ss >> moveto;
                ss >> type;
                if (type != "") {
                    if (type[0] != 'b' && type[0] != 'q' && type[0] != 'r' &&
                        type[0] != 'n') {
                        cout << "Invalid promotion!" << endl;
                        invalidpromotion = true;
                    } else {
                        remPiece(coord);
                        addPiece(type[0], coord);
                    }
                }

            } else {
                remPiece(coord);
                addPiece('q', coord);
            }
        }
    }

    if (wantmove.second.first != -1 && wantmove.second.second != -1 && !invalidpromotion) {
        move(wantmove.first.first, wantmove.first.second, wantmove.second.first, wantmove.second.second);
    } else if (!invalidpromotion) {
        cout << "Invalid move! please try again" << endl;
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
void Board::boardcopy(vector<vector<shared_ptr<Piece>>> &a, vector<vector<shared_ptr<Piece>>> &b) {
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
    vector<pair<int, int>> escapeMoves = (*boardmap)[kingrow][kingcol]->legalMoves(*boardmap, kingrow, kingcol);
    if (escapeMoves.size() > 0) {
        return false;
    }

    //2. move of other pieces can eliminate the check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == kingcolor) {
                vector<pair<int, int>> legalmoves = (*boardmap)[i][j]->legalMoves(*boardmap, i, j);
                if (legalmoves.size() > 0) {
                    for (size_t k = 0; k < legalmoves.size(); k++) {
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

bool Board::isStalemate(char kingcolor) {
    //1.双方均无法checkmate 单马/象单王对单王
    //2.无子可动
    if (Wpiececount == 1 && Bpiececount == 1) {
        return true;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == kingcolor) {
                vector<pair<int, int>> legalm = (*boardmap)[i][j]->legalMoves(*boardmap, i, j);
                if (legalm.size() > 0) {
                    return false;
                }
            }
        }
    }
    return true;
}



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
            newpiece = make_shared<King>(King(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W'));
            Wpiececount++;
            break;
        case 'Q':
            newpiece = make_shared<Queen>(Queen(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W'));
            Wpiececount++;
            break;
        case 'B':
            newpiece = make_shared<Bishop>(Bishop(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W'));
            Wpiececount++;
            break;
        case 'R':
            newpiece = make_shared<Rook>(Rook(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W'));
            Wpiececount++;
            break;
        case 'N':
            newpiece = make_shared<Knight>(Knight(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W'));
            Wpiececount++;
            break;
        case 'P':
            newpiece = make_shared<Pawn>(Pawn(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'W'));
            Wpiececount++;
            break;
        case 'k':
            Bkingcol = col;
            Bkingrow = row;
            newpiece = make_shared<King>(King(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B'));
            Bpiececount++;
            break;
        case 'q':
            newpiece = make_shared<Queen>(Queen(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B'));
            Bpiececount++;
            break;
        case 'b':
            newpiece = make_shared<Bishop>(Bishop(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B'));
            Bpiececount++;
            break;
        case 'r':
            newpiece = make_shared<Rook>(Rook(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B'));
            Bpiececount++;
            break;
        case 'n':
            newpiece = make_shared<Knight>(Knight(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B'));
            Bpiececount++;
            break;
        case 'p':
            newpiece = make_shared<Pawn>(Pawn(&Wkingrow, &Wkingcol, &Bkingrow, &Bkingcol, 'B'));
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
    this->torow = row;
    this->tocol = col;
    this->fromrow = -1;
    this->fromcol = -1;
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
        this->fromrow = row;
        this->fromcol = col;
        this->torow = -1;
        this->tocol = -1;
        return true;
    }
}

bool Board::setNextPlayer(char color) {
    if (color == 'W' || color == 'B') {
        currentPlayer = color;
        return true;
    }
    return false;
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
    this->fromrow = -1;
    this->fromcol = -1;
    this->torow = -1;
    this->tocol = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            (*boardmap)[i][j] = nullptr;
        }
    }
}


void Board::default_init() {
    currentPlayer = 'W';
    Bkingcol = 4;
    Bkingrow = 7;
    Wkingcol = 4;
    Wkingrow = 0;
    Bpiececount = 0;
    Wpiececount = 0;
    for (int row = 1; row <= 8; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            stringstream stream;
            stream << col;
            string s = stream.str();
            if ((row == 1) && ((col == 'a') || (col == 'h'))) {
                s += "1";
                addPiece('R', s);
            } else if ((row == 8) && ((col == 'a') || (col == 'h'))) {
                s += "8";
                addPiece('r', s);
            } else if ((row == 1) && ((col == 'b') || (col == 'g'))) {
                s += "1";
                addPiece('N', s);
            } else if ((row == 8) && ((col == 'b') || (col == 'g'))) {
                s += "8";
                addPiece('n', s);
            } else if ((row == 1) && ((col == 'c') || (col == 'f'))) {
                s += "1";
                addPiece('B', s);
            } else if ((row == 8) && ((col == 'c') || (col == 'f'))) {
                s += "8";
                addPiece('b', s);
            } else if (row == 1 && col == 'd') {
                s += "1";
                addPiece('Q', s);
            } else if (row == 8 && col == 'd') {
                s += "8";
                addPiece('q', s);
            } else if (row == 1 && col == 'e') {
                s += "1";
                addPiece('K', s);
            } else if (row == 8 && col == 'e') {
                s += "8";
                addPiece('k', s);
            } else if (row == 2) {
                s += "2";
                addPiece('P', s);
            } else if (row == 7) {
                s += "7";
                addPiece('p', s);
            }
        }
    }
}

void Board::PlayersInit(char w, char b) {
    switch (w) {
        case 'h':
            this->WPlayer = make_shared<Human>(Human(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '1':
            this->WPlayer = make_shared<Level1>(Level1(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '2':
            this->WPlayer = make_shared<Level2>(Level2(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '3':
            this->WPlayer = make_shared<Level3>(Level3(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '4':
            this->WPlayer = make_shared<Level4>(Level4(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
    }
    switch (b) {
        case 'h':
            this->BPlayer = make_shared<Human>(Human(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '1':
            this->BPlayer = make_shared<Level1>(Level1(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '2':
            this->BPlayer = make_shared<Level2>(Level2(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '3':
            this->BPlayer = make_shared<Level3>(Level3(&currentPlayer, &Wpiececount, &Bpiececount));
            break;
        case '4':
            this->BPlayer = make_shared<Level4>(Level4(&currentPlayer, &Wpiececount, &Bpiececount));
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
        this->castling = {{7, 3}, {7, 0}};
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'k' && abs(fromcol - tocol) == 2
               && tocol == 6) {
        //black king short castling
        (*boardmap)[7][5] = (*boardmap)[7][7];
        (*boardmap)[7][7] = nullptr;
        this->castling = {{7, 5}, {7, 7}};
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'K' && abs(fromcol - tocol) == 2
               && tocol == 2) {
        //white king long castling
        (*boardmap)[0][3] = (*boardmap)[0][0];
        (*boardmap)[0][0] = nullptr;
        this->castling = {{0, 3}, {0, 0}};
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'K' && abs(fromcol - tocol) == 2
               && tocol == 6) {
        //white king short castling
        (*boardmap)[0][5] = (*boardmap)[0][7];
        (*boardmap)[0][7] = nullptr;
        this->castling = {{0, 5}, {0, 7}};
    }


    //eliminate the pawn in the situation of en passant
    if ((*boardmap)[fromrow][fromcol]->type() == 'P' && torow == fromrow + 1 && tocol == fromcol + 1) {
        //move white upperright
        if ((*boardmap)[fromrow][fromcol + 1]->type() == 'p') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol + 1]);
            if (p->getEnpassant()) {
                Bpiececount--;
                (*boardmap)[fromrow][fromcol + 1] = nullptr;
                this->enpassent = {fromrow, fromcol+1};
            }
        }
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'P' && torow == fromrow + 1 && tocol == fromcol - 1) {
        //move white upperleft
        if ((*boardmap)[fromrow][fromcol - 1]->type() == 'p') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol - 1]);
            if (p->getEnpassant()) {
                Bpiececount--;
                (*boardmap)[fromrow][fromcol - 1] = nullptr;
                this->enpassent = {fromrow, fromcol-1};
            }
        }
    } else if ((*boardmap)[fromrow][fromcol]->type() == 'p' && torow == fromrow - 1 && tocol == fromcol + 1) {
        //move black upperright
        if ((*boardmap)[fromrow][fromcol + 1]->type() == 'P') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol + 1]);
            if (p->getEnpassant()) {
                Wpiececount--;
                (*boardmap)[fromrow][fromcol + 1] = nullptr;
                this->enpassent = {fromrow, fromcol+1};
            }
        }

    } else if ((*boardmap)[fromrow][fromcol]->type() == 'p' && torow == fromrow - 1 && tocol == fromcol - 1) {
        //move black upperleft
        if ((*boardmap)[fromrow][fromcol - 1]->type() == 'P') {
            shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[fromrow][fromcol - 1]);
            if (p->getEnpassant()) {
                Wpiececount--;
                (*boardmap)[fromrow][fromcol - 1] = nullptr;
                this->enpassent = {fromrow, fromcol-1};
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
                checkmate = true;
            }
        } else if (isStalemate(kingcolor)) {
            stalemate = true;
        }

        //change player, at the very end of the move
        if (currentPlayer == 'W') {
            currentPlayer = 'B';
        } else {
            currentPlayer = 'W';
        }
        this->fromcol = fromcol;
        this->fromrow = fromrow;
        this->torow = torow;
        this->tocol = tocol;
        this->print();
    }




    //if move happens, en passant will be no longer valid
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && ((*boardmap)[i][j]->type() == 'p'
                                      || (*boardmap)[i][j]->type() == 'P')) {
                shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[i][j]);
                if (p->getEnpassant()) {
                    p->setEnpassant(false);
                }
            }
        }
    }


    //make the pawn available to be eaten in the situation of enpassant after first move of two grids
    if ((*boardmap)[torow][tocol]->type() == 'p'
        || (*boardmap)[torow][tocol]->type() == 'P') {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[torow][tocol]);
        if (p->getHaventMoved()) {
            p->setHaventMoved(false);
            if (abs(torow - fromrow) == 2) {
                p->setEnpassant(true);
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
    notifyObservers();
}

char Board::getCurrentPlayer() {
    return currentPlayer;
}

void Board::clearCheck() {
    check = false;
    resign = false;
}


void Board::clearCheckStaleMate() {
    check = false;
    checkmate = false;
    stalemate = false;
    resign = false;
}

void Board::setResign () {
    this->resign = true;
}

bool Board::isResign() {
    return resign;
}

bool Board::ischeck() {
    return check;
}

bool Board::ischeckmate() {
    return checkmate;
}

bool Board::isstalemate() {
    return stalemate;
}

vector<pair<int, int>> Board::getInput() {
    pair<int, int> from = {fromrow, fromcol};
    pair<int, int> to = {torow, tocol};
    vector<pair<int, int>> a = {from, to};
    return a;
}

void Board::setInput() {
    fromrow = -1;
    fromcol = -1;
    torow = -1;
    tocol = -1;
}

void Board::setInit(bool b) {
    this->init = b;
}

bool Board::getInit() {
    return this->init;
}

pair<pair<int, int>, pair<int, int>> Board::getcastling() {
    return this->castling;
}

pair<int, int> Board::getenpassent() {
    return this->enpassent;
}

void Board::setcastling() {
    this->castling = {{-1, -1}, {-1, -1}};
}

void Board::setenpassent() {
    this->enpassent = {-1, -1};
}
