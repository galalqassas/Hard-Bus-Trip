//
// Created by PC on 12/10/2023.
//

#include "ArrivalEvent.h"
#include <iostream>
using namespace std;

// constructor


Passenger ArrivalEvent::Execute() {
    Passenger new_passenger;
    new_passenger.setPassengerType(ptype);
    new_passenger.setId(id);
    new_passenger.setStartStation(start);
    new_passenger.setEndStation(end);
    new_passenger.setArrivalTime(time);
    new_passenger.setSpecialType(SPtype);
    return new_passenger;
}

int ArrivalEvent::getAnEnd() const {
    return end;
}

void ArrivalEvent::setAnEnd(int anEnd) {
    end = anEnd;
}

const string &ArrivalEvent::getPtype() const {
    return ptype;
}

void ArrivalEvent::setPtype(const string &ptype) {
    ArrivalEvent::ptype = ptype;
}

const string &ArrivalEvent::getSPtype() const {
    return SPtype;
}

void ArrivalEvent::setSPtype(const string &sPtype) {
    SPtype = sPtype;
}

ArrivalEvent::ArrivalEvent() {}
