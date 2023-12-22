//
// Created by PC on 12/10/2023.
//

#pragma once
#ifndef PROJECT_UNIVERSITY_LEAVEEVENT_H
#define PROJECT_UNIVERSITY_LEAVEEVENT_H
#include "Event.h"


class LeaveEvent : public Event {
public:
    Passenger Execute() override;
};


#endif //PROJECT_UNIVERSITY_LEAVEEVENT_H
