#include "level3.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

pair<pair<int, int>, pair<int, int>> Level3::generateMove(vector<vector<shared_ptr<Piece>>> &boardmap, string input) {
    vector<pair<pair<int, int>, pair<int, int>>> legalmoves;
    vector<pair<pair<int, int>, pair<int, int>>> capmoves;
    vector<pair<pair<int, int>, pair<int, int>>> checkmoves;
    vector<pair<pair<int, int>, pair<int, int>>> avoidmoves;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((boardmap)[i][j] && (boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> legalmove = (boardmap)[i][j]->legalMoves(boardmap, i, j);
                for (size_t k = 0; k < legalmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {legalmove[k].first, legalmove[k].second}};
                    legalmoves.emplace_back(temp);
                }

                vector<pair<int, int>> capmove = (boardmap)[i][j]->captureMoves(boardmap, i, j);
                for (size_t k = 0; k < capmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                j},
                                                                 {capmove[k].first, capmove[k].second}};
                    capmoves.emplace_back(temp);
                }

                vector<pair<int, int>> checkmove = (boardmap)[i][j]->checkMoves(boardmap, i, j);
                for (size_t k = 0; k < checkmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {checkmove[k].first, checkmove[k].second}};
                    checkmoves.emplace_back(temp);
                }

                vector<pair<int, int>> avoidmove = (boardmap)[i][j]->avoidMoves(boardmap, i, j);
                for (size_t k = 0; k < avoidmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {avoidmove[k].first, avoidmove[k].second}};
                    avoidmoves.emplace_back(temp);
                }
            }


        }
    }


    vector<pair<pair<int, int>, pair<int, int>>> checkandcapmove = findIntersection(checkmoves, capmoves);
    vector<pair<pair<int, int>, pair<int, int>>> checkandavoidmove = findIntersection(checkmoves, avoidmoves);
    vector<pair<pair<int, int>, pair<int, int>>> capandavoidmove = findIntersection(avoidmoves, capmoves);
    vector<pair<pair<int, int>, pair<int, int>>> threemove = findIntersection(checkandcapmove, checkandavoidmove);

    vector<pair<pair<int, int>, pair<int, int>>> allmove;
    if (threemove.size() == 0) {
        if (checkandcapmove.size() == 0 && checkandavoidmove.size() == 0) {
            if (capandavoidmove.size() == 0) {
                if (checkmoves.size() == 0) {
                    if (avoidmoves.size() == 0 && capmoves.size() == 0) {
                        allmove = legalmoves;
                    } else {
                        allmove.insert(allmove.end(), avoidmoves.begin(), avoidmoves.end());
                        allmove.insert(allmove.end(), capmoves.begin(), capmoves.end());
                    }
                } else {
                    allmove = checkmoves;
                }
            } else {
                allmove = capandavoidmove;
            }
        } else {
            allmove.insert(allmove.end(), checkandcapmove.begin(), checkandcapmove.end());
            allmove.insert(allmove.end(), checkandavoidmove.begin(), checkandavoidmove.end());
        }
    } else {
        allmove = threemove;
    }

    int length = allmove.size();
    srand(time(NULL));
    int index = rand() % length;
    return allmove[index];
}
