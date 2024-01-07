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
    removePassengerFromQueue(waitingWcPForward, id);
    removePassengerFromQueue(waitingWcPBackward, id);
    removePassengerFromQueue(waitingNPForward, id);
    removePassengerFromQueue(waitingNPBackward, id);
    removePassengerFromPQ(waitingSPBackward, id);
    removePassengerFromPQ(waitingSPForward, id);
}


void Station::removePassengerFromQueue(Queue<Passenger *> &q, int id) {
    Passenger* temp = nullptr; // Temporary pointer to find the right passenger
    // Loop through the queue to find the passenger with the given id
    for (int i = 0; i < q.getSize(); ++i) {
        temp = q.dequeue(); // Take the front item
        if (temp->getId() != id) {
            q.enqueue(temp); // Put it back if it's not the one we're looking for
        } else {
            // Found the right passenger, don't enqueue it back
            continue;
        }
    }
}

void Station::removePassengerFromPQ(PriorityQueue<Passenger *> &pq, int id) {
    Passenger* temp = nullptr; // Temporary pointer to find the right passenger
    int tempPriority = 0;
    // Similar approach as with the regular queue, but keeping track of priorities as well
    for (int i = 0; i < pq.getSize(); ++i) {
        temp = pq.dequeuePQ(); // Take the front item
        tempPriority = getSPPriority(temp->getSpecialType());
        if (temp->getId() != id) {
            pq.enqueuePQ(temp, tempPriority);
        } else {
            continue;
        }
    }
}
void Station::Execute1MinuteStation(Station s, Bus *tempBus,Passenger *passenger,int numberOfPassengerToRelease) {

    onBoardBuses(tempBus,passenger,numberOfPassengerToRelease);
}

void Station::onBoardBuses(Bus *bus,Passenger *passenger,int numberOfPassengerToRelease) {

    for(int i=0;i<numberOfPassengerToRelease;i++) {
        bus->remove_passenger(passenger);
    }


}
void takeAction(Bus * bus){
//After realising the passenger i have a lot of decisions, what is my current station?(if i am in station s i have to check if the bus will go to checkup)
//This will be done over all the buses and when i drop buses i have to add them into a temp queue to rejoin them to the original queue
if(bus->ge)
}


