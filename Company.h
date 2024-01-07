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
    int num_stations;
    int time_between_stations;
    int num_WBuses;
    int num_MBuses;
    int capacity_WBus;
    int capacity_MBus;
    int trips_before_checkup;
    int checkup_duration_WBus;
    int checkup_duration_MBus;
    int max_waiting_time;
    int get_on_off_time;
};


class Company {
private:
    Time currentTime;
    Queue<Bus *> station0;
    Station *stations = new Station[50];
    Queue<Event *> eventQueue;
    Queue<Passenger *> finishedPassengerList;
    Queue<Bus *> mBusMaintenance;
    Queue<Bus *> wBusMaintenance;
    Queue<Bus *> mBusMovingForward;
    Queue<Bus *> mBusMovingBackward;
    Queue<Bus *> wBusMovingForward;
    Queue<Bus *> wBusMovingBackward;
    Queue<Bus *> station0Buses;
public:
    Company();
    Time getCurrentTime() const;
    void read_file(const char *filename, Parameters &eventParameters,ArrivalEvent *ae,LeaveEvent *le);
    void generateOutputFile(const string& filename);
    void addBusToCheckup(Bus *bus,Parameters&eventParameters);
    void busFromMovingToWaiting(Bus *bus,Parameters &eventParameters);
    void busFromWaitingToMoving(Bus *bus,Parameters  &eventParameters,Station currentStation);
    Station getStation(int stationNumber);
    void incrementTime(int increment = 1);
    void simulation(Station *s);
    void releaseBuses(Queue<Bus *> station0Buses);

    void setCurrentTime(const Time &currentTime);
};


#endif //PROJECT_UNIVERSITY_COMPANY_H
