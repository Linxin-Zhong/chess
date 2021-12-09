//
// Created by Lola Zhong on 2021-11-28.
//

#include "human.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

pair<int, int> Human::generateMove(string input) {
    stringstream ss(input);
    string command;
    string movefrom;
    string moveto;
    ss >> command;
    ss >> movefrom;
    ss >> moveto;
    int fromcol = movefrom[0] - 'a';
    int fromrow = movefrom[1] - '1';
    int tocol = moveto[0] - 'a';
    int torow = moveto[1] - '1';

    vector<pair<int, int>> legalmoves = (*boardmap)[fromrow][fromcol]->legalMoves(fromrow, fromcol);
    pair<int, int> wantmove = {torow, tocol};
    if (find(legalmoves.begin(), legalmoves.end(), wantmove) != legalmoves.end()) {
        return wantmove;
    } else {
        cout << "invalid move! Please try again" << endl;
        return {-1, -1};
    }
}
