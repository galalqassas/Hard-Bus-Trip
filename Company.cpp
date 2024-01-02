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

template
class Queue<Event *>;

void Company::read_file(const char *filename, Parameters &eventParameters) {
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
            ArrivalEvent *ae = new ArrivalEvent();
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
            LeaveEvent *le = new LeaveEvent();
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
        cerr << "Error opening output file: " << filename << std::endl;
        return;
    }

    // Writing passenger details
    outputFile << "FT ID AT WT TT\n";
    for (int i = 0; i < finishedPassengerList.getSize(); i++) {
        Passenger* p = finishedPassengerList.peek();
        finishedPassengerList.dequeue();

        Time t(5, 5);
        p->calculateFinishTime(t);  // Note: we need to ensure the busArrivalTime is set correctly before this call
        // I added a random Time object so call the function.
        Time finishTime = p->getFinishTime();
        Time waitTime = p->calculateWaitTime();
        Time tripTime = p->calculateTripTime();


        outputFile << finishTime << " " << p->getId() << " " << p->getArrivalTime() << " "
                   << waitTime << " " << tripTime << "\n";


        finishedPassengerList.enqueue(p);
    }

    // Initialize statistics variables
    int totalNP = 0, totalSP = 0, totalWP = 0;
    int autoPromoted = 0; // Count of promoted passengers so that we don't repeat this passenger;

    for (int i = 0; i < 50; i++) {
        totalNP += stations[i].getWaitingNpForward().getSize() + stations[i].getWaitingNpBackward().getSize();
        totalSP += stations[i].getWaitingSpForward().getSize() + stations[i].getWaitingSpBackward().getSize();
        totalWP += stations[i].getWaitingWcPForward().getSize() + stations[i].getWaitingWcPBackward().getSize();
    }

//    double avgWaitTime = calculateAverageWaitTime();
//    double avgTripTime = calculateAverageTripTime();
    double autoPromotedPercentage = static_cast<double>(autoPromoted) / finishedPassengerList.getSize() * 100;

    outputFile << "passengers: " << finishedPassengerList.getSize() << " [NP: " << totalNP << ", SP: " << totalSP
               << ", WP: " << totalWP << "]\n";
//    outputFile << "passenger Avg Wait time= " << avgWaitTime << "\n";
//    outputFile << "passenger Avg trip time = " << avgTripTime << "\n";
    outputFile << "Auto-promoted passengers: " << autoPromotedPercentage << "%\n";

    // Calculate bus statistics
    int totalMBuses = mBusMaintenance.getSize() + mBusMovingForward.getSize() + mBusMovingBackward.getSize();
    int totalWBuses = wBusMaintenance.getSize() + wBusMovingForward.getSize() + wBusMovingBackward.getSize();
//    double avgBusyTime = calculateAverageBusBusyTime();
//    double avgUtilization = calculateAverageBusUtilization();

    outputFile << "buses: " << (totalMBuses + totalWBuses) << " [WBus: " << totalWBuses << ", MBus: " << totalMBuses
               << "]\n";
//    outputFile << "Avg Busy time = " << fixed << setprecision(2) << avgBusyTime << "%\n";
//    outputFile << "Avg utilization = " << fixed << setprecision(2) << avgUtilization << "%\n";

    outputFile.close();
}

void Company::addBusToCheckup(Bus *bus, Parameters &eventParameters) {
    if (eventParameters.trips_before_checkup >= bus->getJourneys() &&
        (bus->getBusType() == "NP" || bus->getBusType() == "SP")) {
        mBusMaintenance.enqueue(bus);
    } else
        wBusMaintenance.enqueue(bus);
}

void Company::busFromMovingToWaiting(Bus *bus) {

}

void Company::busFromWaitingToMoving(Bus *bus) {

}