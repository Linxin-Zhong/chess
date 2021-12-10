//
// Created by Lola Zhong on 2021-11-28.
//

#include "human.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

pair<pair<int, int>, pair<int, int>> Human::generateMove(string input) {
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

    if ((*boardmap)[fromrow][fromcol]->getColor() != *currentPlayer) {
        cout << "This is not the turn of this piece you want to move, plz try again:)" << endl;
        return {{-1, -1},
                {-1, -1}};
    }

    vector<pair<int, int>> legalmoves = (*boardmap)[fromrow][fromcol]->legalMoves(fromrow, fromcol);
    pair<pair<int, int>, pair<int, int>> wantmove = {{fromrow, fromcol},
                                                     {torow,   tocol}};
    pair<int, int> wantmoveto = {torow, tocol};
    if (find(legalmoves.begin(), legalmoves.end(), wantmoveto) != legalmoves.end()) {
        return wantmove;
    } else {
        cout << "invalid move! Please try again" << endl;
        return {{-1, -1},
                {-1, -1}};
    }
}
