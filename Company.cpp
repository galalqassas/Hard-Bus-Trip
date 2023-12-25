//
// Created by PC on 12/8/2023.
//

#include <iostream>
#include <fstream>
#include "Company.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"
#include "Queue.h"
template class Queue<Event*>;
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
            ArrivalEvent* ae = new ArrivalEvent();
            string type;
            string atime;
            int id, start, end;
            file >> type;
            ae->setPtype(type);
            //
            file >> atime;
            short hour = stoi(atime.substr(0, 2));
            short minute = stoi(atime.substr(3 ,5));
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
                if (sptype == "POD" || sptype == "aged" || sptype == "Pregnant")
                    ae->setSPtype(sptype);
            }
            cout << eventType << " " << type << " " << atime << " " << id << " " << start << " " << end<<" "<<sptype<<endl;
            eventQueue.enqueue(ae);
        } else if (eventType == 'L') {
            LeaveEvent* le = new LeaveEvent();
            string ltime;
            file >> ltime;
            short hour = stoi(ltime.substr(0, 2));
            short minute = stoi(ltime.substr(3, 5));
            le->setTime(Time(hour, minute));
            int id;
            file >> id;
            le->setId(id);
            cout << eventType << " " << ltime << " " << id << endl;
            eventQueue.enqueue(le);
        }
    }
}
/*
    if (p.getPassengerType() == "NP")
        stations[events[i].strtStation].addPassengerNp(&p);
    else if (p.getPassengerType() == "SP")
        stations[events[i].strtStation].addPassengerSp(&p, "Aged");
    else if (p.getPassengerType() == "WP")
        stations[events[i].strtStation].addPassengerWp(&p);
    }
    file.close();*/
