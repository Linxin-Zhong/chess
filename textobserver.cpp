#include <iostream>
#include "textobserver.h"
#include <iostream>
#include "textobserver.h"

using namespace std;

TextObserver::TextObserver(Board *bd)
        : subject{bd} {
    subject->attach(this);
}

TextObserver::~TextObserver() {
    subject->detach(this);
}

void TextObserver::notify() {
    for (int i = row8; i >= row1; i--) {
        cout << i + 1 << " ";
        for (int j = cola; j <= colh; j++) {
            cout << (*subject->boardmap)[i][j]->type() << " ";
        }
        cout << endl;
    }
    cout << "  ";
    for (char c = 'a'; c <= 'h'; c++) {
        cout << c << " ";
    }
    cout << endl;

    char color = subject->getCurrentPlayer();
    if (subject->isResign()) {
        if (color == 'W') {
            cout << "Black wins!" << endl;
        } else {
            cout << "White wins!" << endl;
        }
        return;
    }
    if (subject->isstalemate()) {
        cout << "Stalemate!" << endl;
        return;
    }
    if (subject->ischeckmate()) {
        if (color == 'W') {
            cout << "Checkmate! White wins." << endl;
        } else {
            cout << "Checkmate! Black wins." << endl;
        }
        return;
    } 
    if (subject->ischeck()) {
        if (color == 'W') {
            cout << "White is in check." << endl;
        } else {
            cout << "Black is in check." << endl;
        }
        return;
    }
}
