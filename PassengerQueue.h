//
// Created by PC on 1/7/2024.
//

#ifndef EASY_BUS_TRIP_V2_PASSENGERQUEUE_H
#define EASY_BUS_TRIP_V2_PASSENGERQUEUE_H

#include "Queue.h"
#include "PassengerQueue.h"
#include "Passenger.h"

class PassengerQueue : public Queue<Passenger*> {
public:
    PassengerQueue() : Queue<Passenger*>() {}

    // Function to remove a passenger by ID
    void removePassengerById(int id);
};

#endif //EASY_BUS_TRIP_V2_PASSENGERQUEUE_H
