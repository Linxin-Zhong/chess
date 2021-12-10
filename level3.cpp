#include "level3.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

pair<pair<int, int>, pair<int, int>> Level3::generateMove(string input) {
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

    vector<pair<int, int>> avoidmoveto, avoidmovefrom;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> avoidmoves = (*boardmap)[i][j]->avoidMoves(i, j);
                for (int k = 0; k < avoidmoves.size(); k++) {
                    pair<int, int> temp = {i, j};
                    avoidmovefrom.emplace_back(temp);
                }
                avoidmoveto.insert(avoidmoveto.end(), avoidmoves.begin(), avoidmoves.end());
            }
        }
    }

    vector<pair<int, int>> checkandcapmoveto = findIntersection(checkmoveto, capmoveto);
    vector<pair<int, int>> checkandcapmovefrom = findIntersection(checkmovefrom, capmovefrom);
    vector<pair<int, int>> checkandavoidmoveto = findIntersection(checkmoveto, avoidmoveto);
    vector<pair<int, int>> checkandavoidmovefrom = findIntersection(checkmovefrom, avoidmovefrom);
    vector<pair<int, int>> capandavoidmoveto = findIntersection(capmoveto, avoidmoveto);
    vector<pair<int, int>> capandavoidmovefrom = findIntersection(capmovefrom, avoidmovefrom);
    vector<pair<int, int>> threemoveto = findIntersection(checkandcapmoveto, checkandavoidmoveto);
    vector<pair<int, int>> threemovefrom = findIntersection(checkandcapmovefrom, checkandavoidmovefrom);

    vector<pair<int, int>> allmovefrom, allmoveto;
    if (threemovefrom.size() == 0) {
        if (checkandcapmoveto.size() == 0 && checkandavoidmoveto.size() == 0) {
            if (capandavoidmoveto.size() == 0) {
                if (checkmoveto.size() == 0) {
                    if (avoidmoveto.size() == 0 && capmoveto.size() == 0) {
                        allmovefrom = legalmovefrom;
                        allmoveto = legalmoveto;
                    } else {
                        allmovefrom.insert(allmovefrom.end(), avoidmovefrom.begin(), avoidmovefrom.end());
                        allmovefrom.insert(allmovefrom.end(), capmovefrom.begin(), capmovefrom.end());
                        allmoveto.insert(allmoveto.end(), avoidmoveto.begin(), avoidmoveto.end());
                        allmoveto.insert(allmoveto.end(), capmoveto.begin(), capmoveto.end());
                    }
                } else {
                    allmovefrom = checkmovefrom;
                    allmoveto = checkmoveto;
                }
            } else {
                allmovefrom = capandavoidmovefrom;
                allmoveto = capandavoidmoveto;
            }
        } else {
            allmovefrom.insert(allmovefrom.end(), checkandcapmovefrom.begin(), checkandcapmovefrom.end());
            allmovefrom.insert(allmovefrom.end(), checkandavoidmovefrom.begin(), checkandavoidmovefrom.end());
            allmoveto.insert(allmoveto.end(), checkandcapmoveto.begin(), checkandcapmoveto.end());
            allmoveto.insert(allmoveto.end(), checkandavoidmoveto.begin(), checkandavoidmoveto.end());
        }
    } else {
        allmovefrom = threemovefrom;
        allmoveto = threemoveto;
    }
    
    int length = allmoveto.size();
    srand(time(NULL));
    int index = rand() % length;
    return {{allmovefrom[index].first, allmovefrom[index].second},
            {allmoveto[index].first,   allmoveto[index].second}};
}
