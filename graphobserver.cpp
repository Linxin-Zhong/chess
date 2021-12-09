/*#include <iostream>
#include "graphobserver.h"
#include "window.h"
#include <string>
#include <sstream>
#include <memory>

using namespace std;

GraphObserver::GraphObserver(Board *bd)
        : subject{bd} {
    shared_ptr<Xwindow> tmp = make_shared<Xwindow>(400, 400);
    tmp->fillRectangle(0, 0, 400, 400, Xwindow::Green);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                tmp->fillRectangle(j * 50, (7 - i) * 50, 50, 50, Xwindow::White);
            }
        }
    }
    w = tmp;
    subject->attach(this);
}

GraphObserver::~GraphObserver() {
    subject->detach(this);
}

void GraphObserver::notify() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::shared_ptr<Piece> p = (*subject->boardmap)[i][j];
            if (p == nullptr) {
                if ((i + j) % 2 == 0) {
                    w->fillRectangle(j * 50, (7 - i) * 50, 50, 50, Xwindow::Green);
                } else {
                    w->fillRectangle(j * 50, (7 - i) * 50, 50, 50, Xwindow::White);
                }
                break;
            }
            string str;
            stringstream stream;
            stream << p->type();
            str = stream.str();
            w->drawString(j * 50 + 25, (7 - i) * 50 + 25, str);
        }
    }
}
 */
