//
// Created by LENOVO on 10/12/2023.
//

#include "Passenger.h"


Passenger::Passenger() : Auto_Promoted(false), Max_Wait_Time(0, 0) {}

Passenger::Passenger(int maxWaitMinutes) : Auto_Promoted(false), Max_Wait_Time(0, maxWaitMinutes) {}

const Time &Passenger::getArrivalTime() const {
    return Arrival_Time;
}

void Passenger::setArrivalTime(const Time &arrivalTime) {
    Arrival_Time = arrivalTime;
}

short Passenger::getGetOn() const {
    return Get_On;
}

void Passenger::setGetOn(short getOn) {
    Get_On = getOn;
}

short Passenger::getGetOff() const {
    return Get_Off;
}

void Passenger::setGetOff(short getOff) {
    Get_Off = getOff;
}

int Passenger::getStartStation() const {
    return Start_Station;
}

void Passenger::setStartStation(int startStation) {
    Start_Station = startStation;
}

int Passenger::getEndStation() const {
    return End_Station;
}

void Passenger::setEndStation(int endStation) {
    End_Station = endStation;
}

const string &Passenger::getPassengerType() const {
    return Passenger_Type;
}

void Passenger::setPassengerType(const string &passengerType) {
    Passenger_Type = passengerType;
}

const string &Passenger::getSpecialType() const {
    return Special_Type;
}

void Passenger::setSpecialType(const string &specialType) {
    Special_Type = specialType;
}

int Passenger::getId() const {
    return Id;
}

void Passenger::setMoveTime(const Time &moveTime) {
    Move_Time = moveTime;
}

void Passenger::setId(int id) {
    Id = id;
}



Time Passenger::calculateWaitTime() const {
    // WT = MT - AT
    return Move_Time - Arrival_Time;
}

void Passenger::calculateFinishTime(Time &busArrivalTime) {
    // FT = busArrivalTime + this passenger's Get_Off time
    Time getOffTime(0, Get_Off);
    Finish_Time = busArrivalTime + getOffTime;
}

Time Passenger::calculateTripTime() const {
    // TT = FT - MT
    return Finish_Time - Move_Time;
}

const Time &Passenger::getMoveTime() const {
    return Move_Time;
}

const Time &Passenger::getFinishTime() const {
    return Finish_Time;
}

void Passenger::setFinishTime(const Time &finishTime) {
    Finish_Time = finishTime;
}

bool Passenger::isAutoPromoted() const {
    Time waitTime = calculateWaitTime();
    if (Max_Wait_Time < waitTime  && Passenger_Type == "NP") {
        return true;
    }
    return false;
}

bool Passenger::isForward() {
    return (getEndStation() - getStartStation() > 0);
}

