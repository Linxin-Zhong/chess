#include "pawn.h"

Pawn::Pawn(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap) : Piece(color, 1, boardmap) {}

bool Pawn::check(int tocol, int torow, int kingcol, int kingrow) {
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