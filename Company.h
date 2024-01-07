//
// Created by PC on 12/8/2023.
//
#pragma once
#ifndef PROJECT_UNIVERSITY_COMPANY_H
#define PROJECT_UNIVERSITY_COMPANY_H

#include <iostream>
#include "Bus.h"
#include "Queue.h"
#include "Passenger.h"
#include "Event.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"

//#include "Station.h"
class Passenger;
using namespace std;


struct Parameters {
    short num_stations;
    short time_between_stations;
    short num_WBuses;
    short num_MBuses;
    short capacity_WBus;
    short capacity_MBus;
    short trips_before_checkup;
    short checkup_duration_WBus;
    short checkup_duration_MBus;
    short max_waiting_time;
    short get_on_off_time;
};


class Company {
private:
    Time currentTime;
    Queue<Bus *> station0;
    Station *stations;
    Queue<Event *> eventQueue;
    Queue<Passenger *> finishedPassengerList;
    Queue<Bus *> mBusMaintenance;
    Queue<Bus *> wBusMaintenance;
    Queue<Bus *> mBusMovingForward;
    Queue<Bus *> mBusMovingBackward;
    Queue<Bus *> wBusMovingForward;
    Queue<Bus *> wBusMovingBackward;
    Parameters eventParameters;
public:
    Company();
    Time getCurrentTime() const;
    void read_file(const char *filename, ArrivalEvent *ae,LeaveEvent *le);
    void generateOutputFile(const string& filename);
    void addBusToCheckup(Bus *bus,Parameters&eventParameters);
    void busFromMovingToWaiting(Bus *bus,Parameters &eventParameters);
    void busFromWaitingToMoving(Bus *bus,Parameters  &eventParameters,Station currentStation);
    Station getStation(int stationNumber);
    void incrementTime(int increment = 1);
    void simulation(Station *s);
    void releaseBusesEvery15();

    void setCurrentTime(const Time &currentTime);
};


#endif //PROJECT_UNIVERSITY_COMPANY_H
