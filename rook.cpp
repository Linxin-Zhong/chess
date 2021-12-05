#include "rook.h"

Rook::Rook(char color, std::vector<std::vector<std::shared_ptr<Piece>>> boardmap) : Piece(color, 5, boardmap) {}

bool Rook::check(int tocol, int torow, int kingcol, int kingrow) {

}
