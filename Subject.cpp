#include "Subject.h"

void Subject::add(Observer *observer) {
    observers.push_back(observer);
}

void Subject::remove(Observer *observer) {
    std::remove(observers.begin(), observers.end(), observer);
}
