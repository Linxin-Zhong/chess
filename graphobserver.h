#ifndef GRAPH_H
#define GRAPH_H

#include "observer.h"
#include "board.h"
#include <vector>

class Xwindow;

class GraphObserver : public Observer {
    Board *subject;
    shared_ptr<Xwindow> w; // a Xwindow element to store the window needed (do not create new windows)

public:
    GraphObserver(Board *bd);

    void notify() override;

    void grade(int w, int b);

    void clearGraph();

    ~GraphObserver();
};

#endif
