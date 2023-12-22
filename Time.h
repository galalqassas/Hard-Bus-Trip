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
    short sec;
public:
    Time();
    short getHour() const;
    void setHour(short hour);
    short getMin() const;
    void setMin(short min);
    short getSec() const;
    void setSec(short sec);
    void setTime(short h, short m, short s);
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
    int toSeconds() const;
    Time fromSeconds(int seconds);
    int operator-(const Time& other) const;
    Time operator+ (const Time& t);
    ~Time();
    Time (short h, short m, short s);
};


#endif //PROJECT_UNIVERSITY_TIME_H
