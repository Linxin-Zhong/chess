#include "level2.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


pair<pair<int, int>, pair<int, int>> Level2::generateMove(string input) {
    vector<pair<pair<int, int>, pair<int, int>>> legalmoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> legalmove = (*boardmap)[i][j]->legalMoves(i, j);
                for (size_t k = 0; k < legalmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {legalmove[k].first, legalmove[k].second}};
                    legalmoves.emplace_back(temp);
                }
            }
        }
    }

    vector<pair<pair<int, int>, pair<int, int>>> capmoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> capmove = (*boardmap)[i][j]->captureMoves(i, j);
                for (size_t k = 0; k < capmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                j},
                                                                 {capmove[k].first, capmove[k].second}};
                    capmoves.emplace_back(temp);
                }
            }
        }
    }

    vector<pair<pair<int, int>, pair<int, int>>> checkmoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> checkmove = (*boardmap)[i][j]->checkMoves(i, j);
                for (size_t k = 0; k < checkmove.size(); k++) {
                    pair<pair<int, int>, pair<int, int>> temp = {{i,                  j},
                                                                 {checkmove[k].first, checkmove[k].second}};
                    checkmoves.emplace_back(temp);
                }
            }
        }
    }

    vector<pair<pair<int, int>, pair<int, int>>> checkandcapmove = findIntersection(checkmoves, capmoves);
    vector<pair<pair<int, int>, pair<int, int>>> allmove;

    if (checkandcapmove.size() == 0) {
        if (checkmoves.size() == 0) {
            if (capmoves.size() == 0) {
                allmove = legalmoves;
            } else {
                allmove = capmoves;
            }
        } else {
            allmove = checkmoves;
        }
    } else {
        allmove = checkandcapmove;
    }

    int length = allmove.size();
    srand(time(NULL));
    int index = rand() % length;
    return allmove[index];
}