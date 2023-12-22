//
// Created by PC on 12/8/2023.
//

#include <iostream>
#include <fstream>
#include "Company.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"

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

    int num_events;
    file >> num_events;
//    Event_To_Read events[num_events];
    for (int i = 0; i < num_events; ++i) {
        char eventType;
        file >> eventType;
        if (eventType == 'A') {
            ArrivalEvent ae;
            string type, sptype;
            string atime;
            int id,start,end;
            file >> type;
            ae.setPtype(type);
            //
            file >> atime;
            int hour = stoi(atime.substr(0, 2));
            int minute = stoi(atime.substr(3, 5));
            Time t(hour, minute, 0);
            ae.setTime(t);
            //
            file >> id;
            ae.setId(id);
            //
            file >> start;
            ae.setStart(start);
            //
            file >> end;
            ae.setAnEnd(end);

            file >> sptype;
            if (sptype != "\n")
                ae.setSPtype(sptype);

           eventQueue.enqueue(&ae);
        } else if (eventType == 'L') {
            LeaveEvent le;
            string ltime;
            file >> ltime;
            int hour = stoi(ltime.substr(0, 2));
            int minute = stoi(ltime.substr(3, 5));
            le.setTime(Time(hour, minute, 0));
            int id, start, end;
            file >> id;
            le.setId(id);
            eventQueue.enqueue(&le);
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
    file.close(); */
}