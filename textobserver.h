#ifndef TEXT_H
#define TEXT_H

#include "observer.h"
#include "board.h"

class TextObserver : public Observer {
    Board *subject;

public:
    TextObserver(Board *bd);

    void notify() override;

    ~TextObserver();
};

#endif
