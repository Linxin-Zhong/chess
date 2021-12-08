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
    subject->print();
}
