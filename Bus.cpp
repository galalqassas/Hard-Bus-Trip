//
// Created by LENOVO on 10/12/2023.
//
#include "Bus.h"

Bus::Bus() {}

Bus::Bus(string busType, int busCapacity) : busType(busType), busCapacity(busCapacity) {}


void Bus::setBusType(string bt) {
    busType = bt;
}

void Bus::setBusCapacity(int bc) {
    busCapacity = bc;
}

string Bus::getBusType() const {
    return busType;
}

int Bus::getBusCapacity() const {
    return busCapacity;
}

int Bus::getN() const {
    return Num_of_trips;
}

void Bus::setN(int n) {
    Num_of_trips = n;
}

int Bus::getPassengerNumber() const {
    return Passenger_number;
}

void Bus::setPassengerNumber(int passengerNumber) {
    Passenger_number = passengerNumber;
}

const int &Bus::getCurrentStation() const {
    return currentStation;
}

void Bus::setCurrentStation(const int &currentStation) {
    Bus::currentStation = currentStation;
}

void Bus::getPrioritysp(string passenger_type) {
    if (passenger_type == "sp") {

    }
}

void Bus::add_passenger(Passenger *passenger) {
    if (isCurrentStation(passenger)) {
        int priority = getDifferenceStation(passenger);
        passengers.enqueuePQ(passenger, priority);
    }
    Passenger_number++;
}

int Bus::getDifferenceStation(const Passenger *passenger) const {
    return abs(passenger->getEndStation() - passenger->getStartStation());
}

bool Bus::isCurrentStation(const Passenger *passenger) const { return passenger->getStartStation() == currentStation; }

int Bus::getSPPriority(string sp_type) {
    if (sp_type == "Aged") {
        return 1;
    } else if (sp_type == "POD") {
        return 2;
    } else if (sp_type == "pregnant") {
        return 3;
    } else {
        return 0;
    }
}

void Bus::remove_passenger(Passenger *passenger) {
    int priority = abs(passenger->getEndStation() - passenger->getStartStation());
    passengers.dequeuePQ();
    Num_of_trips--;
}

int Bus::getNumOfTrips() const {
    return Num_of_trips;
}

void Bus::setNumOfTrips(int numOfTrips) {
    Num_of_trips = numOfTrips;
}

int Bus::getJourneys() const {
    return journeys;
}

void Bus::setJourneys(int journeys) {
    Bus::journeys = journeys;
}

int Bus::getCheckupHours() const {
    return checkupHours;
}

void Bus::setCheckupHours(int checkupHours) {
    Bus::checkupHours = checkupHours;
}

int Bus::getDirection() const {
    return direction;
}

void Bus::setDirection(int direction) {
    Bus::direction = direction;
}

bool Bus::isBusForward() {
    return direction == 0;
}



