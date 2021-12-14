#include "pawn.h"

Pawn::Pawn(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
           char color) :
        Piece(Wkingrow, Wkingcol, Bkingrow, Bkingcol, color, 1) {}

bool Pawn::check(vector<vector<shared_ptr<Piece>>> &b, int torow, int tocol, int kingrow, int kingcol) {
    if (color == 'W') {
        if ((torow + 1 == kingrow) &&
            (tocol + 1 == kingcol || tocol - 1 == kingcol)) {
            return true;
        } else {
            return false;
        }
    } else {
        if ((torow - 1 == kingrow) &&
            (tocol + 1 == kingcol || tocol - 1 == kingcol)) {
            return true;
        } else {
            return false;
        }
    }

}

vector<pair<int, int>> Pawn::legalMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofLegalMoves;
    pair<int, int> temp;


    if (haventmoved) {
        //first move
        if ((r - 2) >= 0 && (r - 2) < 8 && color == 'B' && !(boardmap)[r - 2][c] && !(boardmap)[r - 1][c]) {
            temp = {r - 2, c};
            listofLegalMoves.emplace_back(temp);
        } else if ((r + 2) >= 0 && (r + 2) < 8 && color == 'W' && !(boardmap)[r + 2][c] && !(boardmap)[r + 1][c]) {
            temp = {r + 2, c};
            listofLegalMoves.emplace_back(temp);
        }
    }

    //normal move
    if ((r - 1) >= 0 && (r - 1) < 8 && color == 'B' &&
        (!(boardmap)[r - 1][c])) {
        temp = {r - 1, c};
        listofLegalMoves.emplace_back(temp);
    } else if ((r + 1) >= 0 && (r + 1) < 8 && color == 'W' &&
               (!(boardmap)[r + 1][c])) {
        temp = {r + 1, c};
        listofLegalMoves.emplace_back(temp);
    }

    //normal capture
    if ((r - 1) >= 0 && (r - 1) < 8 && (c - 1) >= 0 && (c - 1) < 8 &&
        (color == 'B' && (boardmap)[r - 1][c - 1] && (boardmap)[r - 1][c - 1]->getColor() != color)) {
        temp = {r - 1, c - 1};
        listofLegalMoves.emplace_back(temp);
    }
    if ((r - 1) >= 0 && (r - 1) < 8 && (c + 1) >= 0 && (c + 1) < 8 &&
        (color == 'B' && (boardmap)[r - 1][c + 1] && (boardmap)[r - 1][c + 1]->getColor() != color)) {
        temp = {r - 1, c + 1};
        listofLegalMoves.emplace_back(temp);
    }
    if ((r + 1) >= 0 && (r + 1) < 8 && (c - 1) >= 0 && (c - 1) < 8 &&
        color == 'W' && (boardmap)[r + 1][c - 1] && (boardmap)[r + 1][c - 1]->getColor() != color) {
        temp = {r + 1, c - 1};
        listofLegalMoves.emplace_back(temp);
    }
    if ((r + 1) >= 0 && (r + 1) < 8 && (c + 1) >= 0 && (c + 1) < 8 &&
        color == 'W' && (boardmap)[r + 1][c + 1] && (boardmap)[r + 1][c + 1]->getColor() != color) {
        temp = {r + 1, c + 1};
        listofLegalMoves.emplace_back(temp);
    }

    //en passant
    if ((c + 1) >= 0 && (c + 1) < 8 && (boardmap)[r][c + 1] && (boardmap)[r][c + 1]->getColor() != this->color
        && ((boardmap)[r][c + 1]->type() == 'p' || (boardmap)[r][c + 1]->type() == 'P')) {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((boardmap)[r][c + 1]);
        if (this->color == 'W' && p->getEnpassant() && !(boardmap)[r + 1][c + 1]) {
            temp = {r + 1, c + 1};
            listofLegalMoves.emplace_back(temp);
        } else if (this->color == 'B' && p->getEnpassant() && !(boardmap)[r - 1][c + 1]) {
            temp = {r - 1, c + 1};
            listofLegalMoves.emplace_back(temp);
        }
    }

    if ((c - 1) >= 0 && (c - 1) < 8 && (boardmap)[r][c - 1] && (boardmap)[r][c - 1]->getColor() != this->color
        && ((boardmap)[r][c - 1]->type() == 'p' || (boardmap)[r][c - 1]->type() == 'P')) {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((boardmap)[r][c - 1]);
        if (this->color == 'W' && p->getEnpassant() && !(boardmap)[r + 1][c - 1]) {
            temp = {r + 1, c - 1};
            listofLegalMoves.emplace_back(temp);
        } else if (this->color == 'B' && p->getEnpassant() && !(boardmap)[r - 1][c - 1]) {
            temp = {r - 1, c - 1};
            listofLegalMoves.emplace_back(temp);
        }
    }

    int kingrow, kingcol;
    if (color == 'W') {
        kingrow = *Wkingrow;
        kingcol = *Wkingcol;
    } else {
        kingrow = *Bkingrow;
        kingcol = *Bkingcol;
    }

    int checkcol, checkrow;

    vector<pair<int, int>> movesSavingKing;
    for (size_t i = 0; i < listofLegalMoves.size(); i++) {
        //check if making that move would eliminate the check on king
        vector<vector<shared_ptr<Piece>>> newboard;
        boardcopy2((boardmap), newboard);
        int fromrow, fromcol, torow, tocol;
        fromrow = r;
        fromcol = c;
        torow = listofLegalMoves[i].first;
        tocol = listofLegalMoves[i].second;
        newboard[torow][tocol] = newboard[fromrow][fromcol];
        newboard[fromrow][fromcol] = nullptr;
        if (!isCheck(newboard, color, kingrow, kingcol, &checkrow, &checkcol)) {
            movesSavingKing.emplace_back(listofLegalMoves[i]);
        }
    }
    return movesSavingKing;
}

