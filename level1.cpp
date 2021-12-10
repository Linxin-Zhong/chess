#include "level1.h"
#include <string>
#include <time.h>

using namespace std;

pair<pair<int, int>, pair<int, int>> Level1::generateMove(string input) {

    vector<pair<int, int>> allmoveto;

    vector<pair<int, int>> allmovefrom;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*boardmap)[i][j] && (*boardmap)[i][j]->getColor() == *currentPlayer) {
                vector<pair<int, int>> legalmoves = (*boardmap)[i][j]->legalMoves(i, j);
                for (int k = 0; k < legalmoves.size(); k++) {
                    pair<int, int> temp = {i, j};
                    allmovefrom.emplace_back(temp);
                }
                allmoveto.insert(allmoveto.end(), legalmoves.begin(), legalmoves.end());
            }
        }
    }

    int length = allmoveto.size();
    srand(time(NULL));
    int index = rand() % length;
    return {{allmovefrom[index].first, allmovefrom[index].second},
            {allmoveto[index].first,   allmoveto[index].second}};

}
