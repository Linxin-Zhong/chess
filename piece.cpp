#include "piece.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "board.h"

Piece::Piece(char color, int value, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) : color(
        color),
                                                                                                             value(value),
                                                                                                             boardmap(boardmap) {}


char Piece::type() {
    if (this == nullptr) {
        return '-';
    }
    if (dynamic_cast<Rook *>(this) != nullptr) {
        Rook *r = dynamic_cast<Rook *>(this);
        if (r->color == 'B') {
            return 'r';
        } else {
            return 'R';
        }
    } else if (dynamic_cast<Queen *>(this) != nullptr) {
        Queen *q = dynamic_cast<Queen *>(this);
        if (q->color == 'B') {
            return 'q';
        } else {
            return 'Q';
        }
    } else if (dynamic_cast<King *>(this) != nullptr) {
        King *k = dynamic_cast<King *>(this);
        if (k->color == 'B') {
            return 'k';
        } else {
            return 'K';
        }
    } else if (dynamic_cast<Pawn *>(this) != nullptr) {
        Pawn *p = dynamic_cast<Pawn *>(this);
        if (p->color == 'B') {
            return 'p';
        } else {
            return 'P';
        }
    } else if (dynamic_cast<Knight *>(this) != nullptr) {
        Knight *p = dynamic_cast<Knight *>(this);
        if (p->color == 'B') {
            return 'n';
        } else {
            return 'N';
        }
    } else if (dynamic_cast<Bishop *>(this) != nullptr) {
        Bishop *b = dynamic_cast<Bishop *>(this);
        if (b->color == 'B') {
            return 'b';
        } else {
            return 'B';
        }
    }
}

char Piece::getColor() {
     return color;
}


bool Piece::isCheck(vector<vector<shared_ptr<Piece>>> &b, char kingcolor, int kingrow,
                    int kingcol, int *checkrow, int *checkcol) {
    *checkcol = -1;
    *checkrow = -1;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (b[r][c] && b[r][c]->check(r, c, kingrow, kingcol)) {
                if (b[r][c]->getColor() != kingcolor) {
                    *checkrow = r;
                    *checkcol = c;
                    return true;
                }
            }
        }
    }
    return false;
}