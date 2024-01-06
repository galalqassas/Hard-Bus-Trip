//
// Created by PC on 12/10/2023.
//

#include "Time.h"
#include "iostream"
using namespace std;
class Time;
class Passenger;

Time::Time() : hour(0), min(0) {}


short Time::getHour() const {
    return hour;
}

void Time::setHour(short hour) {
    Time::hour = hour;
}

short Time::getMin() const {
    return min;
}

void Time::setMin(short min) {
    Time::min = min;
}

void Time::setTime(short h, short m) {
    this->hour = h;
    this->min = m;
}

Time::~Time() {

}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << "hour: " << time.hour << " min: " << time.min << "\n";
    return os;
}

bool Time::operator<(const Time& other) const {
    if (hour < other.hour)
        return true;
    if (other.hour < hour)
        return false;
    return min < other.getMin();
}


Time Time::operator-(const Time& other) const {
    int new_hour = hour - other.hour;
    int new_min = min - other.min;
    if (new_min < 0) {
        new_hour--;
        new_min += 60; // previous hour
    }
    if (new_hour < 0) {
        new_hour = (new_hour + 24) % 24; // previous day
    }
    return Time(new_hour, new_min);
}

Time Time::operator+(const Time &t) {
    Time result;
    result.min = min + t.min;
    if (result.min >= 60) {
        result.min -= 60;
        result.hour = hour + t.hour + 1; // Corrected line
    } else {
        result.hour = hour + t.hour;
    }
    if (result.hour >= 24) {
        result.hour -= 24;
    }
    return result;
}

Time::Time(short h, short m) {
    hour = h;
    min = m;
}

bool Time::operator==(const Time& other) const {
    return (hour == other.hour) && (min == other.min);
}

int Time::getTotalMinutes() {
    return (hour * 60 + min);
}
