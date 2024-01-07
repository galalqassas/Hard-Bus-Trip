//
// Created by LENOVO on 10/12/2023.
//
#include "Bus.h"

Bus::Bus() : busType(""), busCapacity(0), Num_of_trips(0), Passenger_number(0), journeys(0),
             checkupHours(0), currentStation(0), direction(0), totalBusyTime(0), totalCapacityTime(0) {}

Bus::Bus(string busType, int busCapacity) : busType(busType), busCapacity(busCapacity), Num_of_trips(0),
                                            Passenger_number(0), journeys(0), checkupHours(0), currentStation(0),
                                            direction(0), totalBusyTime(0), totalCapacityTime(0) {}


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
    bool flag=passenger->getEndStation()==isCurrentStation(passenger);
    if(flag) {
        passengers.dequeuePQ();
    }
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

void Bus::updateBusyTime(int tripTime) {
    totalBusyTime += tripTime;
    totalCapacityTime += tripTime * busCapacity;
}

// New method to calculate utilization
double Bus::calculateUtilization() const {
    if (totalBusyTime == 0) return 0;
    return static_cast<double>(totalCapacityTime) / (totalBusyTime * busCapacity) * 100;
}

