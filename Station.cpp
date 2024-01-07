//
// Created by PC on 12/10/2023.
//

#include "Station.h"
#include "Passenger.h"
#include "PriorityQueue.h"
#include "Queue.h"

short Station::getStationNumber() const {
    return stationNumber;
}


const PriorityQueue<Passenger *> Station::getWaitingSpForward() const {
    return waitingSPForward;
}

void Station::setWaitingSpForward(const PriorityQueue<Passenger*> &waitingSpForward) {
    waitingSPForward = waitingSpForward;
}

const PriorityQueue<Passenger*> &Station::getWaitingSpBackward() const {
    return waitingSPBackward;
}

void Station::setWaitingSpBackward(const PriorityQueue<Passenger*> &waitingSpBackward) {
    waitingSPBackward = waitingSpBackward;
}

const Queue<Passenger *> /*I removed the & here and add const in this function and in isEmpty function inside Queue*/Station::getWaitingNpForward() const {
    return waitingNPForward;
}

void Station::setWaitingNpForward(const Queue<Passenger*> &waitingNpForward) {
    waitingNPForward = waitingNpForward;
}

const Queue<Passenger*> &Station::getWaitingNpBackward() const {
    return waitingNPBackward;
}

void Station::setWaitingNpBackward(const Queue<Passenger*> &waitingNpBackward) {
    waitingNPBackward = waitingNpBackward;
}

const Queue<Passenger*> &Station::getWaitingWcPForward() const {
    return waitingWcPForward;
}

void Station::setWaitingWcPForward(const Queue<Passenger*> &waitingWcPForward) {
    Station::waitingWcPForward = waitingWcPForward;
}

const Queue<Passenger*> &Station::getWaitingWcPBackward() const {
    return waitingWcPBackward;
}

void Station::setWaitingWcPBackward(const Queue<Passenger*> &waitingWcPBackward) {
    Station::waitingWcPBackward = waitingWcPBackward;
}

const Queue<Bus*> &Station::getAvailableBusesForward() const {
    return availableBusesForward;
}

void Station::setAvailableBusesForward(const Queue<Bus*> &availableBusesForward) {
    Station::availableBusesForward = availableBusesForward;
}

const Queue<Bus*> &Station::getAvailableBusesBackward() const {
    return availableBusesBackward;
}

void Station::setAvailableBusesBackward(const Queue<Bus*> &availableBusesBackward) {
    Station::availableBusesBackward = availableBusesBackward;
}

void Station::addPassengerWp(Passenger* passenger) {

    if (isPassengerForward(passenger))
        waitingWcPForward.enqueue(passenger);
    else
        waitingWcPBackward.enqueue(passenger);
}
int Station::getSPPriority(string sp_type) {
    if (sp_type == "aged"){
        return 1;
    } else if (sp_type == "POD"){
        return 2;
    } else if (sp_type == "Pregnant"){
        return 3;
    } else {
        return 0;
    }
}

void Station::addPassengerSp(Passenger* passenger, string type) {
    int priority = getSPPriority(type);
    if (isPassengerForward(passenger))
        waitingSPForward.enqueuePQ(passenger, priority);
    else
        waitingSPBackward.enqueuePQ(passenger, priority);
}

void Station::addPassengerNp(Passenger* passenger) {
    if (isPassengerForward(passenger))
        waitingNPForward.enqueue(passenger);
    else
        waitingNPBackward.enqueue(passenger);
}

bool Station::isPassengerForward(const Passenger *passenger) const {
    return passenger->getEndStation() > passenger->getStartStation();
}

void Station::removePassengerWp(Passenger* passenger) {
    if (isPassengerForward(passenger))
        waitingWcPForward.dequeue();
    else
        waitingWcPBackward.dequeue();
}

void Station::removePassengerNp(Passenger* passenger) {
    if (isPassengerForward(passenger))
        waitingNPForward.dequeue();
    else
        waitingNPBackward.dequeue();
}

void Station::removePassengerSp(Passenger* passenger) {
    if (isPassengerForward(passenger))
        waitingSPForward.dequeuePQ();
    else
        waitingSPBackward.dequeuePQ();
}

void Station::addBusForward(Bus *bus) {
    if (bus->isBusForward()){
        availableBusesForward.enqueue(bus);
    }
}

void Station::addBusBackward(Bus *bus) {
    if (!bus->isBusForward()){
        availableBusesBackward.enqueue(bus);
    }
}
void Station::promotePassenger(Passenger* passenger) {
    passenger->setPassengerType("SP");
    removePassengerNp(passenger);
    addPassengerSp(passenger, "Aged");
}

const Queue<Bus *> &Station::getWaitingMBusesForward() const {
    return waitingMBusesForward;
}

