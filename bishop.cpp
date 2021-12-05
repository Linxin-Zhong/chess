#include "bishop.h"

Bishop::Bishop(char color, std::vector<std::vector<std::shared_ptr<Piece>>> boardmap) : Piece(color, 3, boardmap) {}

bool Bishop::check(int tocol, int torow, int kingcol, int kingrow) {

}