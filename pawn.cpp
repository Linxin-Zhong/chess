#include "pawn.h"

Pawn::Pawn(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) : Piece(color, 1,
                                                                                                      boardmap) {}

bool Pawn::check(int torow, int tocol, int kingrow, int kingcol) {
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

pair<int, int> Pawn::legalMove(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
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