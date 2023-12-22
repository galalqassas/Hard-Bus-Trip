//
// Created by PC on 12/10/2023.
//

#ifndef PROJECT_UNIVERSITY_EVENT_H
#define PROJECT_UNIVERSITY_EVENT_H
#pragma once
#include <string>
#include "Time.h"
#include "Station.h"
using namespace std;

class Event {
protected:
    Time time; // event time step in hh:mm format
    int id; // passenger ID
    int start; // start station
public:
    // constructor
    Event();
    virtual Passenger Execute()=0;
    const Time &getTime() const;
    void setTime(const Time &time);
    int getId() const;
    void setId(int id);
    int getStart() const;
    void setStart(int start);
};


#endif //PROJECT_UNIVERSITY_EVENT_H
