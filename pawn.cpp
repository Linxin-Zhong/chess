#include "pawn.h"

Pawn::Pawn(int *Wkingrow, int *Wkingcol, int *Bkingrow, int *Bkingcol,
           char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) :
        Piece(Wkingrow, Wkingcol, Bkingrow, Bkingcol, color, 9, boardmap) {}

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

vector<pair<int, int>> Pawn::legalMoves(int r, int c) {
    vector<pair<int, int>> listofLegalMoves;
    pair<int, int> temp;


    if (haventmoved) {
        //first move
        if ((r - 2) >= 0 && (r - 2) < 8 && color == 'B' &&
            !(*boardmap)[r - 2][c]) {
            temp = {r - 2, c};
            listofLegalMoves.emplace_back(temp);
        } else if ((r + 2) >= 0 && (r + 2) < 8 && color == 'W' &&
                   !(*boardmap)[r + 2][c]) {
            temp = {r + 2, c};
            listofLegalMoves.emplace_back(temp);
        }
    }

    //normal move
    if ((r - 1) >= 0 && (r - 1) < 8 && color == 'B' &&
        (!(*boardmap)[r - 1][c])) {
        temp = {r - 1, c};
        listofLegalMoves.emplace_back(temp);
    } else if ((r + 1) >= 0 && (r + 1) < 8 && color == 'W' &&
               (!(*boardmap)[r + 1][c])) {
        temp = {r + 1, c};
        listofLegalMoves.emplace_back(temp);
    }

    //normal capture
    if ((r - 1) >= 0 && (r - 1) < 8 && (c - 1) >= 0 && (c - 1) < 8 &&
        (color == 'B' && (*boardmap)[r - 1][c - 1] && (*boardmap)[r - 1][c - 1]->getColor() != color)) {
        temp = {r - 1, c - 1};
        listofLegalMoves.emplace_back(temp);
    }
    if ((r - 1) >= 0 && (r - 1) < 8 && (c + 1) >= 0 && (c + 1) < 8 &&
        (color == 'B' && (*boardmap)[r - 1][c + 1] && (*boardmap)[r - 1][c + 1]->getColor() != color)) {
        temp = {r - 1, c + 1};
        listofLegalMoves.emplace_back(temp);
    }
    if ((r + 1) >= 0 && (r + 1) < 8 && (c - 1) >= 0 && (c - 1) < 8 &&
        color == 'W' && (*boardmap)[r + 1][c - 1] && (*boardmap)[r + 1][c - 1]->getColor() != color) {
        temp = {r + 1, c - 1};
        listofLegalMoves.emplace_back(temp);
    }
    if ((r + 1) >= 0 && (r + 1) < 8 && (c + 1) >= 0 && (c + 1) < 8 &&
        color == 'W' && (*boardmap)[r + 1][c + 1] && (*boardmap)[r + 1][c + 1]->getColor() != color) {
        temp = {r + 1, c + 1};
        listofLegalMoves.emplace_back(temp);
    }

    //en passant
    if ((c + 1) >= 0 && (c + 1) < 8 && (*boardmap)[r][c + 1] && (*boardmap)[r][c + 1]->getColor() != this->color
        && ((*boardmap)[r][c + 1]->type() == 'p' || (*boardmap)[r][c + 1]->type() == 'P')) {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[r][c + 1]);
        if (this->color == 'W' && p->getEnpassant() && !(*boardmap)[r + 1][c + 1]) {
            temp = {r + 1, c + 1};
            listofLegalMoves.emplace_back(temp);
        } else if (this->color == 'B' && p->getEnpassant() && !(*boardmap)[r - 1][c + 1]) {
            temp = {r - 1, c + 1};
            listofLegalMoves.emplace_back(temp);
        }
    }

    if ((c - 1) >= 0 && (c - 1) < 8 && (*boardmap)[r][c - 1] && (*boardmap)[r][c - 1]->getColor() != this->color
        && ((*boardmap)[r][c - 1]->type() == 'p' || (*boardmap)[r][c - 1]->type() == 'P')) {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[r][c - 1]);
        if (this->color == 'W' && p->getEnpassant() && !(*boardmap)[r + 1][c - 1]) {
            temp = {r + 1, c - 1};
            listofLegalMoves.emplace_back(temp);
        } else if (this->color == 'B' && p->getEnpassant() && !(*boardmap)[r - 1][c - 1]) {
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

    bool kinginCheck = false;

    if (isCheck((*boardmap), color, kingrow, kingcol, &checkrow, &checkcol)) {
        kinginCheck = true;
    }

    if (kinginCheck) {
        vector<pair<int, int>> movesSavingKing;
        for (int i = 0; i < listofLegalMoves.size(); i++) {
            //check if making that move would eliminate the check on king
            vector<vector<shared_ptr<Piece>>> newboard;
            boardcopy2((*boardmap), newboard);
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

    return listofLegalMoves;
}

vector<pair<int, int>> Pawn::captureMoves(int r, int c) {
    vector<pair<int, int>> listofCaptureMoves;
    pair<int, int> temp;

    if ((r - 1) >= 0 && (r - 1) < 8 && (c - 1) >= 0 && (c - 1) < 8 &&
        (color == 'B' && (*boardmap)[r - 1][c - 1] && (*boardmap)[r - 1][c - 1]->getColor() != color)) {
        temp = {r - 1, c - 1};
        listofCaptureMoves.emplace_back(temp);
    }
    if ((r - 1) >= 0 && (r - 1) < 8 && (c + 1) >= 0 && (c + 1) < 8 &&
        (color == 'B' && (*boardmap)[r - 1][c + 1] && (*boardmap)[r - 1][c + 1]->getColor() != color)) {
        temp = {r - 1, c + 1};
        listofCaptureMoves.emplace_back(temp);
    }
    if ((r + 1) >= 0 && (r + 1) < 8 && (c - 1) >= 0 && (c - 1) < 8 &&
        color == 'W' && (*boardmap)[r + 1][c - 1] && (*boardmap)[r + 1][c - 1]->getColor() != color) {
        temp = {r + 1, c - 1};
        listofCaptureMoves.emplace_back(temp);
    }
    if ((r + 1) >= 0 && (r + 1) < 8 && (c + 1) >= 0 && (c + 1) < 8 &&
        color == 'W' && (*boardmap)[r + 1][c + 1] && (*boardmap)[r + 1][c + 1]->getColor() != color) {
        temp = {r + 1, c + 1};
        listofCaptureMoves.emplace_back(temp);
    }

    //en passant
    if ((c + 1) >= 0 && (c + 1) < 8 && (*boardmap)[r][c + 1] && (*boardmap)[r][c + 1]->getColor() != this->color
        && ((*boardmap)[r][c + 1]->type() == 'p' || (*boardmap)[r][c + 1]->type() == 'P')) {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[r][c + 1]);
        if (this->color == 'W' && p->getEnpassant() && !(*boardmap)[r + 1][c + 1]) {
            temp = {r + 1, c + 1};
            listofCaptureMoves.emplace_back(temp);
        } else if (this->color == 'B' && p->getEnpassant() && !(*boardmap)[r - 1][c + 1]) {
            temp = {r - 1, c + 1};
            listofCaptureMoves.emplace_back(temp);
        }
    }

    if ((c - 1) >= 0 && (c - 1) < 8 && (*boardmap)[r][c - 1] && (*boardmap)[r][c - 1]->getColor() != this->color
        && ((*boardmap)[r][c - 1]->type() == 'p' || (*boardmap)[r][c - 1]->type() == 'P')) {
        shared_ptr<Pawn> p = dynamic_pointer_cast<Pawn>((*boardmap)[r][c - 1]);
        if (this->color == 'W' && p->getEnpassant() && !(*boardmap)[r + 1][c - 1]) {
            temp = {r + 1, c - 1};
            listofCaptureMoves.emplace_back(temp);
        } else if (this->color == 'B' && p->getEnpassant() && !(*boardmap)[r - 1][c - 1]) {
            temp = {r - 1, c - 1};
            listofCaptureMoves.emplace_back(temp);
        }
    }

    return listofCaptureMoves;
}

vector<pair<int, int>> Pawn::avoidMoves(int r, int c) {
    vector<pair<int, int>> a;
    return a;
}

vector<pair<int, int>> Pawn::checkMoves(int r, int c) {
    vector<pair<int, int>> a;
    return a;
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
