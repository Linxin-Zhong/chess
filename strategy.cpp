#include "strategy.h"


vector<pair<pair<int, int>, pair<int, int>>> Strategy::findIntersection(vector<pair<pair<int, int>, pair<int, int>>> v1,
                                                                        vector<pair<pair<int, int>, pair<int, int>>> v2) {
    vector<pair<pair<int, int>, pair<int, int>>> intersection;
    for (size_t i = 0; i < v1.size(); i++) {
        for (size_t j = 0; j < v2.size(); j++) {
            pair<pair<int, int>, pair<int, int>> move = v1[i];
            pair<pair<int, int>, pair<int, int>> move2 = v2[j];
            if (move == move2) {
                intersection.emplace_back(move);
            }
        }
    }
    return intersection;
}