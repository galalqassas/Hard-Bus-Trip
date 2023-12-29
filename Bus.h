//
// Created by LENOVO on 10/12/2023.
//
#pragma once
#ifndef DATA_STRUCTURE_PROJECT_BUS_H
#define DATA_STRUCTURE_PROJECT_BUS_H
#include "Passenger.h"
#include "PriorityQueue.h"
#include "LinkedList.h"
#include <string>
class Passenger;
class Bus;
using namespace std;



class Bus {
private:
    string busType;
    int busCapacity;
    int Num_of_trips; // number of delivery trips of this bus
    int Passenger_number; // number of passenger travelled on this bus
    int journeys;
    int checkupHours;
    PriorityQueue<Passenger*> passengers; // moving passengers

    int currentStation;
    void getPrioritysp(string passenger_type);
    int direction;
    int getSPPriority(string sp_type);
public:
    int getDirection() const;
    void setDirection(int direction);
    int getNumOfTrips() const;
    void setNumOfTrips(int numOfTrips);
    int getJourneys() const;
    void setJourneys(int journeys);
    int getCheckupHours() const;
    void setCheckupHours(int checkupHours);

    bool isBusForward();
    Bus();
    Bus(string busType, int busCapacity);
    void setBusType(string bt);
    void setBusCapacity(int bc);
    string getBusType() const;
    int getBusCapacity() const;
    int getN() const;
    void setN(int n);
    int getPassengerNumber() const;
    void setPassengerNumber(int passengerNumber);
    const int& getCurrentStation() const;
    void setCurrentStation(const int &currentStation);
    void add_passenger(Passenger* passenger);
    void remove_passenger(Passenger* passenger);

    bool isCurrentStation(const Passenger *passenger) const;
    int getDifferenceStation(const Passenger *passenger) const;



};
#endif //DATA_STRUCTURE_PROJECT_BUS_H