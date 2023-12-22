//
// Created by PC on 12/10/2023.
//

#include "Event.h"

#include "Event.h"
#include <iostream>
using namespace std;

const Time &Event::getTime() const {
    return time;
}

void Event::setTime(const Time &time) {
    Event::time = time;
}

int Event::getId() const {
    return id;
}

void Event::setId(int id) {
    Event::id = id;
}

int Event::getStart() const {
    return start;
}

void Event::setStart(int start) {
    Event::start = start;
}
