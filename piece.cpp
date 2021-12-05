#include "piece.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "board.h"

Piece::Piece(char color, int value) : color(color), value(value) {}

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