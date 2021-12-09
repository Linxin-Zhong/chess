#include "pawn.h"

Pawn::Pawn(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) : Piece(color, 1,
                                                                                                      boardmap) {}

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
            (!(*boardmap)[r - 2][c] || (*boardmap)[r - 2][c]->getColor() != color)) {
            temp = {r - 2, c};
            listofLegalMoves.emplace_back(temp);
        } else if ((r + 2) >= 0 && (r + 2) < 8 && color == 'W' &&
                   (!(*boardmap)[r + 2][c] || (*boardmap)[r + 2][c]->getColor() != color)) {
            temp = {r + 2, c};
            listofLegalMoves.emplace_back(temp);
        }
    }

    //normal move
    if ((r - 1) >= 0 && (r - 1) < 8 && color == 'B' &&
        (!(*boardmap)[r - 1][c] || (*boardmap)[r - 1][c]->getColor() != color)) {
        temp = {r - 1, c};
        listofLegalMoves.emplace_back(temp);
    } else if ((r + 1) >= 0 && (r + 1) < 8 && color == 'W' &&
               (!(*boardmap)[r + 1][c] || (*boardmap)[r + 1][c]->getColor() != color)) {
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

    return listofLegalMoves;
}

pair<int, int> Pawn::capture(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Pawn::avoid(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Pawn::checks(int r, int c) {
    pair<int, int> a = {0, 0};
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