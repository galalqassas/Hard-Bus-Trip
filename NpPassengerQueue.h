//
// Created by PC on 12/17/2023.
//
#pragma once
#ifndef PROJECT_UNIVERSITY_NPPASSENGERQUEUE_H
#define PROJECT_UNIVERSITY_NPPASSENGERQUEUE_H
#include "Passenger.h"

class NpPassengerQueue : public Queue<Passenger> {
    // passenger queue implementation
    void removePassenger(int id);
};


#endif //PROJECT_UNIVERSITY_NPPASSENGERQUEUE_H
