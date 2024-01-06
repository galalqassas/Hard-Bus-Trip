//
// Created by PC on 12/10/2023.
//


#include "LeaveEvent.h"
#include <iostream>
using namespace std;

Passenger LeaveEvent::Execute() {
    Passenger new_passenger;
    new_passenger.setStartStation(start);
    new_passenger.setId(id);



    return new_passenger;
}
