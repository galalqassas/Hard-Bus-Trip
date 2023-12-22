//
// Created by PC on 12/10/2023.
//

#include "Time.h"

Time::Time() : hour(hour), min(min), sec(sec) {}


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

short Time::getSec() const {
    return sec;
}

void Time::setSec(short sec) {
    Time::sec = sec;
}

void Time::setTime(short h, short m, short s) {
    this->hour = h;
    this->min = m;
    this->sec = s;
}

Time::~Time() {

}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << "hour: " << time.hour << " min: " << time.min << " sec: " << time.sec;
    return os;
}

bool Time::operator<(const Time& other) const {
    if (hour < other.hour)
        return true;
    if (other.hour < hour)
        return false;
    if (min < other.min)
        return true;
    if (other.min < min)
        return false;
    return sec < other.sec;
}

bool Time::operator>(const Time& other) const {
    return other < *this;
}

bool Time::operator<=(const Time& other) const {
    return !(other < *this);
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}

int Time::toSeconds() const {
    return hour * 3600 + min * 60 + sec;
}

Time Time::fromSeconds(int seconds) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;
    return Time();
}

int Time::operator-(const Time& other) const {
    int secondsThis = toSeconds();
    int secondsOther = other.toSeconds();
    return secondsThis - secondsOther;
}

Time Time::operator+(const Time &t) {
    Time result;
    result.sec = sec + t.sec;
    if (result.sec >= 60) {
        result.sec -= 60;
        result.min += 1;
    }
    result.min += min + t.min;
    if (result.min >= 60) {
        result.min -= 60;
        result.hour += 1;
    }
    result.hour += hour + t.hour;
    if (result.hour >= 24) {
        result.hour -= 24;
    }
    return result;
}

Time::Time (short h, short m, short s) {
    hour = h;
    min = m;
    sec = s;
}
