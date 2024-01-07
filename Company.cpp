//
// Created by PC on 12/8/2023.
//

#include "Company.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "ArrivalEvent.h"
#include "LeaveEvent.h"
#include "Queue.h"
#include <map>
#include <algorithm>

using namespace std;

template
class Queue<Event *>;

void Company::read_file(const char *filename, ArrivalEvent *ae, LeaveEvent *le) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    file >> eventParameters.num_stations >> eventParameters.time_between_stations;
    file >> eventParameters.num_WBuses >> eventParameters.num_MBuses;
    file >> eventParameters.capacity_WBus >> eventParameters.capacity_MBus;
    file >> eventParameters.trips_before_checkup >> eventParameters.checkup_duration_WBus
         >> eventParameters.checkup_duration_MBus;
    file >> eventParameters.max_waiting_time >> eventParameters.get_on_off_time;

    cout << "Parameters:\n"
         << "  Number of Stations: " << eventParameters.num_stations << "\n"
         << "  Time Between Stations: " << eventParameters.time_between_stations << "\n"
         << "  Number of WBuses: " << eventParameters.num_WBuses << "\n"
         << "  Number of MBuses: " << eventParameters.num_MBuses << "\n"
         << "  Capacity of WBus: " << eventParameters.capacity_WBus << "\n"
         << "  Capacity of MBus: " << eventParameters.capacity_MBus << "\n"
         << "  Trips Before Checkup: " << eventParameters.trips_before_checkup << "\n"
         << "  Checkup Duration WBus: " << eventParameters.checkup_duration_WBus << "\n"
         << "  Checkup Duration MBus: " << eventParameters.checkup_duration_MBus << "\n"
         << "  Max Waiting Time: " << eventParameters.max_waiting_time << "\n"
         << "  Get On/Off Time: " << eventParameters.get_on_off_time << "\n";

    int num_events;
    file >> num_events;

    for (int i = 0; i < num_events; ++i) {
        char eventType;
        file >> eventType;
        if (eventType == 'A') {
            string type;
            string atime;
            int id, start, end;
            file >> type;
            ae->setPtype(type);
            //
            file >> atime;
            short hour = stoi(atime.substr(0, 2));
            short minute = stoi(atime.substr(3, 5));
            Time t(hour, minute);
            ae->setTime(t);
            file >> id;
            ae->setId(id);
            //
            file >> start;
            ae->setStart(start);
            //
            file >> end;
            ae->setAnEnd(end);
            string sptype;
            getline(file, sptype);
            if (!sptype.empty()) {
                ae->setSPtype(sptype);
            }
            cout << eventType << " " << type << " " << atime << " " << id << " " << start << " " << end << " " << sptype
                 << endl;
            eventQueue.enqueue(ae);
        } else if (eventType == 'L') {
            string ltime;
            file >> ltime;
            short hour = stoi(ltime.substr(0, 2));
            short minute = stoi(ltime.substr(3, 5));
            le->setTime(Time(hour, minute));
            int id;
            file >> id;
            le->setId(id);
            short start;
            file >> start;
            le->setStart(start);
            cout << eventType << " " << ltime << " " << id << " " << start << endl;
            eventQueue.enqueue(le);
        }
    }
}


void Company::generateOutputFile(const string &filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << filename << endl;
        return;
    }

    map<Time, Queue<Passenger *>> sortedPassengers;
    while (!finishedPassengerList.isEmpty()) {
        Passenger *p = finishedPassengerList.dequeue();
        sortedPassengers[p->getFinishTime()].enqueue(p);
    }

    outputFile << "FT ID AT WT TT\n";
    long totalWaitTime = 0, totalTripTime = 0;
    int totalNP = 0, totalSP = 0, totalWP = 0, autoPromoted = 0;

    for (auto &pair: sortedPassengers) {
        while (!pair.second.isEmpty()) {
            Passenger *p = pair.second.dequeue();

            Time waitTime = p->calculateWaitTime();
            Time tripTime = p->calculateTripTime();
            totalWaitTime += waitTime.getTotalMinutes();
            totalTripTime += tripTime.getTotalMinutes();

            string type = p->getPassengerType();
            if (type == "NP") totalNP++;
            else if (type == "SP") totalSP++;
            else if (type == "WP") totalWP++;

            // Check for auto-promoted passengers to not count them twice
            if (p->isAutoPromoted()) autoPromoted++;

            outputFile << p->getFinishTime() << " " << p->getId() << " "
                       << p->getArrivalTime() << " " << waitTime << " " << tripTime << "\n";
        }
    }

    int totalPassengers = totalNP + totalSP + totalWP;
    double avgWaitTime = static_cast<double>(totalWaitTime) / totalPassengers;
    double avgTripTime = static_cast<double>(totalTripTime) / totalPassengers;
    double autoPromotedPercentage = static_cast<double>(autoPromoted) / totalNP * 100;

    // Bus statistics
    int totalBuses = mBusMaintenance.getSize() + wBusMaintenance.getSize()
                     + mBusMovingForward.getSize() + mBusMovingBackward.getSize()
                     + wBusMovingForward.getSize() + wBusMovingBackward.getSize();
    int totalMBuses = mBusMaintenance.getSize() + mBusMovingForward.getSize()
                      + mBusMovingBackward.getSize();
    int totalWBuses = wBusMaintenance.getSize()
                      + wBusMovingForward.getSize() + wBusMovingBackward.getSize();
    double totalBusyTime = 0, totalUtilization = 0;

    // Bus statistics


    // Calculate total busy time and utilization for all buses
    for (int i = 0; i < station0.getSize(); i++) {
        Bus *b = station0.dequeue();
        b->updateBusyTime(0); // instead of 0 it should be total trip time
        totalUtilization += b->calculateUtilization();
        station0.enqueue(b);
    }

    double avgBusyTime = totalBuses > 0 ? totalBusyTime / totalBuses : 0;
    double avgUtilization = totalBuses > 0 ? totalUtilization / totalBuses * 100 : 0;

    // Output passenger statistics
    outputFile << "passengers: " << totalPassengers << " [NP: " << totalNP
               << ", SP: " << totalSP << ", WP: " << totalWP << "]\n";
    outputFile << "passenger Avg Wait time= " << avgWaitTime << "\n";
    outputFile << "passenger Avg trip time = " << avgTripTime << "\n";
    outputFile << "Auto-promoted passengers: " << fixed << setprecision(2)
               << autoPromotedPercentage << "%\n";

    // Output bus statistics
    outputFile << "buses: " << totalBuses << " [WBus: "
               << totalWBuses << ", MBus: " << totalMBuses << "]\n";
    outputFile << "Avg Busy time = " << fixed << setprecision(2) << avgBusyTime << "%\n";
    outputFile << "Avg utilization = " << fixed << setprecision(2) << avgUtilization << "%\n";

    outputFile.close();
}

