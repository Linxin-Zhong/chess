#ifndef CHESS_SUBJECT_H
#define CHESS_SUBJECT_H

#include <vector>

class subject {
    std::vector<observer *> observers;
public:
    attatch(observer
    * o);
    detach(observer
    *o);

};

#endif