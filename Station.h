//
// Created by PC on 12/10/2023.
//

#ifndef PROJECT_UNIVERSITY_STATION_H
#define PROJECT_UNIVERSITY_STATION_H
#pragma once
#include "Passenger.h"
#include "Bus.h"
#include "PriorityQueue.h"
#include "Queue.h"
class Passenger;
class Bus;
using namespace std;
class Station {
private:
    short stationNumber;
    PriorityQueue<Passenger*> waitingSPForward;
    PriorityQueue<Passenger*> waitingSPBackward;
    Queue<Passenger*> waitingWcPForward;
    Queue<Passenger*> waitingWcPBackward;
    Queue<Passenger*> waitingNPForward;
    Queue<Passenger*> waitingNPBackward;
    Queue<Bus*> availableBusesForward;
    Queue<Bus*> availableBusesBackward;
    // I did not know where is the waiting bus Queue, so I will create one, you can change it later.
    Queue<Bus *>waitingMBusesForward;
    Queue<Bus *>waitingWBusesForward;
    Queue<Bus *>waitingMBusesBackward;
    Queue<Bus *>waitingWBusesBackward;
public:
    const Queue<Bus *> &getWaitingWBusesBackward() const;

    void setWaitingWBusesBackward(const Queue<Bus *> &waitingWBusesBackward);

public:
    const Queue<Bus *> &getWaitingWBusesForward() const;

    void setWaitingWBusesForward(const Queue<Bus *> &waitingWBusesForward);

    const Queue<Bus *> &getWaitingMBusesBackward() const;

    void setWaitingMBusesBackward(const Queue<Bus *> &waitingMBusesBackward);

public:
    const Queue<Bus *> &getWaitingMBusesForward() const;

    void setWaitingMBusesForward(const Queue<Bus *> &waitingMBusesForward);

private:
    int getSPPriority(string sp_type);
    bool isPassengerForward(const Passenger *passenger) const;
public:
    // getters and setters
    short getStationNumber() const;

    const PriorityQueue<Passenger *> getWaitingSpForward() const;
    void setWaitingSpForward(const PriorityQueue<Passenger*> &waitingSpForward);
    const PriorityQueue<Passenger*> &getWaitingSpBackward() const;
    void setWaitingSpBackward(const PriorityQueue<Passenger*> &waitingSpBackward);
    const Queue<Passenger *> getWaitingNpForward() const;
    void setWaitingNpForward(const Queue<Passenger*> &waitingNpForward);
    const Queue<Passenger*> &getWaitingNpBackward() const;
    void setWaitingNpBackward(const Queue<Passenger*> &waitingNpBackward);
    const Queue<Passenger*> &getWaitingWcPForward() const;
    void setWaitingWcPForward(const Queue<Passenger*> &waitingWcPForward);
    const Queue<Passenger*> &getWaitingWcPBackward() const;
    void setWaitingWcPBackward(const Queue<Passenger*> &waitingWcPBackward);
    const Queue<Bus*> &getAvailableBusesForward() const;
    void setAvailableBusesForward(const Queue<Bus*> &availableBusesForward);
    const Queue<Bus*> &getAvailableBusesBackward() const;
    void setAvailableBusesBackward(const Queue<Bus*> &availableBusesBackward);


    void addPassengerWp(Passenger* passenger);
    void addPassengerSp(Passenger* passenger, string type);
    void addPassengerNp(Passenger* passenger);

    void removePassengerWp(Passenger* passenger);
    void removePassengerNp(Passenger* passenger);
    void removePassengerSp(Passenger* passenger);
    void addBusForward(Bus* bus);
    void addBusBackward(Bus* bus);

    void promotePassenger(Passenger* passenger);
};


#endif //PROJECT_UNIVERSITY_STATION_H
