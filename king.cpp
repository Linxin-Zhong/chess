#include "king.h"

King::King(char color, std::vector<std::vector<std::shared_ptr<Piece>>> boardmap) : Piece(color, 10, boardmap) {}

bool King::check(int tocol, int torow, int kingcol, int kingrow) {
    return false;
}