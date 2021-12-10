#include "level2.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


pair<pair<int, int>, pair<int, int>> Level2::generateMove(string input) {
    vector<pair<int, int>> legalmoveto, legalmovefrom;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> legalmoves = (*boardmap)[i][j]->legalMoves(i, j);
                for (int k = 0; k < legalmoves.size(); k++) {
                    pair<int, int> temp = {i, j};
                    legalmovefrom.emplace_back(temp);
                }
                legalmoveto.insert(legalmoveto.end(), legalmoves.begin(), legalmoves.end());
            }
        }
    }

    vector<pair<int, int>> capmoveto, capmovefrom;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> captures = (*boardmap)[i][j]->captureMoves(i, j);
                for (int k = 0; k < captures.size(); k++) {
                    pair<int, int> temp = {i, j};
                    capmovefrom.emplace_back(temp);
                }
                capmoveto.insert(capmoveto.end(), captures.begin(), captures.end());
            }
        }
    }

    vector<pair<int, int>> checkmoveto, checkmovefrom;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> checks = (*boardmap)[i][j]->checkMoves(i, j);
                for (int k = 0; k < checks.size(); k++) {
                    pair<int, int> temp = {i, j};
                    checkmovefrom.emplace_back(temp);
                }
                checkmoveto.insert(checkmoveto.end(), checks.begin(), checks.end());
            }
        }
    }

    vector<pair<int, int>> checkandcapmoveto = findIntersection(checkmoveto, capmoveto);
    vector<pair<int, int>> checkandcapmovefrom = findIntersection(checkmovefrom, capmovefrom);
    vector<pair<int, int>> allmovefrom, allmoveto;

    if (checkandcapmoveto.size() == 0) {
        if (checkmoveto.size() == 0) {
            if (capmoveto.size() == 0) {
                allmovefrom = legalmovefrom;
                allmoveto = legalmoveto;
            } else {
                allmovefrom = capmovefrom;
                allmoveto = capmoveto;
            }
        } else {
            allmovefrom = checkmovefrom;
            allmoveto = checkmoveto;
        }
    } else {
        allmovefrom = checkandcapmovefrom;
        allmovefrom = checkandcapmoveto;
    }

    int length = allmoveto.size();
    srand(time(NULL));
    int index = rand() % length;
    return {{allmovefrom[index].first, allmovefrom[index].second},
            {allmoveto[index].first,   allmoveto[index].second}};
}