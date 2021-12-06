#include "king.h"

King::King(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap) : Piece(color, 10, boardmap) {}

bool King::check(int torow, int tocol, int kingrow, int kingcol) {
    return false;
}