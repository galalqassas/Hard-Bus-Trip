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

    Queue<Bus *>waitingMBusesForward;
    Queue<Bus *>waitingWBusesForward;
    Queue<Bus *>waitingMBusesBackward;
    Queue<Bus *>waitingWBusesBackward;
    int getSPPriority(string sp_type);
public:
    bool isPassengerForward(const Passenger *passenger) const;
    const Queue<Bus *> &getWaitingWBusesBackward() const;
    void setWaitingWBusesBackward(const Queue<Bus *> &waitingWBusesBackward);
    const Queue<Bus *> &getWaitingWBusesForward() const;
    void setWaitingWBusesForward(const Queue<Bus *> &waitingWBusesForward);
    const Queue<Bus *> &getWaitingMBusesBackward() const;
    void setWaitingMBusesBackward(const Queue<Bus *> &waitingMBusesBackward);
    const Queue<Bus *> &getWaitingMBusesForward() const;
    void setWaitingMBusesForward(const Queue<Bus *> &waitingMBusesForward);
    void removePassengerWp(Passenger* passenger);
    void removePassengerNp(Passenger* passenger);
    void removePassengerSp(Passenger* passenger);
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


    void addBusForward(Bus* bus);
    void addBusBackward(Bus* bus);

    void promotePassenger(Passenger* passenger);

    void removePassenger(int id);
    void removePassengerFromQueue(Queue<Passenger *> &q, int id);

    void removePassengerFromPQ(PriorityQueue<Passenger *> &pq, int id);

    void removePassengersInOneMinute(Station s, Bus *tempBus, Passenger *passenger, int numberOfPassengerToRelease);

    void onBoardBuses(Bus *bus,Passenger *passenger,int numberOfPassengerToRelease);//Responsible for removing the passengers from the bus
};


#endif //PROJECT_UNIVERSITY_STATION_H

