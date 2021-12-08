#include "king.h"

King::King(char color, std::vector<std::vector<std::shared_ptr<Piece>>> &boardmap) : Piece(color, 10, boardmap) {}

bool King::check(int torow, int tocol, int kingrow, int kingcol) {
    return false;
}

pair<int, int> King::legalMove(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> King::capture(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> King::avoid(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> King::checks(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}