vector<pair<int, int>> Pawn::captureMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofCaptureMoves;
    vector<pair<int, int>> legalMoves = this->legalMoves(boardmap, r, c);
    for (size_t i = 0; i < legalMoves.size(); i++) {
        if ((boardmap)[legalMoves[i].first][legalMoves[i].second]) {
            listofCaptureMoves.emplace_back(legalMoves[i]);
        }
    }
    return listofCaptureMoves;
}

vector<pair<int, int>> Pawn::avoidMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listOfAvoidMoves;
    // check if the current piece is under attack
    int checkrow, checkcol;
    if (!(boardmap)[r][c]->isCheck((boardmap), this->color, r, c, &checkrow, &checkcol)) {
        return listOfAvoidMoves;
    }

    vector<pair<int, int>> legalmoves = (boardmap)[r][c]->legalMoves(boardmap, r, c);
    for (size_t i = 0; i < legalmoves.size(); i++) {
        int newrow = legalmoves[i].first;
        int newcol = legalmoves[i].second;
        vector<vector<shared_ptr<Piece>>> boardAfterMove;
        boardcopy2(boardmap, boardAfterMove);
        boardAfterMove[newrow][newcol] = boardAfterMove[r][c];
        boardAfterMove[r][c] = nullptr;
        int checkrow, checkcol;
        if (!isCheck(boardAfterMove, color, newrow, newcol, &checkrow, &checkcol)) {
            pair<int, int> temp = {newrow, newcol};
            listOfAvoidMoves.emplace_back(temp);
        }
    }
    return listOfAvoidMoves;
}

vector<pair<int, int>> Pawn::checkMoves(vector<vector<shared_ptr<Piece>>> &boardmap, int r, int c) {
    vector<pair<int, int>> listofchecks;
    vector<pair<int, int>> legalmoves = (boardmap)[r][c]->legalMoves(boardmap, r, c);

    for (size_t i = 0; i < legalmoves.size(); i++) {
        int newrow = legalmoves[i].first;
        int newcol = legalmoves[i].second;
        if ((boardmap)[newrow][newcol] && (boardmap)[newrow][newcol]->getColor() != color &&
            ((boardmap)[newrow][newcol]->type() == 'k' || (boardmap)[newrow][newcol]->type() == 'K')) {
            pair<int, int> temp = {newrow, newcol};
            listofchecks.emplace_back(temp);
        }
    }
    return listofchecks;
}

void Pawn::setHaventMoved(bool b) {
    haventmoved = b;
}

void Pawn::setEnpassant(bool b) {
    Enpassant = b;
}

bool Pawn::getHaventMoved() {
    return haventmoved;
}

bool Pawn::getEnpassant() {
    return Enpassant;
}
