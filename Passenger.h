//
// Created by LENOVO on 10/12/2023.
//
#pragma once
#ifndef DATA_STRUCTURE_PROJECT_PASSENGER_H
#define DATA_STRUCTURE_PROJECT_PASSENGER_H

#include "Time.h"
#include <string>
#include "Station.h"

using namespace std;

class Passenger {
private:
    Time Arrival_Time;  // AT
    Time Move_Time;     // MT
    Time Finish_Time;   // FT
    short Get_On;
    short Get_Off;
    int Start_Station;
    int End_Station;
    string Passenger_Type; // "NP", "SP", "WP"
    string Special_Type;   // Additional type for special passengers
    int Id;
    bool Auto_Promoted;    // Flag for auto-promotion
    Time Max_Wait_Time;    // Max wait time for auto-promotion

public:
    Passenger();
    Passenger(int maxWaitMinutes); // Constructor to set max wait time

    const Time &getArrivalTime() const;
    void setArrivalTime(const Time &arrivalTime);

    short getGetOn() const;
    void setGetOn(short getOn);

    short getGetOff() const;
    void setGetOff(short getOff);

    int getStartStation() const;
    void setStartStation(int startStation);

    int getEndStation() const;
    void setEndStation(int endStation);

    const Time &getMoveTime() const;
    void setMoveTime(const Time &moveTime);

    const Time &getFinishTime() const;
    void setFinishTime(const Time &finishTime);

    const string &getPassengerType() const;
    void setPassengerType(const string &passengerType);

    const string &getSpecialType() const;
    void setSpecialType(const string &specialType);

    int getId() const;
    void setId(int id);

    Time calculateWaitTime() const;
    void calculateFinishTime(Time &busArrivalTime);
    Time calculateTripTime() const;
    bool isForward();
    bool isAutoPromoted() const; // Method to check auto-promotion


};



#endif //DATA_STRUCTURE_PROJECT_PASSENGER_H
