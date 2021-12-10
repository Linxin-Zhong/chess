#include "strategy.h"

vector<pair<int, int>> Strategy::findIntersection(vector<pair<int, int>> v1, vector<pair<int, int>> v2) {
    vector<pair<int, int>> intersection;
    for (int i = 0; i < v1.size(); ++i) {
        pair<int, int> temp = {v1[i].first, v1[i].second};
        if (find(v2.begin(), v2.end(), temp) != v2.end()) {
            intersection.emplace_back(temp);
        }
    }
    return intersection;
}