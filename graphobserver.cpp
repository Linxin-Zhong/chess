#include <iostream>
#include "graphobserver.h"
#include "window.h"
#include <string>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

GraphObserver::GraphObserver(Board *bd)
        : subject{bd} {
    shared_ptr<Xwindow> tmp = make_shared<Xwindow>(450, 500);
    tmp->fillRectangle(50, 0, 400, 400, Xwindow::White);
    tmp->fillRectangle(45, 400, 405, 5, Xwindow::Black);
    tmp->fillRectangle(45, 0, 5, 400, Xwindow::Black);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 0) {
                char c = 'a' + j;
                string str;
                stringstream stream;
                stream << c;
                str = stream.str();
                tmp->drawString((j + 1) * 50 + 25, 425, str);
            }
        }
        char c = '1' + i;
        string str;
        stringstream stream;
        stream << c;
        str = stream.str();
        tmp->drawString(25, (7 - i) * 50 + 25, str);
    }
    tmp->drawString(100, 475, "Please use command 'game' to start a game");
    tmp->drawString(100, 495, "or use 'setup' to enter the set up mode.");
    w = tmp;
    subject->attach(this);
}

GraphObserver::~GraphObserver() {
    subject->detach(this);
}

void GraphObserver::notify() {
    w->fillRectangle(0, 450, 475, 50, Xwindow::White); 
    char color = subject->getCurrentPlayer();
    if (subject->isResign()) {
        string info; 
        if (color == 'W') {
            info = "White wins!";
        } else {
            info = "Black wins!";
        }
        w->drawString(200, 475, info);
        return;
    }
    vector<pair<int, int>> a = subject->getInput();
    int fromrow = a[0].first;
    int fromcol = a[0].second;
    int torow = a[1].first;
    int tocol = a[1].second;
    if (subject->getInit()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::shared_ptr<Piece> p = (*subject->boardmap)[i][j];
                if (p == nullptr) {
                    continue;
                }
                string str;
                stringstream stream;
                stream << p->type();
                str = stream.str();
                w->drawString((j + 1) * 50 + 25, (7 - i) * 50 + 25, str);
            }
        }
        subject->setInit(false);
        return;
    }
    if (fromrow == -1 && fromcol == -1 && torow == -1 && tocol == -1) {
        return; 
    }
    if (fromrow == -1 && fromcol == -1) {
        if ((torow + tocol) % 2 == 0) {
            w->fillRectangle((tocol + 1) * 50, (7 - torow) * 50, 50, 50, Xwindow::White);
        } else {
            w->fillRectangle((tocol + 1) * 50, (7 - torow) * 50, 50, 50, Xwindow::Green); 
        }
        std::shared_ptr<Piece> p = (*subject->boardmap)[torow][tocol];
        string str;
        stringstream stream;
        stream << p->type();
        str = stream.str();
        w->drawString((tocol + 1) * 50 + 25, (7 - torow) * 50 + 25, str);
    } else if (torow == -1 && tocol == -1) {
        if ((fromrow + fromcol) % 2 == 0) {
            w->fillRectangle((fromcol + 1) * 50, (7 - fromrow) * 50, 50, 50, Xwindow::White);
        } else {
            w->fillRectangle((fromcol + 1) * 50, (7 - fromrow) * 50, 50, 50, Xwindow::Green); 
        }
    } else {
        std::shared_ptr<Piece> to= (*subject->boardmap)[torow][tocol];
        string str;
        stringstream stream;
        stream << to->type();
        str = stream.str();
        if ((fromrow + fromcol) % 2 == 0) {
            w->fillRectangle((fromcol + 1) * 50, (7 - fromrow) * 50, 50, 50, Xwindow::White);
        } else {
            w->fillRectangle((fromcol + 1) * 50, (7 - fromrow) * 50, 50, 50, Xwindow::Green); 
        }
        if ((torow + tocol) % 2 == 0) {
            w->fillRectangle((tocol + 1) * 50, (7 - torow) * 50, 50, 50, Xwindow::White);
        } else {
            w->fillRectangle((tocol + 1) * 50, (7 - torow) * 50, 50, 50, Xwindow::Green); 
        }
        w->drawString((tocol + 1) * 50 + 25, (7 - torow) * 50 + 25, str);
    }
    pair<int, int> enpassent = subject->getenpassent();
    if (enpassent.first != -1 && enpassent.second != -1) {
        int row = enpassent.first;
        int col = enpassent.second;
        if ((row + col) % 2 == 0) {
            w->fillRectangle((col + 1) * 50, (7 - row) * 50, 50, 50, Xwindow::White);
        } else {
            w->fillRectangle((col + 1) * 50, (7 - row) * 50, 50, 50, Xwindow::Green); 
        }
        subject->setenpassent(); 
    }
    pair<pair<int ,int >, pair<int, int>>castling = subject->getcastling();
    if (castling.first.first != -1 && castling.first.second != -1 && castling.second.second != -1 && castling.second.first != -1) {
        int row = castling.first.first;
        int col = castling.first.second;
        if ((row + col) % 2 == 0) {
            w->fillRectangle((col + 1) * 50, (7 - row) * 50, 50, 50, Xwindow::White);
        } else {
            w->fillRectangle((col + 1) * 50, (7 - row) * 50, 50, 50, Xwindow::Green); 
        }
        std::shared_ptr<Piece> tmp= (*subject->boardmap)[row][col];
        string str;
        stringstream stream;
        stream << tmp->type();
        str = stream.str();
        w->drawString((col + 1) * 50 + 25, (7 - row) * 50 + 25, str);
        row = castling.second.first;
        col = castling.second.second;
        if ((row + col) % 2 == 0) {
            w->fillRectangle((col + 1) * 50, (7 - row) * 50, 50, 50, Xwindow::White);
        } else {
            w->fillRectangle((col + 1) * 50, (7 - row) * 50, 50, 50, Xwindow::Green); 
        }
        subject->setcastling(); 
    }

    if (subject->isstalemate()) {
        w->drawString(200, 475, "Stalemate!");
        return;
    }
    if (subject->ischeckmate()) {
        string info; 
        if (color == 'W') {
            info = "Checkmate! White wins.";
        } else {
            info = "Checkmate! Black wins.";
        }
        w->drawString(200, 475, info);
        return;
    } 
    if (subject->ischeck()) {
        string info;
        if (color == 'W') {
        info = "White is in check.";
        } else {
        info = "Black is in check.";
        }
        w->drawString(200, 475, info);
        return;
    }
}

std::string to_string_precision(float a_value, float n = 1) {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}


void GraphObserver::grade(float W, float B) {
    w->fillRectangle(0, 0, 475, 500, Xwindow::White);
    w->drawString(100, 200, "Final Score:");
    string str;
    str = to_string_precision(W);
    w->drawString(100, 250, "White: " + str);
    str = to_string_precision(B);
    w->drawString(100, 300, "Black: " + str);
    w->drawString(100, 350, "Thank your for playing :) Game ended!");
}

void GraphObserver::clearGraph() {
    w->fillRectangle(0, 450, 475, 50, Xwindow::White); 
    w->fillRectangle(50, 0, 400, 400, Xwindow::White);
    w->drawString(150, 475, "checkerboard loading...");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                w->fillRectangle((j + 1) * 50, (7 - i) * 50, 50, 50, Xwindow::Green);
            }
        }
    }
    w->fillRectangle(0, 450, 475, 50, Xwindow::White); 
    w->drawString(150, 475, "checkerboard loading completed."); 
    w->fillRectangle(0, 450, 475, 50, Xwindow::White); 
}
