//
// Created by LENOVO on 10/12/2023.
//

#include "Passenger.h"


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

void Passenger::setId(int id) {
    Id = id;
}

Passenger::Passenger() {}
