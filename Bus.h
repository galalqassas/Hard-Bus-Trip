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
    string busType;  // "WB" for Wheelchair Bus, "MB" for Mixed Bus
    int busCapacity;
    int Num_of_trips;
    int Passenger_number; // Total number of passengers travelled on this bus
    int journeys;
    int checkupHours;
    PriorityQueue<Passenger*> passengers; // moving passengers

    int currentStation;
    int direction; // 0 for forward, 1 for backward

    // New attributes for busy time and utilization
    int totalBusyTime; // Total time the bus spent in service
    int totalCapacityTime; // Sum of capacity * time for each trip

public:
    Bus();
    Bus(string busType, int busCapacity);

    void setBusType(string bt);
    void setBusCapacity(int bc);
    string getBusType() const;
    int getBusCapacity() const;
    int getNumOfTrips() const;
    void setNumOfTrips(int numOfTrips);
    int getPassengerNumber() const;
    void setPassengerNumber(int passengerNumber);
    const int& getCurrentStation() const;
    void setCurrentStation(const int &currentStation);

    void add_passenger(Passenger* passenger);
    void remove_passenger(Passenger* passenger);

    bool isCurrentStation(const Passenger *passenger) const;
    int getDifferenceStation(const Passenger *passenger) const;
    int getSPPriority(string sp_type);

    int getJourneys() const;
    void setJourneys(int journeys);
    int getCheckupHours() const;
    void setCheckupHours(int checkupHours);
    int getDirection() const;
    void setDirection(int direction);
    bool isBusForward();

    // New methods for busy time and utilization
    void updateBusyTime(int tripTime);
    double calculateUtilization() const;
};
#endif //DATA_STRUCTURE_PROJECT_BUS_H