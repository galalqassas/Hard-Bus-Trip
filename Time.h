//
// Created by PC on 12/10/2023.
//
#pragma once
#ifndef PROJECT_UNIVERSITY_TIME_H
#define PROJECT_UNIVERSITY_TIME_H


#include <ostream>

class Time {
private:
    short hour;
    short min;
public:
    Time();
    Time(short hour, short min);
    short getHour() const;
    void setHour(short hour);
    short getMin() const;
    void setMin(short min);
    void setTime(short h, short m);
    bool operator<(const Time& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
    Time operator-(const Time& other) const;
    Time operator+(const Time& t);
    bool operator==(const Time& other) const;
    int getTotalMinutes();
    ~Time();
};


#endif //PROJECT_UNIVERSITY_TIME_H