void Station::setWaitingMBusesForward(const Queue<Bus *> &waitingMBusesForward) {
    Station::waitingMBusesForward = waitingMBusesForward;
}

const Queue<Bus *> &Station::getWaitingWBusesForward() const {
    return waitingWBusesForward;
}

void Station::setWaitingWBusesForward(const Queue<Bus *> &waitingWBusesForward) {
    Station::waitingWBusesForward = waitingWBusesForward;
}

const Queue<Bus *> &Station::getWaitingMBusesBackward() const {
    return waitingMBusesBackward;
}

void Station::setWaitingMBusesBackward(const Queue<Bus *> &waitingMBusesBackward) {
    Station::waitingMBusesBackward = waitingMBusesBackward;
}

const Queue<Bus *> &Station::getWaitingWBusesBackward() const {
    return waitingWBusesBackward;
}

void Station::setWaitingWBusesBackward(const Queue<Bus *> &waitingWBusesBackward) {
    Station::waitingWBusesBackward = waitingWBusesBackward;
}

void Station::removePassenger(int id) {
    // Lambda function to search through a queue and remove a passenger with a given ID.
    auto removePassengerFromQueue = [&](Queue<Passenger*> &queue, void (Station::*removalFunction)(Passenger*)) {
        int size = queue.getSize();
        for (int i = 0; i < size; ++i) {
            Passenger* current = queue.dequeue();
            if (current->getId() == id) {
                (this->*removalFunction)(current);
                break; // Stop searching after finding the passenger
            } else {
                queue.enqueue(current); // Re-enqueue the passenger if it's not the one to remove
            }
        }
    };

    // Iterate over each queue and remove the passenger if found.
    removePassengerFromQueue(waitingWcPForward, &Station::removePassengerWp);
    removePassengerFromQueue(waitingWcPBackward, &Station::removePassengerWp);
    removePassengerFromQueue(waitingNPForward, &Station::removePassengerNp);
    removePassengerFromQueue(waitingNPBackward, &Station::removePassengerNp);


}


/*
void Station::addPassenger(Passenger passenger, string sp_type) {
    if (passenger.getStartStation() != stationNumber) return;
    if (passenger.getStartStation() ==  stationNumber){
         if(passenger.getPassengerType() == "wp"){
            if (isForward(passenger))
                waitingWcPForward.enqueue(passenger);
            else
               waitingWcPBackward.enqueue(passenger);
        } else if (passenger.getPassengerType() == "np"){
            if (passenger.getEndStation() > passenger.getStartStation())
                waitingNPForward.enqueue(passenger);
            else
                waitingNPBackward.enqueue(passenger);
        }
        if (passenger.getPassengerType() == "sp" && (sp_type == "aged" || sp_type == "pod" || sp_type == "pregnant")){
            int priority = getSPPriority(sp_type);
            if (passenger.getEndStation() > passenger.getStartStation())
                waitingSPForward.enqueue(passenger, priority);
            else
                waitingSPBackward.enqueuePQ(passenger, priority);
        } else return;
    }
}

bool Station::isPassengerForward(const Passenger &passenger) const {
    return passenger.getEndStation() > passenger.getStartStation();
}

int Station::getSPPriority(string sp_type) {
    if (sp_type == "Aged"){
        return 1;
    } else if (sp_type == "POD"){
        return 2;
    } else if (sp_type == "pregnant"){
        return 3;
    } else {
        return 0;
    }
}

void Station::removePassenger(Passenger passenger, string sp_type) {
    if (passenger.getEndStation() != stationNumber) return;
    if (passenger.getEndStation() ==  stationNumber){
        if(passenger.getPassengerType() == "wp") {
            if (passenger.getEndStation() > passenger.getStartStation())
                waitingWcPForward.dequeue();
            else
                waitingWcPBackward.dequeue();
        } else if (passenger.getPassengerType() == "np"){
            if (passenger.getEndStation() > passenger.getStartStation())
                waitingNPForward.dequeue();
            else
                waitingNPBackward.dequeue();
        }
        if (passenger.getPassengerType() == "sp" && (sp_type == "aged" || sp_type == "pod" || sp_type == "pregnant")){
            if (passenger.getPassengerType() == "sp"
            && (sp_type == "aged" || sp_type == "pod"
            || sp_type == "pregnant")){
                int priority = getSPPriority(sp_type);
                if (passenger.getEndStation() > passenger.getStartStation())
                    waitingSPForward.dequeue();
                else
                    waitingSPBackward.dequeuePQ();
            } else return;
        } else return;
    }
}
*/

void Station::Execute1MinuteStation(Station s, Queue<Bus *> station0Buses) {

    onBoardBuses(station0Buses);
}

void Station::onBoardBuses(Queue<Bus *> station0Buses) {

}