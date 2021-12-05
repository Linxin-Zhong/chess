#include "queen.h"

Queen::Queen(char color, std::vector<std::vector<std::shared_ptr<Piece>>> boardmap) : Piece(color, 9, boardmap) {}

bool Queen::check(int tocol, int torow, int kingcol, int kingrow) {

}