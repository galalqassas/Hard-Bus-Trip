//
// Created by PC on 12/10/2023.
//
#pragma once
#ifndef PROJECT_UNIVERSITY_ARRIVALEVENT_H
#define PROJECT_UNIVERSITY_ARRIVALEVENT_H

#include "Event.h"
class ArrivalEvent : public Event {
private:
    int end; // end station (only for arrival events)
    string ptype; // passenger type (SP, WP, NP) (only for arrival events)
    string SPtype; // extra word for an SP type
public:
    ArrivalEvent();
    int getAnEnd() const;
    void setAnEnd(int anEnd);
    const string &getPtype() const;
    void setPtype(const string& ptype);
    const string &getSPtype() const;
    void setSPtype(const string& sPtype);
    Passenger Execute() override;
    friend void print(ostream& out, const ArrivalEvent& ae);
};


#endif //PROJECT_UNIVERSITY_ARRIVALEVENT_H
