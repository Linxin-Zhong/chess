#include "knight.h"

Knight::Knight(char color, shared_ptr<std::vector<std::vector<std::shared_ptr<Piece>>>> boardmap) : Piece(color, 3,
                                                                                                          boardmap) {}


bool Knight::check(int torow, int tocol, int kingrow, int kingcol) {
    int w = abs(kingcol - tocol);
    int h = abs(kingrow - torow);
    if ((w == 2 && h == 1) || (w == 1 && h == 2)) {
        return true;
    } else {
        return false;
    }
}


pair<int, int> Knight::legalMove(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Knight::capture(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Knight::avoid(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}

pair<int, int> Knight::checks(int r, int c) {
    pair<int, int> a = {0, 0};
    return a;
}