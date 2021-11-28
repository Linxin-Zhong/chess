#ifndef OBSERVER_H_
#define OBSERVER_H_

class Subject;

class Observer {
public:
    virtual void notify() = 0;

    virtual ~Observer() = default;
};
#endif //CHESS_OBSERVER_H
