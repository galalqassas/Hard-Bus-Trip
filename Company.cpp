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

    int num_events;
    file >> num_events;
//    Event_To_Read events[num_events];
    for (int i = 0; i < num_events; ++i) {
        char eventType;
        file >> eventType;
        if (eventType == 'A') {
            ArrivalEvent* ae=new ArrivalEvent();
            string type, sptype;
            string atime;
            int id,start,end;
            file >> type;
            ae->setPtype(type);
            //
            file >> atime;
            size_t colonPos = atime.find(':');

            if (colonPos != string::npos) {
                try {
                    short hour = stoi(atime.substr(0, colonPos));
                    short minute = stoi(atime.substr(colonPos + 1));

                    // Check if the minute part has only one digit, and add a leading zero if needed
                    if (atime.substr(colonPos + 1).length() == 1) {
                        minute *= 10;  // Add a zero to the minute part
                    }

                    // Use hour and minute as needed
                    Time t(hour, minute);
                    ae->setTime(t);
                } catch (const invalid_argument& e) {
                    cerr << "Error parsing time: " << atime << endl;
                }
            } else {
                cerr << "Invalid time format: " << atime << endl;
            }
            //
            file >> id;
            ae->setId(id);
            //
            file >> start;
            ae->setStart(start);
            //
            file >> end;
            ae->setAnEnd(end);

            file >> sptype;
            if (sptype != "\n")
                ae->setSPtype(sptype);
            cout<<"The type is "<<type<<"\n The arrival time is "<<atime<<"\n The id is "<<id<<"\n The start is "<<start<<"\n The end is "<<end<<"\n the sptype is "<<sptype<<endl;
           eventQueue.enqueue(ae);

        } else if (eventType == 'L') {
            LeaveEvent* le=new LeaveEvent();
            string ltime;
            file >> ltime;
            int hour = stoi(ltime.substr(0, 2));
            int minute = stoi(ltime.substr(3, 5));
            le->setTime(Time(hour, minute));
            int id, start, end;
            file >> id;
            le->setId(id);
            cout<<"\n The leave time is "<<ltime<<"\n The id is "<<id<<"\n The start is "<<start<<"\n The end is "<<end<<endl;
            eventQueue.enqueue(le);
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

}