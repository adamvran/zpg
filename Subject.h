#pragma once
#include <vector>

class Observer;
class Subject {
protected:
    std::vector<Observer*> observers;
public:
    void add(Observer* observer);
    void remove(Observer* observer);
    virtual void notifyAll() = 0; //pure virtual method
};
