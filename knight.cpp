#include "knight.h"

Knight::Knight(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap) : Piece(color, 3, boardmap) {}


bool Knight::check(int tocol, int torow, int kingcol, int kingrow) {

}