void Company::addBusToCheckup(Bus *bus, Parameters &eventParameters) {
    if (eventParameters.trips_before_checkup >= bus->getJourneys() &&
        (bus->getBusType() == "NP" || bus->getBusType() == "SP")) {
        mBusMaintenance.enqueue(bus);
    } else
        wBusMaintenance.enqueue(bus);
}

void Company::busFromMovingToWaiting(Bus *bus, Parameters &eventParameters) {
    //if()


}

void Company::busFromWaitingToMoving(Bus *bus, Parameters &eventParameters, Station currentStation) {

// Check if the Mbus is full and there are no waiting passengers of type SP/NP
    if ((currentStation.getWaitingNpForward().isEmpty() || currentStation.getWaitingSpForward().isEmpty()) &&
        bus->getBusType() == "MB" && bus->getBusCapacity() == eventParameters.capacity_MBus) {
        // Check if the bus is moving forward or backward and enqueue accordingly
        if (bus->isBusForward()) {
            mBusMovingForward.enqueue(bus);
        } else {
            mBusMovingBackward.enqueue(bus);
        }
    }

// Check if the Wbus is full and there are no waiting passengers of type WP
    else if ((currentStation.getWaitingNpForward().isEmpty() || currentStation.getWaitingSpForward().isEmpty()) &&
             bus->getBusType() == "WB" && bus->getBusCapacity() == eventParameters.capacity_MBus) {
        // Check if the bus is moving forward or backward and enqueue accordingly
        if (bus->isBusForward()) {
            wBusMovingForward.enqueue(bus);
        } else {
            wBusMovingBackward.enqueue(bus);
        }
    }
}

Station Company::getStation(int stationNumber) {
    return stations[stationNumber];
}

Time Company::getCurrentTime() const {
    return currentTime;
}

void Company::setCurrentTime(const Time &currentTime) {
    Company::currentTime = currentTime;
}


void Company::incrementTime(int increment) {
    currentTime = currentTime + Time(0, increment);
}

void Company::releaseBusesEvery15() {
    if (currentTime.getTotalMinutes() % 15 == 0) {
        station0.dequeue();
    }
}

void Company::simulation(Station *s) {
    // I have to add a loop in which i start to read the events
    // The input file is read only once
    // Time to start the program
    Time currentTime(4, 0);
    this->setCurrentTime(currentTime);

    stations = new Station[eventParameters.num_stations];
    //Create events
    LeaveEvent *le = new LeaveEvent();
    ArrivalEvent *ae = new ArrivalEvent();

    //File name
    const char *filename = "C:\\Users\\LENOVO\\CLionProjects\\Hard-Bus-Trip\\random_file.txt";
    //One of the most important things
    Parameters eventParameters;
    //Read from the function
    read_file(filename, ae, le);
    //Add function that is resposible to execute event at this minute

    //Create MBus
    for (int i = 0; i < eventParameters.num_MBuses; i++) {
        Bus *newBus = new Bus("MB", eventParameters.capacity_MBus);
        station0.enqueue(newBus);
    }
    //Create WBus
    for (int i = 0; i < eventParameters.num_WBuses; i++) {
        Bus *newBus = new Bus("WB", eventParameters.capacity_MBus);
        station0.enqueue(newBus);
    }
    //Release buses from station 0
    releaseBusesEvery15();
    //Check to moving

    //Loop over every station
    int numOfStation = eventParameters.num_stations;
    int numberOfAllBuses = eventParameters.num_WBuses + eventParameters.num_MBuses;
    int numberOfPassengerToRelease = 60 / eventParameters.get_on_off_time;

    Passenger new_passenger = Passenger();
//    Passenger* passenger = new Passenger();
    for (int i = 0; i < eventQueue.getSize(); i++) {
        auto event = eventQueue.dequeue();
        if (event->getTime() == currentTime)
            new_passenger = event->Execute();
    }


    for (int i = 0; i < numOfStation; i++) {
        for (int j = 0; j < numberOfAllBuses; j++) {
            Station currentStation = stations[i];
            Bus *tempBus = station0.dequeue();
            currentStation.removePassengersInOneMinute(currentStation, tempBus, &new_passenger,
                                                       numberOfPassengerToRelease);
        }
    }

    // There is a print function here to print everything every 1 minute

    // Increment minute by one
    incrementTime(1);

}

Company::Company() {
    Time t;
    currentTime = t;
}

