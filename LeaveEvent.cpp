//
// Created by PC on 12/10/2023.
//

#include "Company.h"
#include "LeaveEvent.h"
#include <iostream>
using namespace std;

Passenger LeaveEvent::Execute() {
    Passenger new_passenger;
    new_passenger.setStartStation(start);
    new_passenger.setId(id);
    Company c;
    Station station = c.getStation(start);

    station.removePassenger(id);

    return new_passenger;
}
